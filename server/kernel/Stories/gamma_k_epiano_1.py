#!/usr/bin/env python3
"""
AGENT GAMMA-K (KEYS) — PATCH 004: "The Synthetic Electric Piano"
Source: SyntheoryGordonReid - Chapters 40-42 (Extrapolating Rhodes/Wurlitzer concepts)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Acoustic-Emulation]

Theory Implemented:
  1. Bell-like Transients: Electric pianos (like a Rhodes or DX7 E-Piano) are characterized by an extremely bell-like,
     inharmonic "tine" strike that decays into a warm, nearly pure sine-wave hum.
  2. FM Tine Emulation: Unable to use true multi-operator FM, we emulate the tine strike utilizing our audio-rate LFO 
     modulating the Square wave pitch (`CC3: 127`, `CC17`). We then use the Filter Envelope to snap the cutoff down 
     rapidly (20ms decay), choking off this chaotic metallic sideband cluster almost instantly.
  3. The Body: The Sub-oscillator provides the warm, dark fundamental body that sustains after the filter closes 
     and removes the bright FM tine.
     
Usage:
    python gamma_k_epiano_1.py
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

        print("Agent Gamma-K: Initializing 'The Synthetic Electric Piano' patch...")
    
        # 1. Tine (Upper) & Body (Lower) Split
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 100)    # The Modulated Tine
        midi.cc(CC.SUB_LEVEL, 127)     # The Warm Body 
    
        # 2. Pseudo-FM Tine Generation
        midi.cc(CC.LFO_RATE, 127)      # Audio-rate (140Hz)
        midi.cc(CC.LFO_MODE, 127)
        midi.cc(CC.PITCH, 40)          # Apply FM sidebands to the square wave, making it sound very metallic
    
        # 3. Dynamic Filtering (The Tine decay into the Body)
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 0, 55))  # The rest state is very dark, letting only the sub-oscillator through clearly
        midi.cc(CC.FILTER_ENV, 85)     # 
        midi.cc(CC.FILTER_RES, 20)
    
        # 4. Hybrid Envelope (Fast Filter Snap, Slow VCA Ring)
        midi.cc(CC.AMP_ATTACK, 0)      # Hard hammer strike
        midi.cc(CC.AMP_DECAY, 20)      # Snap the filter down VERY fast to kill the FM tine, while VCA stays loud
        midi.cc(CC.AMP_SUSTAIN, 0)     # Continuous decay
        midi.cc(CC.AMP_RELEASE, 60)    # Long electrical ring out
    
        # 5. Spacial
        # Classical E-Piano requires a chorus effect (Chorus/Tremolo)
        midi.cc(CC.CHORUS_LEVEL, 70)
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
        midi.cc(CC.DELAY_LEVEL, 0)
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-K: Playing E-Piano chords.")
    
        # Jazz/Soul progression
        chords = [
            [60, 64, 67, 71], # Cmaj7
            [62, 65, 69, 72], # Dmin7
            [67, 71, 74, 77], # G7
            [60, 64, 67, 71]  # Cmaj7
        ]
    
        try:
            while True:
                for chord in chords:
                    for note in chord:
                        midi.on(note, 90)
                    time.sleep(1.5)
                    for note in chord:
                        midi.off(note)
                    time.sleep(0.2)
        except KeyboardInterrupt:
            print("\nAgent Gamma-K: Halting.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
