#!/usr/bin/env python3
"""
AGENT GAMMA-K (KEYS/PLUCKED) — PATCH 002: "The Theoretical Acoustic Guitar"
Source: SyntheoryGordonReid - Chapter 27-29 (Synthesizing Plucked Strings)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Pluck] + [Behavior: Decaying] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Plucked-String]

Theory Implemented:
  1. The Pluck Transient: When a string is plucked, the initial transient contains nearly all possible harmonics (very bright),
     but these upper harmonics decay significantly faster than the fundamental. 
  2. Filter Envelope Mapping: To simulate the rapid decay of upper partials, the Filter Envelope is set to a completely 
     different curve than the Amplifier Envelope. The Filter snaps down in ~150ms, while the AMP sustains the fundamental 
     for several seconds.
  3. Harmonic Profile: A plucked string has strong even and odd harmonics. We blend Sawtooth (all harmonics) 
     with Square (odd harmonics) mixed slightly lower.

Usage:
    python gamma_k_guitar_1.py
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

    def init_synth_primitive(self, s1: Midi):

        print("Agent Gamma-K: Initializing 'The Theoretical Acoustic Guitar' patch...")
    
        # 1. Base Core
        s1.cc(CC.SAW_LEVEL, 127)     # Rich in all harmonics
        s1.cc(CC.OSC_SQUARE, 60)     # Emphasis on odd harmonics
        s1.cc(CC.SUB_LEVEL, 40)      # Solid fundamental (the guitar body)
    
        # 2. The Pluck Mechanics (Filter Envelope)
        s1.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 0, 45))  # Rest state is heavily muted
        s1.cc(CC.FILTER_ENV, 100)    # Massive envelope depth to open the filter on the pluck
        s1.cc(CC.FILTER_RES, 30)     # Slight bump
    
        # S-1 uses shared envelopes, so we must compromise:
        s1.cc(CC.AMP_ATTACK, 0)      # Instant Plectrum/Fingernail strike
        s1.cc(CC.AMP_DECAY, 65)      # Moderately slow decay
        s1.cc(CC.AMP_SUSTAIN, 0)     # A plucked string never holds a sustain level; it constantly decays to 0
        s1.cc(CC.AMP_RELEASE, 55)    # Ring out length
    
        # 3. Performance Elements
        s1.cc(CC.LFO_RATE, 65)       
        s1.cc(CC.PITCH, 0)           # Guitars generally do not have LFO pitch wobble unless bending
        s1.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))   # Acoustic body resonance
        s1.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
        s1.cc(CC.DELAY_LEVEL, 0)
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-K: Playing acoustic guitar arpeggio. Listen to the bright pluck decay.")
    
        # Em "Travis Picking" Pattern
        pattern = [
            40, 47, 52, 47, 55, 47, 52, 47  # E2, B2, E3, B2, G3, B2, E3, B2
        ]
    
        try:
            while True:
                for note in pattern:
                    midi.on(note, 90)
                    time.sleep(0.2)
                    midi.off(note)
                    time.sleep(0.05)
        except KeyboardInterrupt:
            print("\nAgent Gamma-K: Halting pattern.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
