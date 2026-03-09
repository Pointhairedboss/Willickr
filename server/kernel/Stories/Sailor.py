#!/usr/bin/env python3
"""
OLD SAILOR'S HARBOUR
Roland S-1 Soundscape  —  python-rtmidi MIDI stream

A blustery wind pulses in the old sailor's ears as he turns his head to
try and light his pipe. Now he can hear the waves crashing in their endless
slow and powerful rhythm — and hear the empty, far-away bell of the buoys,
different tones. The bells of Saint Martin's.

─────────────────────────────────────────────────────────────────────────────
SYNTHESIS ARCHITECTURE
─────────────────────────────────────────────────────────────────────────────

The S-1 is single-timbre ACB (SH-101). The trick is temporal interleaving:
switch the patch state, trigger a note, switch back — the reverb tail of the
bell persists in the wet path even after the patch returns to wind/wave.
This creates the illusion of simultaneous layers.

  WIND   : noise source → LPF mid-low, near-zero resonance.
           Brownian walk on cutoff/noise/resonance = organic gusting.
           Occasional resonance spike = wind whistling around a mast corner.

  WAVES  : sub osc + noise → LPF sweeping from 20 (dark swell) to 90
           (crash), then rolling back down (hiss and drawback).
           Period 7–14 seconds. Each wave has unique strength.

  BUOY BELLS : resonance near self-oscillation (filter as pitched oscillator).
           Brief noise burst excites it → rings at cutoff frequency.
           Very long amp decay+release = iron bell still ringing as wave
           passes. Four buoys, different pitches, different distances,
           different natural periods.

  ST MARTIN'S : same bell approach but higher notes, maximum reverb,
           cutoff lower (fog absorbs high harmonics), velocity very low.
           Some notes deliberately arrive as ghost/reverb-only — fog
           and wind steal them before they reach the ear.

─────────────────────────────────────────────────────────────────────────────
S-1 CC MAP  (from midi.guide/d/roland/s-1 and manual)
─────────────────────────────────────────────────────────────────────────────
  CC3  LFO Rate          CC17 LFO Depth         CC23 Noise Level
  CC5  Portamento        CC19 Sub Osc Level      CC25 LFO→Filter Amt
  CC7  Volume            CC20 Saw Osc Level      CC30 Amp Env Release(alt)
  CC15 PW / Osc Draw     CC21 Square Osc Level   CC71 Filter Resonance
  CC72 Amp Release       CC73 Amp Attack         CC74 Filter Cutoff
  CC75 Amp Decay         CC89 Reverb Type        CC91 Reverb Level
  CC90 Delay Time        CC92 Delay Level        CC102 Osc Draw Multiply
  CC103 OscChop Overtone CC104 OscChop Comb

S-1 default MIDI channel: 3  (0-indexed = 2)
─────────────────────────────────────────────────────────────────────────────
"""

import rtmidi
import time
import random
import math
import threading
import sys
from dataclasses import dataclass
from typing import Optional, List

# ── MIDI CHANNEL ──────────────────────────────────────────────────────────────
CH = 2          # 0-indexed, AIRA Compact default is ch.3

# ── S-1 CC NAMES → NUMBERS ───────────────────────────────────────────────────
class CC:
    LFO_RATE       = 3
    PORTAMENTO     = 5
    VOLUME         = 7
    PW             = 15
    LFO_DEPTH      = 17
    SUB_LEVEL      = 19
    SAW_LEVEL      = 20
    SQ_LEVEL       = 21
    NOISE_LEVEL    = 23
    LFO_TO_FILTER  = 25
    FILTER_RES     = 71
    AMP_RELEASE    = 72
    AMP_ATTACK     = 73
    FILTER_CUTOFF  = 74
    AMP_DECAY      = 75
    REVERB_LEVEL   = 91
    DELAY_LEVEL    = 92
    OSC_DRAW_MULT  = 102
    CHOP_OVERTONE  = 103
    CHOP_COMB      = 104

# ── BUOY PITCHES  (MIDI notes — also drives filter cutoff for bell timbre) ───
#   Deep harbour entrance buoy, mid-harbour, outer channel, far roadstead
BUOY_NOTES   = [33, 40, 45, 50]          # F1, E2, A2, D3
BUOY_DISTANT = [False, False, True, True]
BUOY_PERIODS = [16.5, 21.0, 28.0, 38.0]  # seconds between strikes

# ── SAINT MARTIN'S CARILLON  (Westminster quarter / Oranges & Lemons fragment)
#   (pitch, beat_count)  — some notes will be stolen by wind and fog
ST_MARTINS = [
    (64, 1.0),  # E4   ─ Lord, through this ho-ur
    (62, 1.0),  # D4
    (60, 1.5),  # C4   ─ holds
    (65, 1.0),  # F4
    (64, 1.0),  # E4
    (60, 2.0),  # C4   ─ long
    (67, 1.0),  # G4
    (65, 1.0),  # F4
    (64, 2.5),  # E4   ─ very long tail
    (60, 1.0),  # C4
    (62, 1.0),  # D4
    (64, 3.0),  # E4   ─ phrase end, huge reverb
]

BELL_TEMPO_SEC = 0.50   # ~120 BPM carillon quarter note

# ─────────────────────────────────────────────────────────────────────────────
# BROWNIAN PARAMETER  — random walks with bounds
# ─────────────────────────────────────────────────────────────────────────────

@dataclass
class Brownian:
    val: float
    lo:  float
    hi:  float
    step: float           # std-dev per tick

    def tick(self, bias: float = 0.0) -> int:
        """Gaussian step, optional mean drift, hard-clamp to [lo, hi]."""
        self.val += random.gauss(bias, self.step)
        self.val  = max(self.lo, min(self.hi, self.val))
        return int(round(self.val))

# ─────────────────────────────────────────────────────────────────────────────
# MIDI HELPERS
# ─────────────────────────────────────────────────────────────────────────────

class MidiOut:
    def __init__(self, port_hint: Optional[str] = None):
        self._out = rtmidi.MidiOut()
        ports = self._out.get_ports()
        print(f"\nAvailable MIDI ports:")
        for i, p in enumerate(ports): print(f"  [{i}] {p}")

        opened = False
        if port_hint:
            for i, p in enumerate(ports):
                if port_hint.lower() in p.lower():
                    self._out.open_port(i)
                    print(f"\nOpened: {p}\n")
                    opened = True; break

        if not opened:
            for i, p in enumerate(ports):
                if any(k in p.upper() for k in ('S-1','S1','ROLAND','AIRA')):
                    self._out.open_port(i)
                    print(f"\nAuto-opened: {p}\n")
                    opened = True; break

        if not opened:
            self._out.open_virtual_port("S1-Harbour")
            print("\nOpened virtual port: S1-Harbour\n")

    def cc(self, ctl: int, val: int):
        val = max(0, min(127, int(val)))
        self._out.send_message([0xB0 | CH, ctl, val])

    def note_on(self, note: int, vel: int = 75):
        self._out.send_message([0x90 | CH, note & 127, max(1, min(127, vel))])

    def note_off(self, note: int):
        self._out.send_message([0x80 | CH, note & 127, 0])

    def all_notes_off(self):
        self._out.send_message([0xB0 | CH, 123, 0])

    def glide(self, ctl: int, frm: int, to: int, dur: float,
              n: int = 30, curve: float = 1.0):
        """Smoothly sweep CC over dur seconds with optional power-law curve."""
        for i in range(n):
            t = i / max(1, n - 1)
            t_c = t ** curve
            self.cc(ctl, int(frm + (to - frm) * t_c))
            time.sleep(dur / n)

    def glide_async(self, ctl: int, frm: int, to: int, dur: float,
                    curve: float = 1.0):
        threading.Thread(target=self.glide,
                         args=(ctl, frm, to, dur),
                         kwargs={'curve': curve},
                         daemon=True).start()

# ─────────────────────────────────────────────────────────────────────────────
# SYNTHESIS PATCH STATES
# ─────────────────────────────────────────────────────────────────────────────

class Patches:
    """
    Each method writes a complete patch state to the S-1 via CC.
    Called before triggering notes. Some params are Brownian so states
    have variation between calls.
    """

    def __init__(self, midi: MidiOut):
        self.m = midi
        # Live Brownian parameters — persist across calls
        self.wind_cutoff  = Brownian(48, 28, 72,  3.5)
        self.wind_noise   = Brownian(88, 65, 118, 5.0)
        self.wind_res     = Brownian(14,  5,  28, 2.0)
        self.wave_period  = Brownian(10.0, 7.0, 14.0, 0.6)

    def _osc_mix(self, saw=0, sq=0, sub=0, noise=0):
        self.m.cc(CC.SAW_LEVEL,   saw)
        self.m.cc(CC.SQ_LEVEL,    sq)
        self.m.cc(CC.SUB_LEVEL,   sub)
        self.m.cc(CC.NOISE_LEVEL, noise)

    def _filter(self, cutoff, res):
        self.m.cc(CC.FILTER_CUTOFF, cutoff)
        self.m.cc(CC.FILTER_RES,    res)

    def _amp_env(self, atk, dec, rel):
        self.m.cc(CC.AMP_ATTACK,  atk)
        self.m.cc(CC.AMP_DECAY,   dec)
        self.m.cc(CC.AMP_RELEASE, rel)

    def _lfo(self, rate, depth, to_filter=0):
        self.m.cc(CC.LFO_RATE,      rate)
        self.m.cc(CC.LFO_DEPTH,     depth)
        self.m.cc(CC.LFO_TO_FILTER, to_filter)

    def _fx(self, reverb, delay=0):
        self.m.cc(CC.REVERB_LEVEL, reverb)
        self.m.cc(CC.DELAY_LEVEL,  delay)

    # ── WIND ─────────────────────────────────────────────────────────────────

    def wind(self):
        """
        Base wind: broadband noise through a wandering LPF.
        No musical pitch. The wind is the absence of order.
        Slow LFO on filter cutoff = the natural oscillation of gusts
        (Helmholtz resonance of gaps in the harbour wall, rigging vibration).
        """
        self._osc_mix(sq=6, noise=self.wind_noise.tick())
        self._filter(self.wind_cutoff.tick(), self.wind_res.tick())
        self._amp_env(atk=82, dec=60, rel=108)
        self._lfo(rate=7, depth=28, to_filter=32)
        self._fx(reverb=82, delay=0)
        self.m.cc(CC.PORTAMENTO, 0)
        self.m.cc(CC.VOLUME, 92)

    def wind_gust(self, strength: float = 1.0):
        """
        Gust: filter opens, noise rises, resonance briefly peaks.
        At strength > 0.75 you get the whistle — the wind has found a gap.
        """
        noise_peak = int(95 + strength * 28)
        cut_peak   = int(52 + strength * 30)
        res_peak   = int(12 + strength * 22)
        self.m.cc(CC.NOISE_LEVEL,   noise_peak)
        self.m.cc(CC.FILTER_CUTOFF, cut_peak)
        self.m.cc(CC.FILTER_RES,    res_peak)

    def wind_valley(self):
        """Trough between gusts. Everything closes down. Brief silence."""
        self.m.cc(CC.NOISE_LEVEL,   62)
        self.m.cc(CC.FILTER_CUTOFF, 28)
        self.m.cc(CC.FILTER_RES,    6)

    def wind_muffled(self):
        """
        Sailor has turned his head. This ear is now sheltered.
        Heavy LPF, very low noise — but reverb OPENS (you're now facing
        open water; the acoustic space has expanded behind the filter).
        """
        self.m.cc(CC.FILTER_CUTOFF, 20)
        self.m.cc(CC.FILTER_RES,    5)
        self.m.cc(CC.NOISE_LEVEL,   42)
        self.m.cc(CC.REVERB_LEVEL,  118)

    # ── WAVES ─────────────────────────────────────────────────────────────────

    def wave_swell(self):
        """
        The wave building offshore. Almost entirely sub-bass energy.
        The noise is the texture of water-surface turbulence.
        Filter starts DARK (swell = unbroken deep water) and will be
        swept open manually by the calling code.
        """
        self._osc_mix(sq=0, sub=38, noise=72)
        self._filter(cutoff=18, res=6)
        # Very slow attack — the wave takes 4-6 seconds to build
        # Medium-slow release — the hiss of drawback lasts 3-5 seconds
        self._amp_env(atk=90, dec=55, rel=100)
        self._lfo(rate=3, depth=5, to_filter=0)  # No LFO — we control filter manually
        self._fx(reverb=72, delay=8)
        self.m.cc(CC.VOLUME, 98)

    def wave_crash(self):
        """
        The break. Filter slams to maximum, noise maxes, sub spikes.
        Very brief — the crash is measured in fractions of a second.
        The calling code then sweeps everything back down.
        """
        self.m.cc(CC.FILTER_CUTOFF, 98)
        self.m.cc(CC.FILTER_RES,    14)
        self.m.cc(CC.NOISE_LEVEL,   120)
        self.m.cc(CC.SUB_LEVEL,     65)

    # ── BELLS — BUOY ─────────────────────────────────────────────────────────

    def buoy_bell(self, note: int, distant: bool = False):
        """
        Iron bell struck by wave motion. Key technique:
        Push resonance near self-oscillation → filter becomes a pitched sine
        generator. Brief noise burst excites it. It rings at the cutoff
        frequency corresponding to the note. Very long release.

        The noise level is the 'clapper weight' — heavier = louder strike.
        Distance: lower cutoff (air absorbs highs), less resonance
                  (bell quality degrades at range), more reverb (open water).
        """
        # Map MIDI note to filter cutoff
        # Buoys: F1(33) to D3(50) → filter 32 to 68
        cutoff = int(32 + (note - 33) / (50 - 33) * 36)
        cutoff = max(28, min(72, cutoff))

        if distant:
            cutoff  = max(22, cutoff - 18)   # Air absorption = low-pass
            res     = 92                      # Less crisp, more smeared
            noise   = 70                      # Quieter excitation
            reverb  = 118
            vol     = 65
        else:
            res     = 110                     # Near self-oscillation
            noise   = 90
            reverb  = 105
            vol     = 82

        self._osc_mix(sq=10, noise=noise)
        self._filter(cutoff=cutoff, res=res)
        # Instant attack (clapper is instantaneous)
        # Long decay+release (iron bell at sea — rings for seconds)
        self._amp_env(atk=0, dec=88, rel=100)
        self._lfo(rate=0, depth=0, to_filter=0)
        self._fx(reverb=reverb, delay=12)
        self.m.cc(CC.VOLUME,    vol)
        self.m.cc(CC.PORTAMENTO, 0)

    # ── BELLS — CHURCH ───────────────────────────────────────────────────────

    def church_bell(self):
        """
        Saint Martin's. Half a mile away across the water. Fog between.
        The fog is a physical low-pass filter — it absorbs anything above
        roughly 1kHz before it reaches us. The church also adds its own
        enormous reverb (stone vault, ~4 seconds RT60).
        Combined with the outdoor reverb of water and harbour walls:
        notes arrive soft, smeared, and trailing vast reverb tails.

        Some notes arrive as near-ghost — you only hear the reverb tail,
        not the attack. The attack was stolen by the wind.
        """
        self._osc_mix(sq=14, noise=55)
        self._filter(cutoff=58, res=82)       # Fog eats the highs
        self._amp_env(atk=18, dec=100, rel=122)  # Distance softens attack too
        self._lfo(rate=0, depth=0, to_filter=0)
        self._fx(reverb=126, delay=22)         # Maximum reverb — cathedral + fog
        self.m.cc(CC.VOLUME, 48)               # Quiet — it's a long way away

# ─────────────────────────────────────────────────────────────────────────────
# SOUNDSCAPE COMPOSER
# ─────────────────────────────────────────────────────────────────────────────

class HarbourScene:
    def __init__(self, midi: MidiOut, patches: Patches):
        self.m  = midi
        self.p  = patches
        self.running = False
        self._active_notes: List[int] = []
        self._patch_lock = threading.Lock()

    def _note_on(self, note: int, vel: int = 75):
        self.m.note_on(note, vel)
        self._active_notes.append(note)

    def _note_off(self, note: int):
        self.m.note_off(note)
        try: self._active_notes.remove(note)
        except ValueError: pass

    def _note_off_all(self):
        for n in list(self._active_notes):
            self.m.note_off(n)
        self._active_notes.clear()

    def _sleep(self, t: float):
        """Interruptible sleep."""
        steps = max(1, int(t / 0.05))
        for _ in range(steps):
            if not self.running: return
            time.sleep(t / steps)

    # ── WIND LAYER ────────────────────────────────────────────────────────────

    def _wind_breath(self, duration: float):
        """
        Sustain a wind note for `duration` seconds with organic Brownian
        variation on filter cutoff, resonance and noise level.
        Occasional gust events fire spontaneously.
        """
        WIND_NOTE = 48
        with self._patch_lock:
            self.p.wind()
        self._note_on(WIND_NOTE, 72)

        t = 0.0
        while self.running and t < duration:
            # Brownian tick every 0.4s
            with self._patch_lock:
                self.m.cc(CC.FILTER_CUTOFF, self.p.wind_cutoff.tick())
                self.m.cc(CC.NOISE_LEVEL,   self.p.wind_noise.tick())
                self.m.cc(CC.FILTER_RES,    self.p.wind_res.tick())

            # Spontaneous gust (15% per 0.4s ≈ ~1 per 2.7s)
            if random.random() < 0.15:
                strength = random.triangular(0.4, 1.0, 0.65)
                print(f"   ~ gust (strength {strength:.2f})")
                with self._patch_lock:
                    self.p.wind_gust(strength)
                hold = random.uniform(0.8, 3.2)
                self._sleep(hold)
                t += hold
                with self._patch_lock:
                    self.p.wind_valley()
                self._sleep(0.6)
                t += 0.6

            tick = random.uniform(0.3, 0.5)
            self._sleep(tick)
            t += tick

        self._note_off(WIND_NOTE)

    # ── WAVE LAYER ────────────────────────────────────────────────────────────

    def _single_wave(self, louder: bool = False):
        """
        One complete wave cycle:
          swell build → crash → hiss rollback → silence
        Returns total duration consumed.
        """
        WAVE_NOTE = 36     # C2 — the body of the wave
        period    = self.p.wave_period.tick()
        strength  = random.uniform(0.55, 1.0) * (1.2 if louder else 1.0)
        strength  = min(1.0, strength)
        vel       = int(55 + strength * 30)

        swell_t   = period * 0.50
        crash_t   = 0.35
        rolloff_t = period * 0.28
        silence_t = period * 0.22 + random.uniform(-0.4, 1.2)

        print(f"   ~ wave  period={period:.1f}s  strength={strength:.2f}")

        with self._patch_lock:
            self.p.wave_swell()
        self._note_on(WAVE_NOTE, vel)

        # Swell: slowly open filter (power curve — accelerates near top)
        # Sub level also rises as wave gains body
        steps  = max(8, int(swell_t / 0.25))
        for i in range(steps):
            if not self.running: break
            t_  = (i / max(1, steps-1)) ** 0.55      # Accelerating
            cut = int(18 + t_ * (55 + strength * 22))
            sub = int(28 + t_ * 38)
            self.m.cc(CC.FILTER_CUTOFF, cut)
            self.m.cc(CC.SUB_LEVEL,     sub)
            time.sleep(swell_t / steps)

        if not self.running: self._note_off(WAVE_NOTE); return

        # CRASH
        with self._patch_lock:
            self.p.wave_crash()
        self._sleep(crash_t)

        # Rollback: filter & noise fall (sine ease-out = fast start, slow end)
        noise_start = int(120 * strength)
        steps2 = max(8, int(rolloff_t / 0.2))
        for i in range(steps2):
            if not self.running: break
            t_ = (i / max(1, steps2-1))
            t_e = math.sin(t_ * math.pi / 2)  # Ease-out
            cut   = int(98 - t_e * 80)
            noise = int(noise_start - t_e * (noise_start - 32))
            self.m.cc(CC.FILTER_CUTOFF, cut)
            self.m.cc(CC.NOISE_LEVEL,   noise)
            time.sleep(rolloff_t / steps2)

        self._note_off(WAVE_NOTE)

        # Silence / foam hiss
        self._sleep(max(0.5, silence_t))
        return period

    # ── BUOY BELL ─────────────────────────────────────────────────────────────

    def _strike_buoy(self, note: int, distant: bool, vel: int = 72):
        """
        Steal the S-1 briefly for a bell strike.
        The bell's reverb tail will persist even when we return to wind/wave.
        """
        with self._patch_lock:
            self.p.buoy_bell(note, distant)
        time.sleep(0.04)   # ~40ms for patch to settle before excitation
        self._note_on(note, vel)
        time.sleep(random.uniform(0.08, 0.18))   # Brief ON — env does the work
        self._note_off(note)

    def _buoy_timeline(self, total_dur: float):
        """
        Run all buoys on independent timers for `total_dur` seconds.
        Each buoy has its own period + wave-jitter.
        Runs in its own thread.
        """
        timers = [random.uniform(0, p) for p in BUOY_PERIODS]  # Staggered starts
        t  = 0.0
        dt = 0.5

        while self.running and t < total_dur:
            for i, (note, distant, period) in enumerate(
                    zip(BUOY_NOTES, BUOY_DISTANT, BUOY_PERIODS)):
                timers[i] -= dt
                if timers[i] <= 0:
                    # Wave-driven jitter: ±20% of period
                    jitter       = random.uniform(-0.2, 0.3) * period
                    timers[i]    = period + jitter
                    vel          = random.randint(48, 80) if distant \
                                   else random.randint(58, 92)
                    label = f"[buoy {i+1}  note={note}  {'distant' if distant else 'near'}  vel={vel}]"
                    print(f"   🔔 {label}")
                    threading.Thread(target=self._strike_buoy,
                                     args=(note, distant, vel),
                                     daemon=True).start()
            time.sleep(dt)
            t += dt

    # ── SAINT MARTIN'S ────────────────────────────────────────────────────────

    def _church_bells_phrase(self):
        """
        A phrase from the St Martin's carillon, arriving through fog and wind.
        Start position is random — we catch the bells mid-phrase.
        Some notes are ghost-level (attack stolen by wind), some arrive clearly.
        """
        print("\n   ⛪  Saint Martin's bells...")
        with self._patch_lock:
            self.p.church_bell()
        time.sleep(0.1)

        start = random.randint(0, 4)
        for i in range(len(ST_MARTINS)):
            if not self.running: break
            pitch, beats = ST_MARTINS[(start + i) % len(ST_MARTINS)]

            # Clarity 0→1: how well this note survived the journey
            # Wind and fog are random; some notes arrive whole, some ghostly
            clarity = random.betavariate(2.0, 1.5)   # Right-skewed: mostly clear-ish
            vel = int(15 + clarity * 32)              # 15–47 — always quiet, far away

            if clarity > 0.2:
                self._note_on(pitch, vel)
                time.sleep(0.10)
                self._note_off(pitch)
                print(f"       {'●' if clarity > 0.6 else '○'}  "
                      f"{'CDEFGAB'[(pitch % 12 + 9) % 7]}{pitch // 12 - 1}  "
                      f"clarity={clarity:.2f}")
            else:
                # Note stolen — silence, but next note's reverb will fill
                print(f"       ·  (snatched by wind)")

            # Gap between notes — wind may steal extra time
            gap = beats * BELL_TEMPO_SEC
            if random.random() < 0.25:
                gap += random.uniform(0.3, 1.0)    # Wind buffet / hesitation
            self._sleep(gap)

        self._sleep(4.0)   # Let final reverb tail decay into the harbour

    # ── HEAD TURN  (spatial shift) ────────────────────────────────────────────

    def _head_turn(self):
        """
        The moment the sailor angles his head down to shelter the pipe-light.
        This ear turns away from the full wind.
        The sea opens ahead of him.
        Slow CC automation — takes ~3 seconds to complete.
        """
        print("\n   ↩  Head turn — sheltering pipe from wind...")
        # Wind muffles in this ear
        self.m.glide_async(CC.FILTER_CUTOFF,
                           int(self.p.wind_cutoff.val), 20, 3.2, curve=0.7)
        self.m.glide_async(CC.NOISE_LEVEL,
                           int(self.p.wind_noise.val),  42, 3.5, curve=0.8)
        # But spatial reverb expands — he's now facing open water
        self.m.glide_async(CC.REVERB_LEVEL, 82, 118, 4.0, curve=1.5)

    # ── PIPE LIGHTING ─────────────────────────────────────────────────────────

    def _light_pipe(self):
        """
        World contracts to the small cave of cupped hands.
        Two attempts with a lighter — second one catches.
        World expands again on the first draw.
        """
        print("   🪨  Lighting pipe...")

        # Cupped hands: intimacy, close space, no reverb
        self.m.cc(CC.VOLUME,        42)
        self.m.cc(CC.REVERB_LEVEL,  20)
        self.m.cc(CC.FILTER_CUTOFF, 16)
        self.m.cc(CC.NOISE_LEVEL,   30)
        self._sleep(1.0)

        # Lighter click — brief spike of noise, very short envelope
        self.m.cc(CC.NOISE_LEVEL,  127)
        self.m.cc(CC.AMP_ATTACK,     0)
        self.m.cc(CC.AMP_DECAY,      4)
        self.m.cc(CC.AMP_RELEASE,    8)
        self._note_on(75, 85)          # High note — metallic click
        time.sleep(0.04)
        self._note_off(75)
        self._sleep(0.5)

        # Blown out — frustrated pause
        self._sleep(0.8)

        # Second attempt
        self._note_on(75, 78)
        time.sleep(0.04)
        self._note_off(75)
        self._sleep(0.3)

        # Catches — small triumph
        # World expands back out: slow reverb return, filter opens
        print("   🔥  Caught. First draw.")
        self.m.glide_async(CC.VOLUME,       42, 90, 3.0)
        self.m.glide_async(CC.REVERB_LEVEL, 20, 90, 4.0)
        self.m.glide_async(CC.FILTER_CUTOFF,16, 46, 3.5)

    # ── MAIN SCENE ────────────────────────────────────────────────────────────

    def perform(self):
        """
        OLD SAILOR'S HARBOUR
        ─────────────────────
        Total runtime: ~2 minutes

        Act I   0:00–0:20  Wind establishes. First gust. First buoy.
        Act II  0:20–0:45  Waves add their voice. Second buoy. Strong gust.
        Act III 0:45–1:05  Head turn. Pipe lighting. Sea opens.
        Act IV  1:05–1:30  Saint Martin's bells arrive. Distant buoys.
        Act V   1:30–2:00  Full harbour soundscape settles. Final wave. Fade.
        """
        self.running = True
        print("\n" + "═"*60)
        print("  OLD SAILOR'S HARBOUR")
        print("  Roland S-1 Soundscape  —  Ctrl-C to stop")
        print("═"*60 + "\n")

        try:
            # ─── ACT I: WIND ESTABLISHES ─────────────────────────────────────
            print("─── ACT I: Wind ───")

            with self._patch_lock:
                self.p.wind()
            self.m.cc(CC.VOLUME, 0)
            WIND_NOTE = 48
            self._note_on(WIND_NOTE, 70)
            # Fade wind in slowly — it's been there all along
            self.m.glide(CC.VOLUME, 0, 90, 4.0)

            # Wind settles; early brownian variation
            for _ in range(8):
                if not self.running: break
                with self._patch_lock:
                    self.m.cc(CC.FILTER_CUTOFF, self.p.wind_cutoff.tick())
                    self.m.cc(CC.NOISE_LEVEL,   self.p.wind_noise.tick())
                self._sleep(0.5)

            # FIRST GUST — firm reminder of the day
            print("\n   ~ First gust (firm)")
            with self._patch_lock:
                self.p.wind_gust(strength=0.82)
            self._sleep(2.2)
            with self._patch_lock:
                self.p.wind_valley()
            self._sleep(2.8)
            with self._patch_lock:
                self.p.wind()

            # FIRST BUOY — deep, near harbour mouth
            self._note_off(WIND_NOTE)
            print("\n   🔔 First buoy — near, deep tone")
            self._strike_buoy(BUOY_NOTES[0], distant=False, vel=80)
            self._sleep(2.5)

            # Wind resumes
            with self._patch_lock:
                self.p.wind()
            self._note_on(WIND_NOTE, 70)
            for _ in range(6):
                if not self.running: break
                with self._patch_lock:
                    self.m.cc(CC.FILTER_CUTOFF, self.p.wind_cutoff.tick())
                    self.m.cc(CC.NOISE_LEVEL,   self.p.wind_noise.tick())
                self._sleep(0.5)

            # ─── ACT II: WAVES ADD THEIR VOICE ───────────────────────────────
            print("\n─── ACT II: Sea ───")
            self._note_off(WIND_NOTE)

            # Wave 1: barely there, shows the sea is present
            print("   ~ Wave 1 (gentle, establishing)")
            self._single_wave(louder=False)

            # Mid-harbour buoy during the foam hiss
            print("   🔔 Second buoy — mid harbour")
            self._strike_buoy(BUOY_NOTES[1], distant=False, vel=68)
            self._sleep(2.0)

            # Wind returns between waves
            with self._patch_lock:
                self.p.wind()
            self._note_on(WIND_NOTE, 68)
            self._sleep(2.5)

            # STRONG GUST — a real one
            print("\n   ~ Strong gust (whistle!)")
            with self._patch_lock:
                self.p.wind_gust(strength=0.94)
            self._sleep(1.5)
            with self._patch_lock:
                self.p.wind_valley()
            self._sleep(1.2)
            with self._patch_lock:
                self.p.wind()
            self._sleep(1.5)

            # Wave 2: stronger, more committed
            print("   ~ Wave 2 (stronger)")
            self._note_off(WIND_NOTE)
            self._single_wave(louder=False)

            # ─── ACT III: HEAD TURN + PIPE ────────────────────────────────────
            print("\n─── ACT III: Head turn / pipe ───")

            # Wind note for the transition
            with self._patch_lock:
                self.p.wind()
            self._note_on(WIND_NOTE, 65)
            self._sleep(1.5)

            # HEAD TURN — the world changes
            self._head_turn()
            self._sleep(3.5)   # Time for the transition CCs to complete

            # Wave 3 — now facing the sea directly: LOUD, present
            print("   ~ Wave 3 (facing sea now — full presence)")
            self._note_off(WIND_NOTE)
            self._single_wave(louder=True)

            # PIPE during drawback
            self._light_pipe()
            self._sleep(3.0)    # Glides finishing

            # ─── ACT IV: SAINT MARTIN'S ──────────────────────────────────────
            print("\n─── ACT IV: Saint Martin's ───")

            # Start the buoy background thread now
            buoy_thread = threading.Thread(
                target=self._buoy_timeline,
                args=(70.0,),
                daemon=True
            )
            buoy_thread.start()

            # Brief wind to frame the bells
            with self._patch_lock:
                self.p.wind()
            self._note_on(WIND_NOTE, 58)
            self._sleep(2.0)
            self._note_off(WIND_NOTE)
            self._sleep(0.5)

            # Church bells — fragmented arrival
            self._church_bells_phrase()

            # ─── ACT V: FULL HARBOUR ─────────────────────────────────────────
            print("\n─── ACT V: Full harbour ───")

            with self._patch_lock:
                self.p.wind()
            self._note_on(WIND_NOTE, 72)

            # Wind + wave alternating, buoys firing in background
            for wave_num in range(3):
                if not self.running: break
                # Wind interval
                for _ in range(12):
                    if not self.running: break
                    with self._patch_lock:
                        self.m.cc(CC.FILTER_CUTOFF, self.p.wind_cutoff.tick())
                        self.m.cc(CC.NOISE_LEVEL,   self.p.wind_noise.tick())
                    self._sleep(0.45)
                # Occasional gust
                if random.random() < 0.6:
                    s = random.uniform(0.5, 0.9)
                    print(f"   ~ Gust (s={s:.2f})")
                    with self._patch_lock:
                        self.p.wind_gust(s)
                    self._sleep(random.uniform(1.0, 2.5))
                    with self._patch_lock:
                        self.p.wind_valley()
                    self._sleep(1.0)

                # Wave
                self._note_off(WIND_NOTE)
                print(f"   ~ Wave {wave_num + 4}")
                self._single_wave(louder=(wave_num == 1))
                with self._patch_lock:
                    self.p.wind()
                self._note_on(WIND_NOTE, 68)
                self._sleep(1.5)

            # ─── FINAL BUOY + FADE ────────────────────────────────────────────
            print("\n─── Fade ───")
            self._note_off(WIND_NOTE)

            # One last deep buoy — alone
            print("   🔔 Final buoy (near, deep)")
            self._strike_buoy(BUOY_NOTES[0], distant=False, vel=65)
            self._sleep(3.0)

            # Wind one last time — quiet, fading
            with self._patch_lock:
                self.p.wind()
            self._note_on(WIND_NOTE, 55)
            self.m.cc(CC.NOISE_LEVEL, 55)
            self.m.cc(CC.FILTER_CUTOFF, 35)

            # Slow fade: volume + filter close together
            self.m.glide_async(CC.VOLUME,       90,  0, 12.0, curve=0.8)
            self.m.glide_async(CC.FILTER_CUTOFF, 35, 12, 10.0, curve=1.2)
            self.m.glide_async(CC.NOISE_LEVEL,   55, 10, 10.0)
            self._sleep(12.0)

            self._note_off(WIND_NOTE)
            self._sleep(2.0)   # Final reverb tail

            print("\n═"*60)
            print("  Scene complete.")
            print("═"*60 + "\n")

        except KeyboardInterrupt:
            print("\n\n  Interrupted.\n")

        finally:
            self.running = False
            self._note_off_all()
            self.m.all_notes_off()
            # Restore neutral state
            self.m.cc(CC.VOLUME,        100)
            self.m.cc(CC.REVERB_LEVEL,   40)
            self.m.cc(CC.NOISE_LEVEL,     0)
            self.m.cc(CC.FILTER_CUTOFF,  64)
            self.m.cc(CC.FILTER_RES,      0)
            print("  MIDI released. S-1 restored to neutral.\n")

# ─────────────────────────────────────────────────────────────────────────────
# ENTRY POINT
# ─────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":
    hint = None
    if "--list" in sys.argv:
        m = rtmidi.MidiOut()
        for i, p in enumerate(m.get_ports()):
            print(f"[{i}] {p}")
        sys.exit(0)
    for arg in sys.argv[1:]:
        if not arg.startswith("-"):
            hint = arg

    midi    = MidiOut(hint)
    patches = Patches(midi)
    scene   = HarbourScene(midi, patches)
    scene.perform()