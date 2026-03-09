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
    AMP_SUSTAIN  = 70  # CC70 = sustain level on Roland S-1
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

# ─────────────────────────────────────────────────────────────────────────────
# BUOY BELL DEFINITIONS
#
# (label, bing_note, bong_note, period_sec, is_distant)
#
# Pitch from the VCO — MIDI note number controls oscillator pitch directly.
# The filter is a tone shaper (open), NOT the sound source.
# Self-oscillation = OFF. That's what caused the laser/video-game sound:
# the resonant filter sweeps as it locks pitch = pew pew.
#
# Buoy bells = heavy cast iron, D2-G3 range, dull and hollow.
# Bing/bong = clapper swings both ways; bong is 4-7 semitones lower,
# NOT a clean musical interval — whatever the swing arc gives.
# ─────────────────────────────────────────────────────────────────────────────
BUOYS = [
    ("deep harbour mouth",  50, 46, 17.0, False),  # D3 / Bb2
    ("mid channel",         55, 51, 22.5, False),  # G3 / Eb3
    ("outer fairway",       47, 43, 31.0, True),   # B2 / G2  (distant)
    ("far roadstead",       43, 39, 42.0, True),   # G2 / Eb2 (barely there)
]


def _bell_patch(midi: Midi, vol: int, reverb: int, decay: int, release: int):
    """
    Write the bell patch to the S-1.
    Square wave VCO → fairly open filter → instant-attack percussive envelope.
    Resonance 55 adds bronze/iron brightness WITHOUT self-oscillating.
    """
    midi.cc(CC.SAW_LEVEL,     0)
    midi.cc(CC.SQ_LEVEL,     70)   # square = hollow cast iron / bronze character
    midi.cc(CC.SUB_LEVEL,     0)
    midi.cc(CC.NOISE_LEVEL,   8)   # tiny transient for clapper impact
    midi.cc(CC.FILTER_CUTOFF, 90)  # open — let the harmonics through
    midi.cc(CC.FILTER_RES,   55)   # brightens the tone, no self-oscillation
    midi.cc(CC.AMP_ATTACK,    0)   # INSTANT — a bell strike is instantaneous
    midi.cc(CC.AMP_DECAY,   decay) # controls the ring duration
    midi.cc(CC.AMP_SUSTAIN,   0)   # no sustain — pure decay shape
    midi.cc(CC.AMP_RELEASE, release)
    midi.cc(CC.LFO_RATE,      0)
    midi.cc(CC.LFO_DEPTH,     0)
    midi.cc(CC.LFO_TO_FILT,   0)
    midi.cc(CC.REVERB_LEVEL, reverb)
    midi.cc(CC.DELAY_LEVEL,   8)
    midi.cc(CC.VOLUME,       vol)
    time.sleep(0.025)


def _bell_strike(midi: Midi, note: int, vel: int):
    """Strike one bell note. Pitch = MIDI note (VCO). Short gate — env does the work."""
    midi.on(note, vel)
    time.sleep(0.04)   # 40ms gate — just enough to trigger envelope
    midi.off(note)


def strike_bell(midi: Midi, bing_note: int, bong_note: int, distant: bool,
                bell_playing: threading.Event,
                vel: int = 80, label: str = ""):
    """
    Buoy bell pair: bing ... bong.
    Clapper swings one way (bing), returns on backswing (bong).
    Bong is 55-70% velocity — clapper loses momentum on return.
    bell_playing held for full pair duration so wind doesn't interfere.
    """
    bell_playing.set()
    try:
        if distant:
            vol, reverb = 52, 112
            vel = max(28, int(vel * 0.62))
        else:
            vol, reverb = 82, 90

        # ── BING ─────────────────────────────────────────────────────────
        _bell_patch(midi, vol=vol, reverb=reverb, decay=52, release=65)
        print(f"   🔔 bing  {label}  note={bing_note}  "
              f"{'distant' if distant else 'near'}  vel={vel}")
        _bell_strike(midi, bing_note, vel)

        # Bell rings ~1s, then clapper swings back
        time.sleep(BELL_DECAY)
        swing_gap = random.uniform(0.35, 0.65)
        time.sleep(swing_gap)

        # ── BONG ─────────────────────────────────────────────────────────
        bong_vel = max(22, int(vel * random.uniform(0.55, 0.70)))
        print(f"   🔔 bong  {label}  note={bong_note}  vel={bong_vel}")
        _bell_strike(midi, bong_note, bong_vel)
        time.sleep(BELL_DECAY)

    finally:
        bell_playing.clear()



# ─────────────────────────────────────────────────────────────────────────────
# WESTMINSTER QUARTERS — St Martin-in-the-Fields (tenor in D)
#
# The four pitches in D major (transposed down 2 semitones from E major std):
#   Note 1 = F#4  MIDI 66  (highest quarter bell)
#   Note 2 = E4   MIDI 64
#   Note 3 = D4   MIDI 62
#   Note 4 = A3   MIDI 57  (lowest quarter bell)
#
# Five canonical sequences (Wikipedia / NAWCC verified):
#   I   = [1,2,3,4]   F#4 E4  D4  A3
#   II  = [3,1,2,4]   D4  F#4 E4  A3
#   III = [3,2,1,3]   D4  E4  F#4 D4
#   IV  = [1,3,2,4]   F#4 D4  E4  A3
#   V   = [4,2,1,3]   A3  E4  F#4 D4
#
# Each sequence: 3 quarter notes + 1 half note at 66 BPM
# (0.909s quarter, 1.818s half = 4.545s per sequence)
# ─────────────────────────────────────────────────────────────────────────────

# ─────────────────────────────────────────────────────────────────────────────
# ORANGES AND LEMONS — "You owe me five farthings, say the bells of St Martin's"
#
# This is NOT the Westminster Quarters. It's a fragment of one of the oldest
# London nursery rhymes (c.1744), where each church's bells "speak" a line.
# St Martin's line: "You owe me five farthings / Say the bells of St Martin's"
#
# Source melody (noobnotes.net / traditional): in C major upper octave —
#   "You owe me five far-things": G G E G E C
#   "Say the bells of St Mar-tin's": D E F D G E C
#
# Transposed to G major (mid-low range, warmer for bells):
#   C→G4(67)  D→A4(69)  E→B4(71)  F→C5(72)  G→D5(74)
#
#   "You owe me five farthings":    D5 D5 B4 D5 B4 G4
#   MIDI:                           74 74 71 74 71 67
#   Rhythm:                          q  q  q  q  q  h
#
#   "Say the bells of St Martin's": A4 B4 C5 A4 D5 B4 G4
#   MIDI:                           69 71 72 69 74 71 67
#   Rhythm:                          q  q  q  q  q  q  h
#
# The C5 (natural 4th in G) gives it that slightly unsettled, haunting
# quality — not quite wrong, not quite comfortable.
#
# Tempo: 72 BPM  (slow and tolling)
# ─────────────────────────────────────────────────────────────────────────────

_OL_BPM = 72
_OL_Q   = 60 / _OL_BPM   # 0.833s  quarter note
_OL_H   = _OL_Q * 2      # 1.667s  half note

# (MIDI note, duration, syllable label)
_OL_PHRASE1 = [
    (74, _OL_Q, "You"),
    (74, _OL_Q, "owe"),
    (71, _OL_Q, "me"),
    (74, _OL_Q, "five"),
    (71, _OL_Q, "far-"),
    (67, _OL_H, "thiiings"),
]
_OL_PHRASE2 = [
    (69, _OL_Q, "Say"),
    (71, _OL_Q, "the"),
    (72, _OL_Q, "bells"),   # ← C5: that slightly-off note, the haunting one
    (69, _OL_Q, "of"),
    (74, _OL_Q, "Saint"),
    (71, _OL_Q, "Mar-"),
    (67, _OL_H, "tin's..."),
]


def church_bell_phrase(midi: Midi, bell_playing: threading.Event):
    """
    "You owe me five farthings, say the bells of St Martin's."
    Oranges and Lemons, trad. English nursery rhyme, c.1744.

    Heard across open water from the old city: fragmentary, slow, haunting.
    Wind may snatch individual notes. The phrase sometimes arrives complete,
    sometimes only the resolution — the "tin's" hanging alone in the dark.

    Synthesis: VCO square wave, MIDI note = pitch, open filter.
    Resonance 58 for bronze warmth. NO self-oscillation.
    bell_playing held for full phrase.
    """
    # Decide how much of the phrase arrives:
    #   full  = both lines
    #   half  = just phrase 2 (we missed the first, or wind ate it)
    #   twice = heard twice (clock is repeating, we're catching it mid-cycle)
    arrival = random.choices(
        ['full', 'half', 'twice'],
        weights=[0.55, 0.30, 0.15]
    )[0]

    phrases_to_play = {
        'full':  [_OL_PHRASE1, _OL_PHRASE2],
        'half':  [_OL_PHRASE2],
        'twice': [_OL_PHRASE1, _OL_PHRASE2, _OL_PHRASE1, _OL_PHRASE2],
    }[arrival]

    print(f"\n   ⛪  St Martin's bells  ({arrival})")

    bell_playing.set()
    try:
        # Bell patch — bronze church bell, warmer than buoys
        midi.cc(CC.SAW_LEVEL,     0)
        midi.cc(CC.SQ_LEVEL,     65)
        midi.cc(CC.SUB_LEVEL,     0)
        midi.cc(CC.NOISE_LEVEL,   5)   # tiny transient only
        midi.cc(CC.FILTER_CUTOFF, 82)  # fairly open
        midi.cc(CC.FILTER_RES,   58)   # warmth and ring, no self-osc
        midi.cc(CC.AMP_ATTACK,    0)   # instant — always for bells
        midi.cc(CC.AMP_DECAY,    68)   # ~1.8s bronze ring
        midi.cc(CC.AMP_SUSTAIN,   0)
        midi.cc(CC.AMP_RELEASE,  80)
        midi.cc(CC.LFO_RATE,      0)
        midi.cc(CC.LFO_DEPTH,     0)
        midi.cc(CC.LFO_TO_FILT,   0)
        midi.cc(CC.REVERB_LEVEL,112)   # stone tower + open water
        midi.cc(CC.DELAY_LEVEL,  14)   # harbour echo off the walls
        midi.cc(CC.VOLUME, CHURCH_VOL)
        time.sleep(0.03)

        for phrase in phrases_to_play:
            for note, dur, syllable in phrase:
                # Wind clarity — betavariate: usually present, occasionally stolen
                clarity = random.betavariate(2.8, 1.1)
                vel = int(20 + clarity * 22)   # 20–42: distant, never loud

                if clarity > 0.18:
                    midi.on(note, vel)
                    time.sleep(0.04)
                    midi.off(note)
                    marker = '▪' if clarity > 0.65 else '·'
                    print(f"         {marker}  {syllable:10s}  "
                          f"MIDI {note}  vel={vel}  {dur:.2f}s")
                else:
                    print(f"         ✗  {syllable:10s}  (wind-stolen)")

                time.sleep(dur)

            # Breath between phrases — the bell mechanism pausing
            time.sleep(random.uniform(0.4, 0.9))

        # Final note lingers longer than usual — reverb across open water
        time.sleep(4.0)
        print("   ⛪  (...farthings...)")

    finally:
        bell_playing.clear()


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
