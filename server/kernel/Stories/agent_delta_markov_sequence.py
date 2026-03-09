#!/usr/bin/env python3
"""
Agent Delta — Algorithmic Translator: Markov Chain & Micro-Envelopes
File: agent_delta_markov_sequence.py

Hardware Constraints Addressed:
1. Micro-Envelopes: Uses rapid filter envelope routed to pitch to emulate voice-stealing transient "clicks".
2. Slow Shifting LFO: Modulates waveform interactions to emulate 2-operator FM evolution over time.

Taxonomic Application:
[Origin: Artifacting] + [Behavior: Generative] + [Emotion: Melancholia] + [Role: Lead]
"""

import time
import random
from s1_midi import Midi, CC

# Simple Markov Chain for Note Generation (C Minor Pentatonic)
NOTES = [48, 51, 53, 55, 58] # C3, Eb3, F3, G3, Bb3
TRANSITIONS = {
    48: [48, 51, 55],
    51: [48, 53],
    53: [51, 55],
    55: [53, 58, 48],
    58: [55, 48]
}

def run_markov_sequence(midi: Midi):
    print("\n[Agent Delta] Constructing Markov Chain patch...")
    
    midi.cc(CC.SAW_LEVEL, 127)
    midi.cc(CC.OSC_SQUARE, 0)
    midi.cc(CC.NOISE_LEVEL, 0)
    
    # Micro-Envelope config for click: 
    midi.cc(CC.AMP_ATTACK, 0)
    midi.cc(CC.AMP_DECAY, 60)
    midi.cc(CC.AMP_SUSTAIN, 40)
    midi.cc(CC.AMP_RELEASE, 80)
    
    midi.cc(CC.FILTER_CUTOFF, 80)
    midi.cc(CC.FILTER_ENV, 100) # Deep envelope impact
    
    # Slow shifting LFO for evolution
    midi.cc(CC.LFO_MODE, 0) # Normal mode
    midi.cc(CC.LFO_RATE, 20) # Glacial
    midi.cc(CC.LFO_SHAPE, 0) # Sine
    midi.cc(CC.FILTER_LFO, 60)
    
    midi.cc(CC.VOLUME, 100)
    time.sleep(0.1)
    
    current_note = 48
    
    print("\n[Agent Delta] Executing Markov Chain...")
    
    try:
        step = 0
        while True:
            midi.on(current_note, random.randint(70, 110))
            
            # Occasionally induce a micro-clip via pitch mod
            if random.random() < 0.3:
                # Spike the Sub Level to fake a transient pop
                midi.cc(CC.SUB_LEVEL, 127)
                time.sleep(0.02)
                midi.cc(CC.SUB_LEVEL, 0)
                print(f"[{step:03d}] {current_note} | Micro-Transient Pop injected")
                time.sleep(0.23) # Rest of step
            else:
                print(f"[{step:03d}] {current_note}")
                time.sleep(0.25)
            
            midi.off(current_note)
            
            # Transition
            current_note = random.choice(TRANSITIONS[current_note])
            
            step += 1
            if step >= 50:
                break
    except KeyboardInterrupt:
        pass
    finally:
        midi.panic()

if __name__ == "__main__":
    m = Midi()
    run_markov_sequence(m)
