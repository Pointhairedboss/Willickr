#!/usr/bin/env python3
"""
Agent Gamma-K (Keys) — Patch 002: "The Synthetic Acoustic Piano"

Source: SyntheoryGordonReid (Chapters 40-43: Synthesizing Pianos)
Objective: To recreate an acoustic piano using purely subtractive methods.

Theory of Operation:
A piano is struck string. It has an immense burst of high harmonics at the hammer 
impact, followed by a dynamically evolving harmonic decay.
- **The String**: A mixture of Sawtooth (even & odd harmonics) and a narrowed 
  Pulse wave (to simulate the struck node cancellations).
- **The Hammer**: A sharp filter envelope sweep. The cutoff starts high but 
  closes quickly, leaving only the fundamental humming.
- **The Soundboard (Decay)**: The VCA decays slower than the VCF, meaning the 
  body of the note rings out dark after the bright transient.
- **Hardware Constraint**: We must manage polyphony voice-stealing gracefully (`CC72`).

Taxonomy (Archivist Pre-Assigned):
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Acoustic-Emulation]
"""

from s1_midi import Midi, CC
from cartridge_base import BaseCartridge
import time


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

        print("\n[Gamma-K] Constructing Synthetic Acoustic Piano...")
    
        # The Harmonic String Body
        midi.cc(CC.SAW_LEVEL, 120)
        midi.cc(CC.OSC_SQUARE, 80) # Adds complex odd harmonics
        midi.cc(CC.SUB_LEVEL, 20)  # Slight body
        midi.cc(CC.NOISE_LEVEL, 0) 
    
        # The Soundboard (VCA Envelope)
        midi.cc(CC.AMP_ATTACK, 0)     # Hammer strike
        midi.cc(CC.AMP_DECAY, 80)     # Long body decay
        midi.cc(CC.AMP_SUSTAIN, 0)    # A true piano string eventually dies
        midi.cc(CC.AMP_RELEASE, 40)   # Moderate release. High values cause voice-stealing clicks on the S-1.
    
        # The Wood / Formant
        midi.cc(CC.FILTER_RES, 15)    # Low resonance so it doesn't sound "synthy"
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 0, 40)) # Dark fundamental body
    
        # The Hammer Strike (Filter Envelope Dynamics)
        # The filter must sweep open rapidly to let the bright Saw/Square harmonics 
        # through at the instant of the strike, then decay back down to the dark fundamental.
        midi.cc(CC.FILTER_ENV, 80)
    
        # Velocity sensitivity emulation (simulated via master volume for illustration)
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
    
        # A tiny bit of chorus and reverb to simulate the piano cabinet and sympathetic resonance
        midi.cc(CC.CHORUS_LEVEL, 25)
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
    
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Gamma-K] Playing piano chord progression (Voice-Stealing managed).")
    
        chords = [
            [60, 64, 67], # C Maj
            [65, 69, 72], # F Maj
            [67, 71, 74], # G Maj
            [60, 64, 67]  # C Maj
        ]
    
        for chord in chords:
            # Strike the chord
            for note in chord:
                midi.on(note, 90)
            
            time.sleep(1.0) # Hold the chord to hear the decay
        
            # Release the chord
            for note in chord:
                midi.off(note)
            
            time.sleep(0.3) # Give the 40ms release tail time to clear before the next chord to avoid click
        
        print("\n[Gamma-K] Piano demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
