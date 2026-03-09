#!/usr/bin/env python3
"""
AGENT GAMMA-P (PERCUSSION) — PATCH 004: "The Orchestral Timpani"
Source: SyntheoryGordonReid - Chapter 30-31 (Practical Percussion Synthesis: Timpani)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]

Theory Implemented:
  1. Pitch Envelope: A timpani is a tuned drum where striking the head heavily bends the pitch downward before it settles 
     on the fundamental note. Because the S-1 lacks a dedicated Pitch Envelope depth knob (it only routes LFO to pitch), 
     we emulate this by routing the Filter Envelope to the Filter Cutoff (`CC26`), setting the filter to Self-Oscillation 
     (`CC71: 127`), and using the filter's frequency *as* the pitch. The rapid closing of the filter thereby functions 
     perfectly as a rapid downward pitch sweep.
  2. The Mallet Strike: Timpani use soft felt mallets, resulting in a slightly muted attack compared to a snare or kick. 
     The `AMP_ATTACK` is raised just slightly above 0 to remove the sharpest digital click.
     
Usage:
    python gamma_p_timpani_1.py
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

        print("Agent Gamma-P: Initializing 'The Orchestral Timpani' patch...")
    
        # 1. Harmonic Core
        # Timpani are highly resonant. We mute all standard waves and use the filter as a pure oscillator.
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 0)
        midi.cc(CC.SUB_LEVEL, 0)
        midi.cc(CC.NOISE_LEVEL, 0) 
    
        # 2. Filter Oscillation & "Pitch" Control
        midi.cc(CC.FILTER_RES, 127)    # Self Oscillation
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 15, 75))  # Rest state base frequency (the fundamental tuning of the drum)
    
        # 3. The Pitch Drop Envelope
        # We use a massive envelope depth to sweep the resonant frequency down from high to low rapidly.
        midi.cc(CC.FILTER_ENV, 110)
    
        # 4. Envelopes (VCA & VCF shared)
        midi.cc(CC.AMP_ATTACK, 10)     # Felt mallet (removes the click)
        midi.cc(CC.AMP_DECAY, 55)      # The pitch drops over this duration and the body volume begins to decay
        midi.cc(CC.AMP_SUSTAIN, 0)     # Drum dies eventually
        midi.cc(CC.AMP_RELEASE, 75)    # Very long copper bowl resonance
    
        # 5. Spatial
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))   # Timpani belong in concert halls
        midi.cc(CC.DELAY_LEVEL, 0)
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-P: Striking Timpani. Note the pitch drop and long resonance.")
        try:
            notes = [48, 48, 41, 41, 53, 53] # C3, F2, F3 pattern
            while True:
                for note in notes:
                    midi.on(note, 110)
                    time.sleep(0.1)
                    midi.off(note)
                    time.sleep(1.2) # Let the bowl resonate between strikes
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
