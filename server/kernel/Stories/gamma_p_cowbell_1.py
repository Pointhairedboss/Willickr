#!/usr/bin/env python3
"""
AGENT GAMMA-P (PERCUSSION) — PATCH 001: "The 808-Style Cowbell"
Source: SyntheoryGordonReid - Chapter 39 (Synthesizing Cowbells & Claves)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]

Theory Implemented:
  1. Metallic Inharmonicity: A cowbell requires two distinct oscillators tuned a major or minor 7th apart to create
     inharmonic metallic clash. Since the S-1 only has one true digital oscillator (and a linked sub/square), we use
     pseudo-FM (LFO to Pitch at audio-rate limits, ~140Hz) against a pure Square wave to generate severe sidebands 
     mimicking the two-oscillator clash of an 808 cowbell.
  2. The Envelope: A cowbell has an immediate strike and a moderately fast exponential decay. We bypass standard
     ADSR sustains to mimic the physical impact.
  3. Bandpass Simulation: True cowbells have very little low end and rolled-off highs. We use a heavily resonant
     filter to isolate the mid-band "clank".

Usage:
    python gamma_p_cowbell_1.py
"""

import sys
import time
import os

# Add parent directory to path to import the shared wrapper
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

        print("Agent Gamma-P: Initializing 'The 808-Style Cowbell' patch...")
    
        # 1. Harmonic Foundation (Square Wave Carrier)
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.SUB_LEVEL, 0)
        midi.cc(CC.NOISE_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 127)    # Pure square for maximum metallic clash potential
    
        # 2. Pseudo-FM Modulator (The second tuning)
        # Driving the LFO fast to create inharmonic sidebands against the square
        midi.cc(CC.LFO_RATE, 127)      # Max 140Hz cap
        midi.cc(CC.LFO_MODE, 127)      # Fast mode
        midi.cc(CC.PITCH, 60)          # Heavy modulation depth
    
        # 3. Bandpass Simulation via Filter
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 55, 115))  # Mid-high focus
        midi.cc(CC.FILTER_RES, 70)     # Heavy resonance to isolate the "clank" frequency
    
        # 4. Percussive Envelope
        midi.cc(CC.AMP_ATTACK, 0)      # Immediate strike
        midi.cc(CC.AMP_DECAY, 35)      # Fast exponential decay
        midi.cc(CC.AMP_SUSTAIN, 0)     # No hold
        midi.cc(CC.AMP_RELEASE, 20)    # Swift release to clear polyphony
    
        # 5. Dry Stage
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
        midi.cc(CC.DELAY_LEVEL, 0)
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-P: Playing cowbell test pattern. Press Ctrl+C to stop.")
    
        # The 808 cowbell relies on specific pitch ranges to hit the right ratio with the 140Hz LFO
        notes = [67, 67, 67, 0, 70, 70, 67, 0] # G4, Bb4 pattern
        bpm = 125
        step_time = (60.0 / bpm) / 4.0  # 16th notes
    
        try:
            while True:
                for note in notes:
                    if note > 0:
                        midi.on(note, 100)
                        time.sleep(step_time * 0.8)
                        midi.off(note)
                        time.sleep(step_time * 0.2)
                    else:
                        time.sleep(step_time)
        except KeyboardInterrupt:
            print("\nAgent Gamma-P: Halting seq.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
