#!/usr/bin/env python3
"""
AGENT GAMMA-W (WINDS/VOICE) — PATCH 004: "The Synthetic Choir"
Source: SyntheoryGordonReid - Chapter 22 (Formant Synthesis)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Breath] + [Behavior: Evolving] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Pad] + [Historical: Vocal-Emulation]

Theory Implemented:
  1. Formant Peaks: The human voice produces distinct, fixed resonant peaks (formants) regardless of the pitch sung. 
     Because the S-1 filter strictly key-tracks (moves the cutoff with the note played), we cannot create true fixed 
     formants on the unit alone. We must compromise: we set a strong, static resonant peak (`CC71: 75`, `CC74: 65`) to 
     simulate a single formant vowel (like "Ah" or "Oh") around 800-1000Hz, and accept that it will shift musically 
     with the keyboard.
  2. The Vocal Tract: The vocal cords generate a complex, rich waveform. We blend maximum Sawtooth and Square waves 
     and add Chorus to simulate multiple voices.
  3. Breath Envelopes: A chorus swells in volume gradually. We use a long `AMP_ATTACK` and a long `AMP_RELEASE`.
     
Usage:
    python gamma_w_choir_1.py
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

        print("Agent Gamma-W: Initializing 'The Synthetic Choir' patch...")
    
        # 1. Complex Source (Vocal Cords)
        midi.cc(CC.SAW_LEVEL, 127)     # Maximum harmonic density
        midi.cc(CC.OSC_SQUARE, 127)    # Maximum odd-harmonic weight
        midi.cc(CC.SUB_LEVEL, 0)       # Keep it out of the low mud
    
        # 2. Formant Approximation ("Ah" Vowel)
        # The S-1 filter acts as a single resonant peak instead of multiple dedicated bandpasses.
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 35, 95))  # Somewhere around the middle "throat" frequency (~1kHz)
        midi.cc(CC.FILTER_RES, 75)     # Very high resonance to artificially peak the "vowel"

        # 3. Dynamic "Breathing" Envelopes
        midi.cc(CC.FILTER_ENV, 55)     # Slight positive filter swell on the attack as the voice opens
        midi.cc(CC.AMP_ATTACK, 80)     # Slow fade in
        midi.cc(CC.AMP_DECAY, 50)      # Settle back down from the initial burst
        midi.cc(CC.AMP_SUSTAIN, 90)    # Hold the choir volume high
        midi.cc(CC.AMP_RELEASE, 85)    # Voices ring out in the space
    
        # 4. Multi-Voice Modulation (The "Chorus")
        midi.cc(CC.LFO_RATE, 60)       # Subtle, slow LFO
        midi.cc(CC.LFO_MODE, 0)
        midi.cc(CC.PITCH, 15)          # Micro-pitch variations simulate multiple singers failing to hit perfect unison
        midi.cc(CC.CHORUS_LEVEL, 120)  # Maximum onboard chorus processing
    
        # 5. Cathedral Space
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
        midi.cc(CC.DELAY_LEVEL, 15)    # Slight slapback
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-W: Playing choral pad swell.")
    
        # Heavenly minor to major resolving 5th progression
        chords = [
            [60, 63, 67, 72], # C min
            [60, 64, 67, 72], # C Maj (Picardy Third resolution)
        ]
    
        try:
            while True:
                for chord in chords:
                    for note in chord:
                        midi.on(note, 80)
                    time.sleep(5.0) # Massive long swell holds 
                    for note in chord:
                        midi.off(note)
                    time.sleep(2.0) # Let the 85-release tail die naturally
        except KeyboardInterrupt:
            print("\nAgent Gamma-W: Halting.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
