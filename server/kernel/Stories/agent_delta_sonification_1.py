#!/usr/bin/env python3
"""
AGENT DELTA (ALGORITHMIC TRANSLATOR) — Phase V, Experiment 1: "The Terrain Walker"

Taxonomy Navigation:
Instead of static music, this script reads a data array (a synthetic 1D terrain heightmap) 
and performs a mathematical sonification translation.

Translation Mappings (Based on data_sonification_deep_dive.md):
1. Pitch (Musical Scale Quantization): 
   - Normalised Height [0.0, 1.0] -> C Minor Pentatonic Scale Index.
2. Timbre (Derivative Mapping):
   - The absolute rate of change (slope) between the current height and previous height
     is multiplied and mapped to the S-1 Filter Cutoff (via afo:SpectralCentroid).
3. Base Primitive:
   - Uses Agent Gamma's subtractive baseline (Sawtooth focused, resonant filter).
"""

import sys
import time
import math
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

# 1. The Dataset (Synthetic Terrain Heightmap)
# We generate 64 points of continuous data resembling hills and valleys [0.0, 1.0]
def generate_terrain(length=64):
    data = []
    for i in range(length):
        # Combine low freq sine (hills) with higher freq sine (bumps)
        v = (math.sin(i * 0.2) + 0.5 * math.sin(i * 0.8) + 1.5) / 3.0 
        data.append(max(0.0, min(1.0, v)))
    return data

# 2. The Scale (C Minor Pentatonic, 3 Octaves)
SCALE = [36, 39, 41, 43, 46, 48, 51, 53, 55, 58, 60, 63, 65, 67, 70]

def get_midi_note(normalized_value):
    val = max(0.0, min(1.0, normalized_value))
    index = math.floor(val * (len(SCALE) - 1))
    return SCALE[index]

class TerrainWalkerCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        # Default parameter mapping fallback
        self.parameters = {"afo:SpectralCentroid": CC.FILTER_CUTOFF}

    def init_synth_primitive(self, midi: Midi):
        print("Agent Delta: Initializing Subtractive Base for Sonification...")
        midi.cc(CC.SAW_LEVEL, 127)
        try:
            midi.cc(CC.OSC_SQUARE, 0)
        except AttributeError:
            pass # Depending on s1_midi CC definition
        try:
            midi.cc(CC.SUB_LEVEL, 80)
            midi.cc(CC.NOISE_LEVEL, 0)
        except AttributeError:
            pass
            
        midi.cc(CC.AMP_ATTACK, 0)
        midi.cc(CC.AMP_DECAY, 40)
        midi.cc(CC.AMP_SUSTAIN, 0)
        midi.cc(CC.AMP_RELEASE, 30)
        
        # Pull base resonance and filter envelope depth from our generic Loudness/Timbre
        base_res = self.get_val("afo:Loudness", 60, 110) # Louder = more squelch
        midi.cc(CC.FILTER_RES, base_res)
        
        try:
            midi.cc(CC.FILTER_ENV, 80)
        except AttributeError:
            pass
        
        # Spatial effects mapping via ontology 
        room_cc = self.get_cc("afo:RoomSize")
        if room_cc:
            midi.cc(room_cc, self.get_val("afo:RoomSize", 0, 80))
            
        time.sleep(0.5)

    def execute(self, duration: float, device_id: int):
        print(f"Agent Delta: Executing sonification for duration {duration}s on device {device_id}...")
        
        m = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(m)
        data = generate_terrain()
        
        prev_height = data[0]
        
        # We need the correct CC for Filter Cutoff, from semantic mapping
        filter_cc = self.get_cc("afo:SpectralCentroid")
        if not filter_cc: filter_cc = CC.FILTER_CUTOFF
        print(f"Using afo:SpectralCentroid mapped to CC: {filter_cc}")
        
        start_time = time.time()
        
        try:
            for i, height in enumerate(data):
                if time.time() - start_time > duration:
                    print("\nAgent Delta: Duration limit reached.")
                    break
                    
                # 1. Pitch Mapping
                note = get_midi_note(height)
                
                # 2. Derivative Mapping (Slope)
                # Calculate absolute change from previous point
                delta = abs(height - prev_height)
                prev_height = height
                
                # Volatility is usually small, so we amplify it to control the filter
                # Mapping [0.0, ~0.2] slope -> [20, 120] CC Cutoff
                cutoff_val = int(min(127, max(15, 15 + (delta * 500)))) 
                
                m.cc(filter_cc, cutoff_val)
                
                # Formulate console output to show the translation layer at work
                bar = "#" * int(height * 20)
                print(f"Index [{i:02d}] | Data: {height:.2f} | Slope: {delta:.2f} -> CC[{filter_cc}]: {cutoff_val:03d} | Note: {note:02d} | Terrain: {bar}")
                
                # Trigger note
                m.on(note, velocity=100)
                time.sleep(0.15) # 16th note at ~100BPM
                m.off(note)
                
        except KeyboardInterrupt:
            print("\nAgent Delta: Transport halted.")
            
        finally:
            m.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = TerrainWalkerCartridge()
    # Test apply_ontology with normalized float
    cartridge.apply_ontology({"afo:SpectralCentroid": 0.8, "afo:RoomSize": 0.9, "afo:Loudness": 0.95})
    
    # Test run it as an object
    cartridge.execute(duration=10.0, device_id=hw_hint)
