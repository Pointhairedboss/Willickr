#!/usr/bin/env python3
"""
Agent Delta — Algorithmic Translator: Euclidean FM
File: agent_delta_euclidean_fm.py

Hardware Constraints Addressed:
1. Pseudo-FM: Uses audio-rate LFO routed to Pitch to create inharmonic percussion.
2. Parameter Locks: Simulates Elektron-style p-locks by sending CCs tied explicitly to sequence steps.

Taxonomic Application:
[Origin: System] + [Behavior: Rhythmic] + [Emotion: Tension] + [Role: Percussive]
"""

import sys
import os
import time
import random

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class AgentDeltaEuclideanFMCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
             "afo:SpectralCentroid": CC.FILTER_CUTOFF,
             "afo:Loudness": CC.VOLUME,
        }
        
    def generate_euclidean(self, k, n):
        """Generate a Euclidean rhythm of k pulses in n steps."""
        result = []
        bucket = 0
        for i in range(n):
            bucket += k
            if bucket >= n:
                bucket -= n
                result.append(1)
            else:
                result.append(0)
        return result

    def init_synth_primitive(self, midi: Midi):
        print("\n[Agent Delta] Constructing Euclidean sequence patch...")
        
        # Initialize Core for Percussive "Strike"
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 127)
        midi.cc(CC.SUB_LEVEL, 127)
        midi.cc(CC.NOISE_LEVEL, 20)
        
        # Sharp Envelope
        midi.cc(CC.AMP_ATTACK, 0)
        midi.cc(CC.AMP_DECAY, 40)
        midi.cc(CC.AMP_SUSTAIN, 0)
        midi.cc(CC.AMP_RELEASE, 20)
        
        # Filter
        midi.cc(CC.FILTER_RES, 110)
        midi.cc(CC.FILTER_ENV, 80)
        
        # LFO FM (Audio rate)
        midi.cc(CC.LFO_MODE, 127) # Fast mode
        midi.cc(CC.LFO_RATE, 127) # Max 140Hz
        midi.cc(CC.LFO_SHAPE, 127) # Random/S&H
        midi.cc(CC.PITCH, 100) # LFO to Pitch
        
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 100))
        time.sleep(0.1)

    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id and str(device_id) != "offline" else None)
        self.init_synth_primitive(midi)
        
        rhythm = self.generate_euclidean(5, 16)
        root = 36 # C2, keep below 140Hz for FM
        
        print(f"\n[Agent Delta] Playing E(5,16): {rhythm} for {duration} seconds.")
        
        start_time = time.time()
        try:
            step = 0
            while time.time() - start_time < duration:
                is_hit = rhythm[step % len(rhythm)]
                if is_hit:
                    # Parameter Lock: Randomize filter and decay on hit
                    base_cutoff = self.get_val("afo:SpectralCentroid", 30, 90)
                    midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, base_cutoff)
                    midi.cc(CC.AMP_DECAY, random.randint(20, 60))
                    midi.on(root, random.randint(100, 127))
                    print(f"[{step:03d}] HIT  | Cutoff P-Lock {base_cutoff}")
                else:
                    # Soft ghost notes occasionally
                    if random.random() < 0.2:
                        midi.on(root + 12, random.randint(30, 60))
                        print(f"[{step:03d}] GHOST")
                
                time.sleep(0.125) # 16th note at ~120 BPM
                midi.off(root)
                midi.off(root + 12)
                step += 1
                
        except KeyboardInterrupt:
            pass
        finally:
            midi.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = AgentDeltaEuclideanFMCartridge()
    cartridge.execute(duration=5.0, device_id=hw_hint)
