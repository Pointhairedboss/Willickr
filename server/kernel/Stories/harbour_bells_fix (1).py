#!/usr/bin/env python3
"""
OLD SAILOR'S HARBOUR  — v2  (bells actually ring this time)

Key changes from v1:
  - _bell_playing Event pauses ALL Brownian wind CC updates during bell decay
  - Bell holds patch lock for full decay duration (2-4s), not just setup
  - Resonance raised to 120 (guaranteed self-oscillation on S-1)
  - Bell trigger: note 60 as "dummy" carrier; filter IS the pitch
  - Cutoff map rebuilt: covers audible range for buoys + carillon
  - Church bells: now sequence as a background thread, not blocking
  - Test mode: `python harbour_bells_fix.py --bells` auditions bells only
"""

import rtmidi, time, random, math, threading, sys
from dataclasses import dataclass, field
from typing import List, Optional

# ── CONFIG ────────────────────────────────────────────────────────────────────
CH          = 2      # 0-indexed MIDI channel (AIRA default = 3 = index 2)
BELL_DECAY  = 1.0    # seconds per individual strike (buoy bell rings ~1s)
CHURCH_VOL  = 52     # Saint Martin's overall volume (quiet — far away)

# ── CC MAP ────────────────────────────────────────────────────────────────────
class CC:
    LFO_RATE     = 3;  PORTAMENTO   = 5;  VOLUME       = 7
    PW           = 15; LFO_DEPTH    = 17; SUB_LEVEL    = 19
    SAW_LEVEL    = 20; SQ_LEVEL     = 21; NOISE_LEVEL  = 23
    LFO_TO_FILT  = 25; FILTER_RES   = 71; AMP_RELEASE  = 72
    AMP_ATTACK   = 73; FILTER_CUTOFF= 74; AMP_DECAY    = 75
    REVERB_LEVEL = 91; DELAY_LEVEL  = 92; OSC_DRAW_MULT=102
    CHOP_OVER    =103; CHOP_COMB    =104

# ── BROWNIAN WALK ─────────────────────────────────────────────────────────────
@dataclass
class B:
    val: float; lo: float; hi: float; step: float
    def tick(self, bias=0.0) -> int:
        self.val += random.gauss(bias, self.step)
        self.val  = max(self.lo, min(self.hi, self.val))
        return int(round(self.val))

# ── MIDI ──────────────────────────────────────────────────────────────────────
class Midi:
    def __init__(self, hint=None):
        self._o = rtmidi.MidiOut()
        ports   = self._o.get_ports()
        print("MIDI ports:")
        for i,p in enumerate(ports): print(f"  [{i}] {p}")
        opened = False
        if hint:
            for i,p in enumerate(ports):
                if hint.lower() in p.lower():
                    self._o.open_port(i); print(f"\nOpened: {p}"); opened=True; break
        if not opened:
            for i,p in enumerate(ports):
                if any(k in p.upper() for k in ('S-1','S1','ROLAND','AIRA')):
                    self._o.open_port(i); print(f"\nAuto: {p}"); opened=True; break
        if not opened:
            self._o.open_virtual_port("S1-Harbour"); print("\nVirtual port")

    def cc(self,c,v):  self._o.send_message([0xB0|CH, c, max(0,min(127,int(v)))])
    def on(self,n,v=75): self._o.send_message([0x90|CH, n&127, max(1,min(127,v))])
    def off(self,n):    self._o.send_message([0x80|CH, n&127, 0])
    def panic(self):    self._o.send_message([0xB0|CH, 123, 0])

    def glide(self, cc_num, frm, to, dur, n=40, curve=1.0):
        for i in range(n):
            t = (i/max(1,n-1))**curve
            self.cc(cc_num, int(frm+(to-frm)*t))
            time.sleep(dur/n)

    def glide_bg(self, cc_num, frm, to, dur, curve=1.0):
        threading.Thread(target=self.glide,
                         args=(cc_num,frm,to,dur),
                         kwargs={'curve':curve}, daemon=True).start()

# ─────────────────────────────────────────────────────────────────────────────
# BELL SYNTHESIS  —  the whole point of this file
# ─────────────────────────────────────────────────────────────────────────────
#
# Self-oscillating filter as tonal generator:
#   1. Push resonance to 120 (S-1 self-oscillates between ~115-127)
#   2. Set filter cutoff = desired bell pitch
#   3. Noise burst (CC23 high momentarily) = clapper strike
#   4. AMP envelope: instant attack, long decay+release = ringing iron
#   5. MIDI note_on with low osc levels — just enough to excite the filter,
#      real pitch comes from the self-oscillating resonance peak
#
# Cutoff → approximate frequency on S-1 ACB:
#   CC74=28  →  ~60Hz   (below musical bell range, sub-rumble only)
#   CC74=38  →  ~110Hz  A2  — deep harbour buoy
#   CC74=46  →  ~185Hz  F#3 — mid harbour
#   CC74=52  →  ~277Hz  C#4 — near buoy
#   CC74=60  →  ~440Hz  A4  — church tenor
#   CC74=68  →  ~740Hz  F#5 — church soprano
#   CC74=76  →  ~1.2kHz      — bright small bell
#
# Distance model:
#   Near:    res=120, noise=100, reverb=100, vol=90
#   Distant: res=115, noise=72,  reverb=118, vol=58
#            (lower cutoff -12: air absorbs highs over water)
#            (lower resonance: bell quality smears at range)
#
# ─────────────────────────────────────────────────────────────────────────────

# Buoy definitions: (cutoff_near, label, period_sec, is_distant)
# Buoy definitions: (label, bing_cutoff, bong_cutoff, period_sec, is_distant)
# Bing and bong are NOT a clean musical interval — a swinging clapper
# hits both sides of the bell housing at whatever angle the wave dictates.
# Cutoffs kept low (34-46): buoy bells are heavy cast iron, roughly D2-E3.
# The bong is always lower than the bing (clapper loses momentum on return).
BUOYS = [
    ("deep harbour mouth",  40, 36, 17.0, False),  # ~130Hz / ~100Hz
    ("mid channel",         44, 40, 22.5, False),  # ~165Hz / ~130Hz
    ("outer fairway",       42, 37, 31.0, True),   # distant — air eats highs
    ("far roadstead",       38, 34, 42.0, True),   # barely there
]

BELL_TEMPO  = 0.52   # kept for test_bells only


def _single_strike(midi: Midi, cut: int, res: int, noise: int,
                   reverb: int, vol: int, vel: int):
    """
    Fire one clapper hit at a given filter cutoff.
    Noise burst → instant attack → ~1s decay.
    The filter's self-oscillation at `cut` gives the pitch.
    """
    midi.cc(CC.SAW_LEVEL,     0)
    midi.cc(CC.SQ_LEVEL,     10)   # tiny square helps excite resonance
    midi.cc(CC.SUB_LEVEL,     0)
    midi.cc(CC.NOISE_LEVEL,   0)
    midi.cc(CC.FILTER_CUTOFF, cut)
    midi.cc(CC.FILTER_RES,   res)
    midi.cc(CC.AMP_ATTACK,    0)   # instantaneous — clapper strike
    midi.cc(CC.AMP_DECAY,    55)   # ~1s decay (buoy bell, not church)
    midi.cc(CC.AMP_RELEASE,  68)   # tail out
    midi.cc(CC.LFO_RATE,      0)
    midi.cc(CC.LFO_DEPTH,     0)
    midi.cc(CC.LFO_TO_FILT,   0)
    midi.cc(CC.REVERB_LEVEL, reverb)
    midi.cc(CC.DELAY_LEVEL,   6)
    midi.cc(CC.VOLUME,       vol)
    time.sleep(0.025)              # patch settle

    # Clapper impact — noise spike then fast pullback
    midi.cc(CC.NOISE_LEVEL, noise)
    midi.on(60, vel)
    time.sleep(0.055)              # 55ms excitation burst
    midi.cc(CC.NOISE_LEVEL, 15)   # iron body has no noise — just resonance
    time.sleep(0.08)
    midi.off(60)


def strike_bell(midi: Midi, bing_cut: int, bong_cut: int, distant: bool,
                bell_playing: threading.Event,
                vel: int = 80, label: str = ""):
    """
    Buoy bell — always a PAIR: bing ... bong
    The clapper swings one way (bing), then returns (bong).
    Bong is quieter — less momentum on the return swing.
    The gap between them is the natural swing period: 0.35–0.7s,
    varies with wave size (bigger wave = longer swing arc = longer gap).

    Both cutoffs are set by the caller from BUOYS table.
    Decay per strike: ~1s. Total pair: ~2s + gap.
    bell_playing held for full duration.
    """
    bell_playing.set()
    try:
        res    = 114 if distant else 120
        noise  = 68  if distant else 98
        reverb = 116 if distant else 98
        vol    = 55  if distant else 88

        # Apply distance model to cutoffs (air absorbs highs over water)
        b_cut = max(22, bing_cut - 6) if distant else bing_cut
        g_cut = max(20, bong_cut - 6) if distant else bong_cut

        # ── BING ─────────────────────────────────────────────────────────
        print(f"   🔔 bing  {label}  cut={b_cut}  "
              f"{'distant' if distant else 'near'}  vel={vel}")
        _single_strike(midi, b_cut, res, noise, reverb, vol, vel)

        # Bell rings for ~1s
        time.sleep(BELL_DECAY)

        # ── Gap: clapper swinging back ────────────────────────────────────
        # Larger waves → longer arc → longer gap.  Range 0.35–0.70s
        swing_gap = random.uniform(0.35, 0.70)
        time.sleep(swing_gap)

        # ── BONG ─────────────────────────────────────────────────────────
        bong_vel = max(30, int(vel * random.uniform(0.55, 0.75)))  # quieter
        print(f"   🔔 bong  {label}  cut={g_cut}  vel={bong_vel}")
        _single_strike(midi, g_cut, res, noise, reverb, vol, bong_vel)

        # Bong rings out
        time.sleep(BELL_DECAY)

    finally:
        bell_playing.clear()


# ─────────────────────────────────────────────────────────────────────────────
# WESTMINSTER QUARTERS — St Martin-in-the-Fields, tenor D
#
# Four pitches in D major (transposed from E major standard):
#   1 = F#4  MIDI 66  cutoff 57
#   2 = E4   MIDI 64  cutoff 55
#   3 = D4   MIDI 62  cutoff 53
#   4 = A3   MIDI 57  cutoff 48
#
# Five canonical sequences (NAWCC / Wikipedia verified):
#   I   = 1 2 3 4   F#4 E4  D4  A3
#   II  = 3 1 2 4   D4  F#4 E4  A3
#   III = 3 2 1 3   D4  E4  F#4 D4
#   IV  = 1 3 2 4   F#4 D4  E4  A3
#   V   = 4 2 1 3   A3  E4  F#4 D4
#
# Each sequence: 3 quarter notes (0.91s) + 1 half note (1.82s) = 4.55s
# Tempo: 66 BPM  (stately carillon pace)
#
# The hour also tolls: D3 (MIDI 50, cutoff 40) struck once per hour.
# We catch the scene mid-sequence — could be any quarter.
# ─────────────────────────────────────────────────────────────────────────────

_WQ_CUTOFF = {1: 57, 2: 55, 3: 53, 4: 48}  # note-id → S-1 CC74 value
_WQ_NAME   = {1:'F#4', 2:'E4', 3:'D4', 4:'A3'}
_WQ_TEMPO  = 66    # BPM
_WQ_Q      = 60 / _WQ_TEMPO          # 0.909s  quarter note
_WQ_H      = _WQ_Q * 2               # 1.818s  half note

_WQ_SEQS = {
    'I':  [1,2,3,4],
    'II': [3,1,2,4],
    'III':[3,2,1,3],
    'IV': [1,3,2,4],
    'V':  [4,2,1,3],
}

# Which sequences play at each quarter-hour
_WQ_QUARTERS = {
    '15min': ['I'],
    '30min': ['II','III'],
    '45min': ['IV','V','I'],
    'hour':  ['II','III','IV','V'],
}


def _church_note(midi_out: Midi, cutoff: int, vel: int):
    """
    Strike one church bell note.
    Self-oscillating filter at cutoff = pitch.
    Instant attack — a bell strike is instantaneous.
    NO patch reconfiguration between notes — only cutoff changes.
    """
    midi_out.cc(CC.FILTER_CUTOFF, cutoff)
    time.sleep(0.032)              # 32ms for resonance to stabilise at new freq

    # Clapper impact: brief noise spike → immediate pullback
    midi_out.cc(CC.NOISE_LEVEL, 62)
    midi_out.on(60, vel)           # note 60 = carrier; pitch from filter
    time.sleep(0.055)
    midi_out.cc(CC.NOISE_LEVEL,  6)   # iron body: almost no noise, pure ring
    time.sleep(0.065)
    midi_out.off(60)


def church_bell_phrase(midi: Midi, bell_playing: threading.Event):
    """
    Westminster Quarters from St Martin-in-the-Fields, arriving through
    open water, fog, and half a mile of winter air.

    Architecture changes vs v1:
    - bell_playing held for ENTIRE PHRASE (not per-note) so wind
      automation cannot fire at all between notes
    - AMP_ATTACK = 0: instant — the defining characteristic of a bell
    - AMP_DECAY = 65 / RELEASE = 82: ring ~1.5s, clear and present
    - Patch written ONCE before phrase; only cutoff changes per note
    - Correct Westminster Quarters sequences in D major
    - Correct 3-quarter + 1-half timing at 66 BPM
    - Fog model: velocity 20-38 (quiet but present); clarity is
      wind-stolen notes, not volume-reduced notes
    """
    # Which quarter are we catching? Randomly pick a quarter-hour moment
    qtr = random.choice(list(_WQ_QUARTERS.keys()))
    sequences_to_play = _WQ_QUARTERS[qtr]

    print(f"\n   ⛪  Saint Martin's bells  ({qtr} — "
          f"sequences {', '.join(sequences_to_play)})")

    # Seize bell_playing for the WHOLE PHRASE
    bell_playing.set()
    try:
        # ── Write church bell patch ONCE ─────────────────────────────────
        # Only cutoff will change per note. Everything else stays fixed.
        midi.cc(CC.SAW_LEVEL,     0)
        midi.cc(CC.SQ_LEVEL,     12)   # tiny harmonic content to feed filter
        midi.cc(CC.SUB_LEVEL,     0)
        midi.cc(CC.NOISE_LEVEL,   0)   # start silent; bursts per note
        midi.cc(CC.FILTER_RES,  120)   # self-oscillation
        midi.cc(CC.AMP_ATTACK,    0)   # INSTANT — this is what makes it a bell
        midi.cc(CC.AMP_DECAY,    65)   # ring ~1.5s
        midi.cc(CC.AMP_RELEASE,  82)   # tail
        midi.cc(CC.LFO_RATE,      0)
        midi.cc(CC.LFO_DEPTH,     0)
        midi.cc(CC.LFO_TO_FILT,   0)
        midi.cc(CC.REVERB_LEVEL,105)   # cathedral + open water — present not drowning
        midi.cc(CC.DELAY_LEVEL,  14)   # harbour wall echo
        midi.cc(CC.VOLUME, CHURCH_VOL)
        time.sleep(0.04)               # patch settle

        # ── Play each sequence ────────────────────────────────────────────
        for seq_name in sequences_to_play:
            seq  = _WQ_SEQS[seq_name]
            print(f"       ♩ seq {seq_name}: "
                  f"{' '.join(_WQ_NAME[n] for n in seq)}")

            for i, note_id in enumerate(seq):
                cutoff = _WQ_CUTOFF[note_id]
                name   = _WQ_NAME[note_id]

                # Wind clarity — can this note reach us?
                clarity = random.betavariate(2.5, 1.2)   # mostly clear
                vel     = int(20 + clarity * 18)          # 20–38: quiet, distant

                if clarity > 0.15:
                    _church_note(midi, cutoff, vel)
                    # Note duration: quarter or half?
                    is_last = (i == len(seq) - 1)
                    dur = _WQ_H if is_last else _WQ_Q
                    print(f"         {'▪' if clarity>0.6 else '·'}  "
                          f"{name}  (cut={cutoff}  vel={vel}  "
                          f"{'half' if is_last else 'quarter'}={dur:.2f}s)")
                    time.sleep(dur)
                else:
                    # Note snatched by wind — still consume the time
                    is_last = (i == len(seq) - 1)
                    dur = _WQ_H if is_last else _WQ_Q
                    print(f"         ✗  {name}  (wind-stolen)")
                    time.sleep(dur)

            # Brief breath between sequences (the hammer mechanism resets)
            time.sleep(random.uniform(0.3, 0.6))

        # If it's the hour, toll the tenor (D3) for the hour count
        if qtr == 'hour':
            hour = random.randint(2, 5)   # We don't know what time it is
            print(f"       ⚫  Hour strike × {hour}  (D3 tenor)")
            midi.cc(CC.FILTER_CUTOFF, 40)   # D3 ≈ 147Hz
            midi.cc(CC.AMP_DECAY,     75)   # Tenor rings longer
            midi.cc(CC.AMP_RELEASE,   90)
            time.sleep(0.03)
            for h in range(hour):
                midi.cc(CC.NOISE_LEVEL, 55)
                midi.on(60, 35)
                time.sleep(0.06)
                midi.cc(CC.NOISE_LEVEL, 5)
                time.sleep(0.06)
                midi.off(60)
                time.sleep(1.8)   # Tenor rings ~1.8s between strikes

        # Final reverb tail — don't rush it
        time.sleep(4.0)
        print("   ⛪  (bells fade into the fog)")

    finally:
        bell_playing.clear()


# ─────────────────────────────────────────────────────────────────────────────
# WIND + WAVE ENGINE  (unchanged in structure, but respects bell_playing)
# ─────────────────────────────────────────────────────────────────────────────

class Harbour:
    def __init__(self, midi: Midi):
        self.m            = midi
        self.running      = False
        self.bell_playing = threading.Event()   # ← THE KEY FLAG
        self._lock        = threading.Lock()
        self._notes       = []

        # Brownian parameters
        self.w_cut  = B(48, 28, 72,  3.5)
        self.w_noi  = B(88, 65,118,  5.0)
        self.w_res  = B(14,  5, 28,  2.0)
        self.w_per  = B(10.0,7.0,14.0, 0.6)

    def _sleep(self, t):
        n = max(1, int(t/0.05))
        for _ in range(n):
            if not self.running: return
            time.sleep(t/n)

    def _on(self, n, v=72):
        self.m.on(n, v); self._notes.append(n)

    def _off(self, n):
        self.m.off(n)
        try: self._notes.remove(n)
        except ValueError: pass

    def _off_all(self):
        for n in list(self._notes): self.m.off(n)
        self._notes.clear()

    # ── Wind CC helpers (check bell_playing before every write) ────────────

    def _wind_cc(self, cc_num, val):
        """Only send wind CC if bells aren't ringing."""
        if not self.bell_playing.is_set():
            self.m.cc(cc_num, val)

    def _set_wind_patch(self):
        if self.bell_playing.is_set(): return
        self.m.cc(CC.SAW_LEVEL,   0)
        self.m.cc(CC.SQ_LEVEL,    8)
        self.m.cc(CC.SUB_LEVEL,   0)
        self.m.cc(CC.NOISE_LEVEL, int(self.w_noi.val))
        self.m.cc(CC.FILTER_CUTOFF,int(self.w_cut.val))
        self.m.cc(CC.FILTER_RES,  int(self.w_res.val))
        self.m.cc(CC.AMP_ATTACK,  82)
        self.m.cc(CC.AMP_DECAY,   60)
        self.m.cc(CC.AMP_RELEASE,108)
        self.m.cc(CC.LFO_RATE,     7)
        self.m.cc(CC.LFO_DEPTH,   28)
        self.m.cc(CC.LFO_TO_FILT, 32)
        self.m.cc(CC.REVERB_LEVEL, 82)
        self.m.cc(CC.VOLUME,       90)

    def _wind_tick(self):
        """One Brownian step on wind params — only if no bell."""
        if self.bell_playing.is_set(): return
        self._wind_cc(CC.FILTER_CUTOFF, self.w_cut.tick())
        self._wind_cc(CC.NOISE_LEVEL,   self.w_noi.tick())
        self._wind_cc(CC.FILTER_RES,    self.w_res.tick())

    def _gust(self, strength=1.0):
        if self.bell_playing.is_set(): return
        self.m.cc(CC.NOISE_LEVEL,   int(95 + strength*28))
        self.m.cc(CC.FILTER_CUTOFF, int(52 + strength*30))
        self.m.cc(CC.FILTER_RES,    int(12 + strength*22))

    def _valley(self):
        if self.bell_playing.is_set(): return
        self.m.cc(CC.NOISE_LEVEL,   62)
        self.m.cc(CC.FILTER_CUTOFF, 28)
        self.m.cc(CC.FILTER_RES,     6)

    # ── Single wave cycle ─────────────────────────────────────────────────

    def _wave(self, loud=False):
        period   = self.w_per.tick()
        strength = min(1.0, random.uniform(0.55,1.0) * (1.2 if loud else 1.0))
        vel      = int(55 + strength*30)
        swell_t  = period * 0.50
        crash_t  = 0.35
        roll_t   = period * 0.28
        sil_t    = period * 0.22 + random.uniform(-0.4,1.2)
        print(f"   ~ wave  {period:.1f}s  str={strength:.2f}")

        # Wave patch
        self.m.cc(CC.SAW_LEVEL,   0)
        self.m.cc(CC.SQ_LEVEL,    0)
        self.m.cc(CC.SUB_LEVEL,  38)
        self.m.cc(CC.NOISE_LEVEL,72)
        self.m.cc(CC.FILTER_CUTOFF,18)
        self.m.cc(CC.FILTER_RES,  6)
        self.m.cc(CC.AMP_ATTACK, 90)
        self.m.cc(CC.AMP_DECAY,  55)
        self.m.cc(CC.AMP_RELEASE,100)
        self.m.cc(CC.LFO_RATE,    3)
        self.m.cc(CC.LFO_DEPTH,   5)
        self.m.cc(CC.REVERB_LEVEL,72)
        self.m.cc(CC.VOLUME,      98)
        self._on(36, vel)

        # Swell — accelerating filter open
        steps = max(8, int(swell_t/0.25))
        for i in range(steps):
            if not self.running: break
            if self.bell_playing.is_set():
                time.sleep(swell_t/steps); continue   # skip CC, keep timing
            t_ = (i/max(1,steps-1))**0.55
            self.m.cc(CC.FILTER_CUTOFF, int(18 + t_*(55+strength*22)))
            self.m.cc(CC.SUB_LEVEL,     int(28 + t_*38))
            time.sleep(swell_t/steps)

        # Crash
        if not self.bell_playing.is_set():
            self.m.cc(CC.FILTER_CUTOFF, 98)
            self.m.cc(CC.FILTER_RES,    14)
            self.m.cc(CC.NOISE_LEVEL,   120)
            self.m.cc(CC.SUB_LEVEL,     65)
        self._sleep(crash_t)

        # Rollback — ease-out
        ns = int(120*strength)
        steps2 = max(8, int(roll_t/0.2))
        for i in range(steps2):
            if not self.running: break
            if self.bell_playing.is_set():
                time.sleep(roll_t/steps2); continue
            t_ = math.sin(i/max(1,steps2-1)*math.pi/2)
            self.m.cc(CC.FILTER_CUTOFF, int(98 - t_*80))
            self.m.cc(CC.NOISE_LEVEL,   int(ns  - t_*(ns-32)))
            time.sleep(roll_t/steps2)

        self._off(36)
        self._sleep(max(0.5, sil_t))

    # ── Bell firing (thread-safe) ─────────────────────────────────────────

    def _fire_buoy(self, idx):
        label, bing, bong, _, distant = BUOYS[idx]
        vel = random.randint(48,72) if distant else random.randint(62,88)
        strike_bell(self.m, bing, bong, distant, self.bell_playing,
                    vel=vel, label=label)

    def _fire_buoy_bg(self, idx):
        threading.Thread(target=self._fire_buoy, args=(idx,),
                         daemon=True).start()

    def _run_buoy_scheduler(self, total: float):
        """Independent timer per buoy, runs in background."""
        timers = [random.uniform(2, p) for _,_,p,_ in BUOYS]
        t, dt  = 0.0, 0.5
        while self.running and t < total:
            for i, (_,_,period,_) in enumerate(BUOYS):
                timers[i] -= dt
                if timers[i] <= 0:
                    timers[i] = period + random.uniform(-0.2,0.3)*period
                    self._fire_buoy_bg(i)
            time.sleep(dt); t += dt

    # ── MAIN PERFORMANCE ──────────────────────────────────────────────────

    def perform(self):
        self.running = True
        Wnote = 48   # Wind carrier note

        print("\n" + "═"*58)
        print("  OLD SAILOR'S HARBOUR  v2")
        print("  Ctrl-C to stop")
        print("═"*58 + "\n")

        try:
            # ── ACT I: WIND ───────────────────────────────────────────────
            print("─── I: Wind ───")
            self._set_wind_patch()
            self.m.cc(CC.VOLUME, 0)
            self._on(WOTE := WOTE if False else WOTE, 68) if False else self._on(WOTE:=48, 68)
            self.m.glide(CC.VOLUME, 0, 88, 5.0)

            for _ in range(10):
                self._wind_tick(); self._sleep(0.5)

            # First gust
            print("   ~ gust")
            self._gust(0.78); self._sleep(2.2)
            self._valley();   self._sleep(2.5)
            self._set_wind_patch()
            for _ in range(6): self._wind_tick(); self._sleep(0.5)

            # First buoy — announce it explicitly
            print("\n   [direct buoy 0 — near, deep]")
            self._off(48)
            self._fire_buoy(0)          # BLOCKING — we hear it cleanly
            self._sleep(1.0)
            self._set_wind_patch(); self._on(48, 68)
            for _ in range(8): self._wind_tick(); self._sleep(0.5)

            # Second buoy
            print("\n   [direct buoy 1 — mid channel]")
            self._off(48)
            self._fire_buoy(1)
            self._sleep(1.0)
            self._set_wind_patch(); self._on(48, 65)
            for _ in range(6): self._wind_tick(); self._sleep(0.5)

            # ── ACT II: SEA ───────────────────────────────────────────────
            print("\n─── II: Sea ───")
            self._off(48)
            self._wave(loud=False)

            # Strong gust between waves
            self._set_wind_patch(); self._on(48, 68)
            print("   ~ strong gust")
            self._gust(0.92); self._sleep(1.8)
            self._valley();   self._sleep(1.5)

            # Distant buoy 2 fires during gust valley
            print("\n   [direct buoy 2 — outer, distant]")
            self._off(48)
            self._fire_buoy(2)
            self._sleep(0.8)
            self._set_wind_patch(); self._on(48, 65)
            for _ in range(5): self._wind_tick(); self._sleep(0.5)

            self._off(48)
            self._wave(loud=True)

            # ── ACT III: HEAD TURN ────────────────────────────────────────
            print("\n─── III: Head turn / pipe ───")
            self._set_wind_patch(); self._on(48, 62)
            self._sleep(1.5)
            # Turn: wind muffles, sea opens
            print("   ↩  turning...")
            self.m.glide_bg(CC.FILTER_CUTOFF, int(self.w_cut.val), 20, 3.2, 0.7)
            self.m.glide_bg(CC.NOISE_LEVEL,   int(self.w_noi.val), 42, 3.5, 0.8)
            self.m.glide_bg(CC.REVERB_LEVEL,  82, 118, 4.0, 1.5)
            self._sleep(3.5)

            self._off(48)
            self._wave(loud=True)   # Sea loud in the newly-exposed ear

            # Pipe lighting — intimate moment
            print("   🪨  lighting pipe...")
            self.m.cc(CC.VOLUME,        38)
            self.m.cc(CC.REVERB_LEVEL,  18)
            self.m.cc(CC.FILTER_CUTOFF, 15)
            self.m.cc(CC.NOISE_LEVEL,   28)
            self._sleep(0.9)
            # Click
            for attempt in range(2):
                self.m.cc(CC.NOISE_LEVEL, 127)
                self.m.cc(CC.AMP_ATTACK,   0); self.m.cc(CC.AMP_DECAY, 3)
                self.m.on(78, 88); time.sleep(0.04); self.m.off(78)
                self._sleep(0.5 if attempt==0 else 0.2)
                if attempt == 0: self._sleep(0.8)
            print("   🔥  caught")
            self.m.glide_bg(CC.VOLUME,        38,  90, 3.5)
            self.m.glide_bg(CC.REVERB_LEVEL,  18,  88, 4.0)
            self.m.glide_bg(CC.FILTER_CUTOFF, 15,  46, 3.5)
            self._sleep(3.5)

            # ── ACT IV: SAINT MARTIN'S + BUOY SCHEDULER ──────────────────
            print("\n─── IV: Saint Martin's ───")

            # Launch buoy scheduler in background
            threading.Thread(
                target=self._run_buoy_scheduler,
                args=(90.0,), daemon=True
            ).start()

            # Wind to frame the bells
            self._set_wind_patch(); self._on(48, 55)
            for _ in range(5): self._wind_tick(); self._sleep(0.5)
            self._off(48)
            self._sleep(1.0)

            # Church bells — runs in its own thread
            # (does NOT use wind CCs so no conflict)
            church_thread = threading.Thread(
                target=church_bell_phrase,
                args=(self.m, self.bell_playing),
                daemon=True
            )
            church_thread.start()
            church_thread.join()   # Wait for phrase to complete

            # ── ACT V: FULL HARBOUR ───────────────────────────────────────
            print("\n─── V: Full harbour ───")

            for wave_i in range(3):
                if not self.running: break
                self._set_wind_patch(); self._on(48, 70)
                ticks = random.randint(10,16)
                for _ in range(ticks):
                    self._wind_tick()
                    if random.random() < 0.12:
                        s = random.uniform(0.5, 0.9)
                        print(f"   ~ gust ({s:.2f})")
                        self._gust(s); self._sleep(random.uniform(1.0,2.2))
                        self._valley(); self._sleep(0.8)
                    self._sleep(0.5)
                self._off(48)
                self._wave(loud=(wave_i==1))

            # ── FADE ──────────────────────────────────────────────────────
            print("\n─── Fade ───")
            # Final single buoy — lone, clear, unhurried
            print("   [final buoy — near, alone]")
            self._fire_buoy(0)
            self._sleep(2.0)

            self._set_wind_patch(); self._on(48, 50)
            self.m.glide_bg(CC.VOLUME,        90,  0, 14.0, 0.8)
            self.m.glide_bg(CC.FILTER_CUTOFF, 46, 12, 12.0, 1.2)
            self.m.glide_bg(CC.NOISE_LEVEL,   70, 10, 12.0)
            self._sleep(14.0)
            self._off(48)
            self._sleep(3.0)

            print("\n" + "═"*58)
            print("  Scene complete.")
            print("═"*58 + "\n")

        except KeyboardInterrupt:
            print("\n  Interrupted.\n")
        finally:
            self.running = False
            self._off_all()
            self.m.panic()
            self.m.cc(CC.VOLUME,        100)
            self.m.cc(CC.REVERB_LEVEL,   40)
            self.m.cc(CC.NOISE_LEVEL,     0)
            self.m.cc(CC.FILTER_CUTOFF,  64)
            self.m.cc(CC.FILTER_RES,      0)
            print("  S-1 restored.\n")


# ─────────────────────────────────────────────────────────────────────────────
# BELL TEST MODE  — auditions every bell sound in isolation
# Run:  python harbour_bells_fix.py --bells
# ─────────────────────────────────────────────────────────────────────────────

def test_bells(midi: Midi):
    flag = threading.Event()

    print("\n═══ BELL TEST ═══")
    print("Buoys (near):")
    for i, (label, bing, bong, period, distant) in enumerate(BUOYS):
        print(f"  [{i}] {label}  bing={bing}  bong={bong}")
        strike_bell(midi, bing, bong, False, flag, vel=82, label=label)
        time.sleep(0.8)

    print("\nBuoys (distant):")
    for i, (label, bing, bong, period, distant) in enumerate(BUOYS):
        print(f"  [{i}] {label} (distant)  bing={max(22,bing-6)}")
        strike_bell(midi, bing, bong, True, flag, vel=62, label=f"{label} (far)")
        time.sleep(0.8)

    print("\nSaint Martin's Westminster Quarters (random quarter):")
    church_bell_phrase(midi, flag)

    midi.cc(CC.VOLUME, 100)
    midi.cc(CC.FILTER_RES, 0)
    midi.cc(CC.NOISE_LEVEL, 0)
    print("═══ Test complete ═══\n")


# ─────────────────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    hint = None
    if "--list" in sys.argv:
        m = rtmidi.MidiOut()
        for i,p in enumerate(m.get_ports()): print(f"[{i}] {p}")
        sys.exit(0)

    for a in sys.argv[1:]:
        if not a.startswith("-"): hint = a

    midi = Midi(hint)

    if "--bells" in sys.argv:
        test_bells(midi)
    else:
        Harbour(midi).perform()
