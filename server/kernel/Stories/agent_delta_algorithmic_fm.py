#!/usr/bin/env python3
"""
Agent Delta — Algorithmic Translator: Stochastic Pseudo-FM
File: agent_delta_algorithmic_fm.py

Hardware Constraints Addressed:
1. Pseudo-FM Cap: Carrier fundamentals kept below ~140Hz (C2-C3) so the S-1's max LFO (modulator) 
   can produce true inharmonic sidebands via high-rate Pitch and Filter modulation.
2. Artifacting as Feature: 
   - Polyphony (4 voices) is intentionally breached with long AMP release times to produce rhythmic voice-stealing clicks.
   - High-density CC data (600+ msgs/sec) is injected probabilistically to create LPF "zipper noise" tearing out of the filter.

Taxonomic Application:
[Origin: System] + [Behavior: Generative] + [Emotion: Abrasive] + [Role: Texture/Percussion] + [Stress: Failure-State] + [Stress: Artifacting]
"""

import rtmidi
import time
import random
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class StochasticPseudoFMCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:ModulationRate": CC.LFO_RATE,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME
        }

    def init_synth_primitive(self, midi: Midi):
        print("\n[Agent Delta] Constructing primary carrier patch. Initializing Modulators...")
    
        # Square wave base carrier, harsh geometric harmonics
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 127)
        
        # 1st Artifact Mechanism: Long release to force hard-cutoff voice stealing
        midi.cc(CC.AMP_ATTACK, 0)
        midi.cc(CC.AMP_DECAY, self.get_val("afo:Loudness", 40, 100))
        midi.cc(CC.AMP_SUSTAIN, 0)
        midi.cc(CC.AMP_RELEASE, 127) 
        
        # Filter setup for pronounced pseudo-FM interaction
        midi.cc(CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 20, 80))
        midi.cc(CC.FILTER_RES, 90)
        
        # Push modulators to hardware cap (~140Hz max)
        midi.cc(CC.LFO_RATE, self.get_val("afo:ModulationRate", 100, 127))
        midi.cc(CC.PITCH, 110)
        midi.cc(CC.FILTER_LFO, 110)
        # midi.cc(CC.LFO_DEPTH, 127) # Removed, absorbed into specific depth CCs
        
        # Spatial 
        room_cc = self.get_cc("afo:RoomSize")
        if room_cc:
            midi.cc(room_cc, self.get_val("afo:RoomSize", 0, 80))
            
        midi.cc(CC.VOLUME, 100)
        time.sleep(0.1)

    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Delta] Commencing algorithmic translation for {duration}s. Inducing [Failure-State: Voice Stealing & Zipper Noise]")
        
        # Low octave root notes (Fundamental frequencies under 140Hz)
        roots = [36, 38, 41, 43, 48] # C2, D2, F2, G2, C3
        active_voices = []
        
        start_time = time.time()
        step = 0
        
        try:
            while time.time() - start_time < duration:
                note = random.choice(roots)
                velocity = random.randint(90, 127)
                
                # STRESS TEST 1: The Voice-Stealing Percussive "Click"
                midi.on(note, velocity)
                active_voices.append(note)
                
                operator_ratio = 127
                
                # STRESS TEST 2: The CC Flood Zipper
                # 15% probability to flood the data line and cause audible zipper artifacts in the filter
                if random.random() < 0.15:
                    for _ in range(12):
                        # Use centroid mapping for localized CC burst
                        base_cut = self.get_val("afo:SpectralCentroid", 30, 95)
                        midi.cc(CC.FILTER_CUTOFF, random.randint(max(0, base_cut-20), min(127, base_cut+20)))
                else:
                    # Normal stochastic "ratio" modulation
                    operator_ratio = random.randint(95, 127)
                    midi.cc(CC.LFO_RATE, operator_ratio)
                    midi.cc(CC.FILTER_LFO, random.randint(70, 127))

                print(f"[{step:03d}] Carrier Note: {note} | Modulator 'Ratio' (Rate CC): {operator_ratio}")
                
                # Rapid sequence speed guaranteed to breach polyphony
                time.sleep(random.uniform(0.04, 0.12))
                
                # Cull oldest notes to maintain continuous trigger influx
                if len(active_voices) > 10:
                    old_note = active_voices.pop(0)
                    midi.off(old_note)
                step += 1
                    
        except KeyboardInterrupt:
            print("\n[Agent Delta] Operator manual override. Terminating sequence.")
        finally:
            for n in active_voices:
                midi.off(n)
            midi.panic()
            print("\n[Agent Delta] Stochastic patch playback complete.")

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = StochasticPseudoFMCartridge()
    cartridge.apply_ontology({"afo:SpectralCentroid": 0.5, "afo:ModulationRate": 1.0, "afo:Loudness": 0.9})
    cartridge.execute(duration=10.0, device_id=hw_hint)
