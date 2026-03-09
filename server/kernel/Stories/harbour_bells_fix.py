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
BELL_DECAY  = 3.2    # seconds to hold patch lock after bell strike
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
BUOYS = [
    (38, "deep harbour mouth",  17.0, False),
    (46, "mid channel",         22.5, False),
    (50, "outer fairway",       31.0, True),
    (44, "far roadstead",       42.0, True),
]

# Saint Martin's — fragment (Oranges & Lemons / Westminster quarter hybrid)
# (cutoff, beat_dur, label)
ST_MARTINS_MELODY = [
    (60, 0.9,  "C"),   # 440Hz  A4-ish
    (58, 0.9,  "B"),   # 370Hz
    (56, 1.4,  "G#"),  # 311Hz  — held
    (62, 0.9,  "D"),   # 555Hz
    (60, 0.9,  "C"),
    (56, 1.8,  "G#"),  # held longer
    (64, 0.9,  "E"),   # 698Hz
    (62, 0.9,  "D"),
    (60, 2.5,  "C"),   # phrase-end hold
    (56, 0.9,  "G#"),
    (58, 0.9,  "B"),
    (60, 3.5,  "C"),   # final — enormous reverb tail
]

BELL_TEMPO = 0.52   # seconds per beat unit


def strike_bell(midi: Midi, cutoff: int, distant: bool,
                bell_playing: threading.Event,
                vel: int = 80, label: str = ""):
    """
    The complete bell strike sequence. Holds its own time.
    Sets bell_playing for the full BELL_DECAY duration so
    wind automation freezes completely.
    """
    bell_playing.set()
    try:
        res    = 115 if distant else 120
        noise  = 72  if distant else 100
        reverb = 118 if distant else 100
        vol    = 58  if distant else 90
        cut    = max(22, cutoff - 12) if distant else cutoff

        # ── Full patch write ──────────────────────────────────────────────
        midi.cc(CC.SAW_LEVEL,    0)
        midi.cc(CC.SQ_LEVEL,    12)    # Tiny sq to help excite filter
        midi.cc(CC.SUB_LEVEL,    0)
        midi.cc(CC.NOISE_LEVEL,  0)    # Start at 0; we'll burst it below
        midi.cc(CC.FILTER_CUTOFF, cut)
        midi.cc(CC.FILTER_RES,   res)
        midi.cc(CC.AMP_ATTACK,   0)    # Instant — clapper is instantaneous
        midi.cc(CC.AMP_DECAY,   92)    # Long — iron bell rings
        midi.cc(CC.AMP_RELEASE,110)    # Very long tail
        midi.cc(CC.LFO_RATE,     0)
        midi.cc(CC.LFO_DEPTH,    0)
        midi.cc(CC.LFO_TO_FILT,  0)
        midi.cc(CC.REVERB_LEVEL, reverb)
        midi.cc(CC.DELAY_LEVEL,   8)
        midi.cc(CC.VOLUME,       vol)
        time.sleep(0.03)               # Let patch settle

        # ── Noise BURST = clapper strike ──────────────────────────────────
        # Big spike then immediate fallback — clapper is brief
        midi.cc(CC.NOISE_LEVEL, noise)
        midi.on(60, vel)               # Note 60 as carrier (filter gives pitch)
        time.sleep(0.06)               # 60ms burst
        midi.cc(CC.NOISE_LEVEL,  20)   # Pull noise back — body of bell has no noise
        time.sleep(0.10)
        midi.off(60)

        print(f"   🔔 {label}  cut={cut}  res={res}  "
              f"{'distant' if distant else 'near'}  vel={vel}")

        # ── Hold bell state for full decay ────────────────────────────────
        # Wind must NOT touch these CCs during this time
        time.sleep(BELL_DECAY)

    finally:
        bell_playing.clear()


def church_bell_phrase(midi: Midi, bell_playing: threading.Event):
    """
    Saint Martin's arrives through fog and water.
    Runs in its own thread. Each note checks fog/wind clarity randomly.
    """
    print("\n   ⛪  Saint Martin's bells across the water...")

    # Start mid-phrase (we catch it in progress, as you would in real life)
    start = random.randint(0, 5)

    for i in range(len(ST_MARTINS_MELODY)):
        if not bell_playing.is_set():
            bell_playing.set()
        try:
            cut, dur, name = ST_MARTINS_MELODY[(start+i) % len(ST_MARTINS_MELODY)]

            # ── Fog and distance patch ────────────────────────────────────
            midi.cc(CC.SAW_LEVEL,    0)
            midi.cc(CC.SQ_LEVEL,    10)
            midi.cc(CC.SUB_LEVEL,    0)
            midi.cc(CC.NOISE_LEVEL, 40)
            midi.cc(CC.FILTER_CUTOFF, cut)
            midi.cc(CC.FILTER_RES,  118)   # Fog smears resonance slightly
            midi.cc(CC.AMP_ATTACK,   22)   # Soft — distance rounds the attack
            midi.cc(CC.AMP_DECAY,   105)
            midi.cc(CC.AMP_RELEASE, 120)
            midi.cc(CC.LFO_RATE,     0)
            midi.cc(CC.LFO_DEPTH,    0)
            midi.cc(CC.REVERB_LEVEL,126)   # Maximum — cathedral + open water
            midi.cc(CC.DELAY_LEVEL,  20)   # Subtle echo (harbour walls)
            midi.cc(CC.VOLUME, CHURCH_VOL)
            time.sleep(0.025)

            # Wind clarity — beta distribution, mostly clear-ish
            clarity = random.betavariate(2.2, 1.4)
            vel     = int(14 + clarity * 28)  # 14–42: always quiet

            if clarity > 0.18:
                midi.cc(CC.NOISE_LEVEL, 35)
                midi.on(60, vel)
                time.sleep(0.05)
                midi.cc(CC.NOISE_LEVEL, 12)
                time.sleep(0.08)
                midi.off(60)
                marker = "●" if clarity > 0.65 else "○"
                print(f"       {marker}  {name}  (cut={cut}  "
                      f"vel={vel}  clarity={clarity:.2f})")
            else:
                print(f"       ·  {name}  (snatched by wind)")

        finally:
            bell_playing.clear()

        # Inter-note gap — occasionally wind steals extra time
        gap = dur * BELL_TEMPO
        if random.random() < 0.20:
            gap += random.uniform(0.3, 0.9)
        time.sleep(gap)

    time.sleep(5.0)   # Final reverb tail hangs in the air
    print("   ⛪  (bells fade into fog)")


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
        cut, label, _, distant = BUOYS[idx]
        vel = random.randint(48,78) if distant else random.randint(60,90)
        strike_bell(self.m, cut, distant, self.bell_playing,
                    vel=vel, label=f"buoy: {label}")

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
    for i, (cut, label, period, distant) in enumerate(BUOYS):
        print(f"  [{i}] {label}  cut={cut}")
        strike_bell(midi, cut, False, flag, vel=82, label=label)
        time.sleep(1.5)

    print("\nBuoys (distant):")
    for i, (cut, label, period, distant) in enumerate(BUOYS):
        print(f"  [{i}] {label} (distant)  cut={max(22,cut-12)}")
        strike_bell(midi, cut, True, flag, vel=65, label=f"{label} (far)")
        time.sleep(1.5)

    print("\nSaint Martin's phrase:")
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
