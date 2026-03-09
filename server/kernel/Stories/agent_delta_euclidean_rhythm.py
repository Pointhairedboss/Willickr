import time
import random
import sys
import os

# Add parent directory to path to import s1_midi
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

"""
Agent Delta: Euclidean Rhythm & Parameter Locking

Acoustic Theory & Synthesis Strategy:
This script employs Euclidean algorithms to generate a primary rhythmic sequence.
To bypass the S-1's lack of complex built-in modulation matrices, Python acts
as the primary sequencer, utilizing 'Parameter Locks'. Every step of the 
sequence not only triggers a note but also fires rapid CC messages to alter
the Filter Cutoff (CC 74) and Resonance (CC 71). 

This approach creates the illusion of multiple overlapping percussion synths 
(a kick-like low thud vs a sharp high hat) all from a single polyphonic voice.

Taxonomic Application:
[Origin: System] + [Behavior: Rhythmic] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive]
"""

def generate_euclidean(pulses, steps):
    """Generates a Euclidean rhythm pattern."""
    if pulses >= steps:
        return [1] * steps
    
    # Bresenham's line algorithm variation for Euclidean rhythm
    pattern = []
    bucket = 0
    for i in range(steps):
        bucket += pulses
        if bucket >= steps:
            bucket -= steps
            pattern.append(1)
        else:
            pattern.append(0)
    return pattern

def run_euclidean_rhythm_patch():
    print("Agent Delta: Initializing Euclidean Rhythm Generator...")
    try:
        synth = Midi()
    except Exception as e:
        print(f"Failed to connect to S-1: {e}")
        return

    # Basic setup
    synth.cc(CC.VOLUME, 100)
    synth.cc(CC.SAW_LEVEL, 0)
    synth.cc(CC.OSC_SQUARE, 127)  # Square wave core
    synth.cc(CC.NOISE_LEVEL, 40)  # Some noise for percussion transient
    synth.cc(CC.SUB_LEVEL, 127)   # Sub for low end

    # Envelope setup - tight and percussive
    synth.cc(CC.AMP_ATTACK, 0)
    synth.cc(CC.AMP_DECAY, 40)
    synth.cc(CC.AMP_SUSTAIN, 0)
    synth.cc(CC.AMP_RELEASE, 20)
    
    # Filter setup - rely on python script to sequence the cutoff
    synth.cc(CC.FILTER_ENV, 80)
    
    # Generate rhythms
    kick_pattern = generate_euclidean(5, 16)
    hat_pattern = generate_euclidean(11, 16)
    
    bpm = 120
    step_time = (60.0 / bpm) / 4.0 # 16th notes
    
    print("Beginning generative sequence. Press Ctrl+C to stop.")
    
    try:
        step = 0
        while True:
            # Kick lock
            if kick_pattern[step % 16]:
                # Parameter lock: Low filter, high resonance for 'thud'
                synth.cc(CC.FILTER_CUTOFF, 40)
                synth.cc(CC.FILTER_RES, 110)
                synth.on(36, 120) # C2
            
            # Hat lock
            elif hat_pattern[step % 16]:
                # Parameter lock: High filter, low resonance for 'click'
                synth.cc(CC.FILTER_CUTOFF, 110)
                synth.cc(CC.FILTER_RES, 30)
                synth.on(60, 80) # C4
                
            time.sleep(step_time)
            
            # Simple note off (relies on short decay/release anyway)
            synth.off(36)
            synth.off(60)
            
            step += 1
            
            # Algorithmic shift: occasionally mutate the pattern
            if step % 64 == 0:
                print("Agent Delta: Mutating Euclidean parameters...")
                kick_pattern = generate_euclidean(random.randint(3, 7), 16)
                hat_pattern = generate_euclidean(random.randint(9, 13), 16)
                
    except KeyboardInterrupt:
        print("\nAgent Delta sequence terminated.")
        synth.panic()

if __name__ == "__main__":
    run_euclidean_rhythm_patch()
