#!/usr/bin/env python3
"""
AGENT GAMMA-P (PERCUSSION) — PATCH 002: "The Realistic Cymbal"
Source: SyntheoryGordonReid - Chapter 36/37 (Synthesizing Realistic Cymbals)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Cymbal-Emulation]

Theory Implemented:
  1. Inharmonicity: A genuine cymbal consists of hundreds of wildly inharmonic overtones. Since true additive 
     is impossible, we emulate the TR-808 approach: combining a Square wave with a detuned audio-rate LFO 
     modulating pitch (pseudo-FM) to create a chaotic, metallic mess of sidebands.
  2. The Noise Floor: We heavily mix in White Noise (CC23) along with the oscillators to simulate the "shatter" 
     of the brass.
  3. High-Pass Filter Role: Cymbals contain almost no low frequencies. We drive the cutoff high and use resonance 
     to "ring" specific upper-mid nodes.
  4. Envelopes: A cymbal requires a 0ms attack and an extremely long, linear decay/release (simulating the physical ring-out).

Usage:
    python gamma_p_cymbal_1.py
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

        print("Agent Gamma-P: Initializing 'The Realistic Cymbal' patch...")
    
        # 1. Base Metallic Hash
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.SUB_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 127)    # Core harsh oscillator
        midi.cc(CC.NOISE_LEVEL, 127)   # Maximum noise to shatter the square
    
        # 2. Pseudo-FM (The 808 6-Oscillator Fake)
        midi.cc(CC.LFO_RATE, 127)      # 140Hz hardcap for max sidebands
        midi.cc(CC.LFO_MODE, 127)      # Fast mode
        midi.cc(CC.PITCH, 45)          # Bleed the LFO into pitch to ruin the pure square harmonic
    
        # 3. Filtering (Removing the body)
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 75, 127)) # Extreme High Pass simulation (via standard low pass opened wide + no lows from sub)
        midi.cc(CC.FILTER_RES, 80)     # Ringing node
    
        # 4. Long Decay Envelope
        midi.cc(CC.AMP_ATTACK, 0)      # Instant hit
        midi.cc(CC.AMP_DECAY, 90)      # Long wash
        midi.cc(CC.AMP_SUSTAIN, 0)     # No hold
        midi.cc(CC.AMP_RELEASE, 85)    # Very long release tail
    
        # 5. Spatial (Cymbal Splash)
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
        midi.cc(CC.DELAY_LEVEL, 0)
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-P: Striking cymbal. Press Ctrl+C to stop.")
        try:
            while True:
                # Play a high note to keep the fundamental pitch out of the bass frequencies
                midi.on(84, 110) # C6
                time.sleep(0.05)
                midi.off(84)
                time.sleep(4.0) # Let it ring out
        except KeyboardInterrupt:
            print("\nAgent Gamma-P: Halting.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
