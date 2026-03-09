#!/usr/bin/env python3
"""
AGENT GAMMA-K (KEYS/ORGANS) — PATCH 001: "The Tonewheel Drawbar Foundation"
Source: SyntheoryGordonReid - Chapter 53-54 (Synthesizing Tonewheel Organs)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Friction] + [Behavior: Static] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Organ-Emulation]

Theory Implemented:
  1. Additive Approximation: A true Hammond B3 uses 9 drawbars (sine waves at specific harmonic intervals). 
     The S-1 is subtractive, so we cannot do true 9-partial additive synthesis. However, we can use the Sub-Oscillator
     and the primary Square wave to emulate the fundamental and the 1st odd harmonic (the 8' and 16' drawbars), 
     creating the thick foundation of an organ patch.
  2. The Key Click: The signature Hammond "spit" or "click" occurs due to the mechanical busbars engaging. 
     We simulate this with a sharp, lightning-fast pitch-envelope transient or by using the filter envelope 
     wide open with zero sustain and a 5ms decay to inject an immediate transient "pop" before the main body speaks.
  3. Continuous Sustains: Organ envelopes do not decay while held; they are strictly on/off gates. 

Usage:
    python gamma_k_tonewheel_1.py
"""

import sys
import time
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge


class GammaAcousticCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME,
            "afo:ModulationRate": CC.LFO_RATE
        }

    def init_synth_primitive(self, midi: Midi):

        print("Agent Gamma-K: Initializing 'The Tonewheel Drawbar Foundation' patch...")
    
        # 1. Harmonic Foundation (8' and 16' Drawbar Approximation)
        # A B3 uses pure sines. We use the Square (odd harmonics) mixed with a 
        # tuned Sub-Oscillator (octave down fundamental) and filter it heavily to remove buzz.
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 80)     # The 8' Drawbar
        midi.cc(CC.SUB_LEVEL, 110)     # The 16' Drawbar (Octave below)
        midi.cc(CC.NOISE_LEVEL, 5)     # Very slight mechanical floor
    
        # 2. Additive Smoothing (Using the Filter to fake Sine Waves)
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 15, 75))  # Roll off all the abrasive highs of the Square wave to make it sound like a Sine
        midi.cc(CC.FILTER_RES, 0)      # No resonance, we want a flat, pure tone
    
        # 3. The "Key Click" Envelope Transient
        # We use the filter envelope to create a 5ms "burst" of upper harmonics right at the attack phase
        midi.cc(CC.FILTER_ENV, 85)     # Heavy envelope depth
        midi.cc(CC.AMP_ATTACK, 0)      # Instant On
        midi.cc(CC.AMP_DECAY, 5)       # The Click: 5ms to snap the filter closed 
        midi.cc(CC.AMP_SUSTAIN, 100)   # Continuous hold
        midi.cc(CC.AMP_RELEASE, 5)     # Instant Off
    
        # 4. Vibrato / Chorus Simulation (The Leslie Rotary Speaker Lite)
        midi.cc(CC.LFO_RATE, 65)       # Standard Vibrato speed
        midi.cc(CC.LFO_MODE, 0)        # Normal mode
        midi.cc(CC.PITCH, 10)          # Subtle pitch wobble
        midi.cc(CC.CHORUS_LEVEL, 80)   # Heavy chorus to simulate the rotary cabinet spin
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-K: Playing organ progression. Note the key-click transient.")
    
        # Classic Gospel/Soul progression: I -> IV -> V
        chords = [
            [60, 64, 67, 72], # C Maj (Inversion)
            [65, 69, 72, 77], # F Maj (Inversion)
            [67, 71, 74, 79], # G Maj 
            [60, 64, 67, 72]  # C Maj
        ]
    
        try:
            for chord in chords:
                print(f"Chord: {chord}")
                for note in chord:
                    midi.on(note, 80)
                time.sleep(1.2)
                for note in chord:
                    midi.off(note)
                time.sleep(0.1) # Simulate fingers lifting off the unweighted keys
            
        except KeyboardInterrupt:
            print("\nAgent Gamma-K: Halting seq.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
