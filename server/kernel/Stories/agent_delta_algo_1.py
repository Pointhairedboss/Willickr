#!/usr/bin/env python3
"""
Agent Delta — Patch 001: "The Markov Chain Sequence"

Objective: To emulate algorithmic, stochastic sequencing (common in Pure Data 
or Max/MSP) using only external MIDI scripting and the S-1's constraints.

Theory of Operation (Algorithmic Translation):
- True generative sequencers use logic gates, probability networks, and Markov chains.
- We simulate a Markov chain externally in Python. The current note determines 
  the probability weights for the *next* note.
- **Motion Recording Illusion**: In a modular environment, modulation is per-step. 
  To emulate this on the S-1 without programming its internal step sequencer, 
  we send targeted CC sweeps (Filter Cutoff or Envelope Decay) *simultaneously* 
  with specific MIDI notes, effectively creating dynamic "parameter locks" per step.

Taxonomic Application:
[Origin: Flow] + [Behavior: Generative] + [Emotion: Nostalgia] + [Role: Lead] + [Stress: Safe-Mode]
"""

import rtmidi
import time
import random
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class MarkovSequenceCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        # Map ontology for this specific algorithm
        self.parameters = {
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME
        }

    def init_synth_primitive(self, midi: Midi):
        print("\n[Agent Delta] Constructing foundational plucked lead...")
        
        midi.cc(CC.SAW_LEVEL, 127)
        try:
            midi.cc(CC.OSC_SQUARE, 0)
            midi.cc(CC.NOISE_LEVEL, 0)
        except AttributeError:
            pass
            
        # Sharp, plucky envelope
        midi.cc(CC.AMP_ATTACK, 0)
        midi.cc(CC.AMP_DECAY, self.get_val("afo:Loudness", 30, 80)) # Dynamic decay
        midi.cc(CC.AMP_SUSTAIN, 0)
        midi.cc(CC.AMP_RELEASE, 40)
        
        # Static filter base, will be moved rhythmically by SpectralCentroid state
        base_cutoff = self.get_val("afo:SpectralCentroid", 20, 100)
        midi.cc(CC.FILTER_CUTOFF, base_cutoff) 
        midi.cc(CC.FILTER_RES, 70) 
        
        midi.cc(CC.VOLUME, 100)
        
        # Spatial
        room_cc = self.get_cc("afo:RoomSize")
        if room_cc:
            midi.cc(room_cc, self.get_val("afo:RoomSize", 0, 80))
            
        time.sleep(0.1)

    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Delta] Initiating Markov Chain generative sequence for {duration}s.")
    
    # Define the nodes (MIDI notes in D Dorian)
    # 62(D4), 65(F4), 67(G4), 69(A4), 72(D5)
    
    # Markov transition matrix. Dict maps CurrentNote -> (List of NextNotes, Corresponding Weights)
    transitions = {
        62: ([62, 65, 69, 72], [10, 40, 30, 20]),
        65: ([62, 65, 67, 69], [30, 10, 40, 20]),
        67: ([65, 69, 72],     [30, 50, 20]),
        69: ([62, 67, 72],     [40, 40, 20]),
        72: ([62, 69],         [70, 30])
    }
    
    current_note = 62
    
        
        start_time = time.time()
        step = 0
        
        # Run sequence
        try:
            while time.time() - start_time < duration:
                # Dynamic mapping of the "average" brightness to the base
                centroid_val = self.get_val("afo:SpectralCentroid", 30, 90)
                
                # Determine parameter lock modifier based on the note chosen
                if current_note == 72:
                    # High notes get filter opened wide (parameter lock emulation)
                    midi.cc(CC.FILTER_CUTOFF, min(127, centroid_val + 40))
                    midi.cc(CC.AMP_DECAY, 80)
                elif current_note == 62:
                    # Root notes are dark and short
                    midi.cc(CC.FILTER_CUTOFF, max(0, centroid_val - 20))
                    midi.cc(CC.AMP_DECAY, 40)
                else:
                    # Mid notes vary
                    midi.cc(CC.FILTER_CUTOFF, centroid_val + random.randint(-15, 15))
                    midi.cc(CC.AMP_DECAY, 60)
                    
                print(f"Step {step+1:02d}: Note {current_note}")
                midi.on(current_note, 100)
                time.sleep(0.1) # 16th note gate
                midi.off(current_note)
                time.sleep(0.15) # rest
                
                # Calculate next state
                next_states, weights = transitions[current_note]
                current_note = random.choices(next_states, weights=weights)[0]
                step += 1
                
        except KeyboardInterrupt:
            print("\n[Agent Delta] Transport halted.")
        finally:
            midi.panic()

        print("\n[Agent Delta] Sequence concluded.")
    
if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = MarkovSequenceCartridge()
    cartridge.apply_ontology({"afo:SpectralCentroid": 0.6, "afo:RoomSize": 0.8})
    cartridge.execute(duration=10.0, device_id=hw_hint)
