#!/usr/bin/env python3
"""
AGENT BETA (AMBIENT) — PATCH 001: "The Fracture Bed"

Taxonomy:
[Origin: Fracture] + [Behavior: Generative] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Bed/Pad]

Theory Implemented:
  1. Spatial Smearing: Heavy reverb (CC91) and delay (CC92) to create continuous beds from sparse 2-voice plucks.
  2. Generative Motion: LFO (CC3, CC17) routed to filter (CC25) at a very slow rate to simulate organic drift.
  3. Textural Source: Square wave (CC21) mixed with noise (CC23) and high resonance (CC71) for unstable tension.
  4. Perspective Layering: Low cutoff (CC74) pushes the drone into the background.

Usage:
    python agent_beta_ambient_1.py
"""

import time
import random
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class AgentBetaAmbient1Cartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME,
            "afo:DelayFeedback": CC.DELAY_LEVEL
        }

    def init_synth_primitive(self, midi: Midi):
        print("Agent Beta: Initializing 'The Fracture Bed' patch...")
        
        # 1. Base Tones
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 85)     # Hollow, haunting base
        midi.cc(CC.NOISE_LEVEL, 15)    # Slight textural hiss (Room Tone)
        
        # 2. Filter & Drift (Ambient Generativity)
        midi.cc(CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 20, 60))  # Dark, pushed into the background
        midi.cc(CC.FILTER_RES, 80)     # High resonance for tension
        
        # Very slow LFO assigned to filter for organic drift
        midi.cc(CC.LFO_RATE, 2)        # Extremely slow
        midi.cc(CC.FILTER_LFO, 64)    # Send LFO to filter cutoff
        
        # 3. Envelope - Swells and Long Tails
        midi.cc(CC.AMP_ATTACK, 40)     # Slow fade in
        midi.cc(CC.AMP_DECAY, 90)      
        midi.cc(CC.AMP_SUSTAIN, 70)    # Hold a drone
        midi.cc(CC.AMP_RELEASE, 65)    # Reduced release to prevent voice-stealing clicks; FX buffer will carry tail
        
        # 4. Spatial Smearing
        midi.cc(CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 80, 127))  # Absolute maximum space
        midi.cc(CC.DELAY_LEVEL, self.get_val("afo:DelayFeedback", 40, 90))    # Increased echo to compensate for shorter envelope tail
        midi.cc(CC.VOLUME, self.get_val("afo:Loudness", 40, 100))
        time.sleep(0.5)

    def execute(self, duration: float, device_id: int):
        print(f"Agent Beta: Starting generative sequence for {duration} seconds.")
        midi = Midi(hint=str(device_id) if device_id and device_id != "offline" else None)
        self.init_synth_primitive(midi)
        
        # E minor pentatonic / tense intervals
        base_pool = [40, 47, 52, 55, 59] 
        active_notes = []
        
        start_time = time.time()
        try:
            while time.time() - start_time < duration:
                # Pick a small cluster (1-2 notes max to preserve S-1 4-voice limit)
                notes_to_play = random.sample(base_pool, k=random.randint(1, 2))
                velocity = random.randint(35, 65) # Kept soft and distant
                
                for note in notes_to_play:
                    midi.on(note, velocity)
                    active_notes.append(note)
                    print(f"🎵 Floating pitch: {note} (vel: {velocity})")
                
                # Hold for a slow breath
                time.sleep(random.uniform(1.0, 3.0))
                
                # Release notes - the spatial engine will carry the sound, voices are freed
                for note in notes_to_play:
                    midi.off(note)
                    if note in active_notes:
                        active_notes.remove(note)
                    
                # Wait for tails to overlap before striking again
                time.sleep(random.uniform(2.0, 4.0))
                
        except KeyboardInterrupt:
            print("\nAgent Beta: Halting sequence.")
            
        finally:
            for note in active_notes:
                midi.off(note)
            midi.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = AgentBetaAmbient1Cartridge()
    cartridge.execute(duration=10.0, device_id=hw_hint)
