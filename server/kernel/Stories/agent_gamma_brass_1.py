#!/usr/bin/env python3
"""
Agent Gamma — Patch 001: "The Synthetic Brass Blat"

Objective: To recreate the classic Prophet-5 style analog brass emulation, 
adhering strictly to Gordon Reid's structural acoustic principles.

Theory of Operation (Subtractive Brass Synthesis):
Unlike real acoustic instruments which change harmonic structure dynamically based 
on lip pressure, analog brass relies on a very specific filter envelope behavior:
- **The Oscillators**: A rich SAW basis is absolutely required for the even + odd harmonics.
- **The "Blat"**: The defining characteristic of synthesized brass. It is achieved 
  by setting the filter cutoff very low, but driving the Filter Envelope Depth 
  high, alongside a moderately slow (but not sluggish) filter attack and a quick decay. 
  This forces the upper harmonics to sweep open and close rapidly at the onset of the note.
- **The Amplifier**: Must mirror the filter envelope but with a slightly softer 
  attack so the fundamental doesn't "click" before the harmonics arrive.

Taxonomic Application:
[Origin: Breath] + [Behavior: Decaying] + [Emotion: Euphoria] + [Role: Lead] + [Historical: Brass-Subtractive]
"""

import rtmidi
import time
import sys
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

        print("\n[Agent Gamma] Constructing Classic Analog Brass...")
    
        # Oscillators: Rich Sawtooth basis
        s1.cc(CC.SAW_LEVEL, 127)  # Maximum harmonic content
        s1.cc(CC.OSC_SQUARE, 0)
        s1.cc(CC.SUB_LEVEL, 40)   # Thicken the fundamental just slightly
        s1.cc(CC.NOISE_LEVEL, 0)

        # Amplifier Envelope
        s1.cc(CC.AMP_ATTACK, 25)  # Slight ramp to avoid click
        s1.cc(CC.AMP_DECAY, 80)
        s1.cc(CC.AMP_SUSTAIN, 95) # High sustain
        s1.cc(CC.AMP_RELEASE, 30) # Natural room decay

        # The Filter "Blat" Mechanics
        s1.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 0, 45)) # Very closed initially
        s1.cc(CC.FILTER_RES, 25)    # Slight bump for the sweep
        s1.cc(CC.FILTER_ENV, 110)   # Extreme ENV depth pushing the cutoff open
    
        # We must orchestrate the Filter Envelope *independently* of the Amp envelope 
        # if the S-1 architecture allows it. The S-1 CCs (73, 75, 70, 72) govern the AMP 
        # envelope. If CC74 acts dynamically under ENV_TO_FILT (CC26), we rely on 
        # the internal routing to offset them, OR we use the S-1's shared envelope. 
        # Assuming shared envelope: The attack of 25 is slow enough to let the filter 
        # open up over ~30-50ms, creating the "mwah" brass blat.

        # Spatial
        s1.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))  # Standard 80s plate verb emulation
        s1.cc(CC.DELAY_LEVEL, 0)
        s1.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
    
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        s1 = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(s1)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Agent Gamma] Triggering C Minor 9 chord to audition the filter sweep.")
    
        chord = [60, 63, 67, 74] # C, Eb, G, D
    
        # Hit the chord hard to trigger maximum envelope/filter depth
        for n in chord:
            s1.on(n, 110)
        
        time.sleep(1.5) # Hold the sustain phase
    
        for n in chord:
            s1.off(n)
        
        time.sleep(1.0)
        print("[Agent Gamma] Demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
