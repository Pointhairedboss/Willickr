"""
AGENT GAMMA-P: "The TR-808 Hi-Hat"
Source: Gordon Reid's Synth Secrets (Chapter 37/38)

Taxonomic Application:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]
"""

import sys
import os
import time
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_patch(s1: Midi):
    print("--- Loading Patch: TR-808 Hi-Hat (Gamma-P) ---")
    
    # 1. 6-Oscillator Fake
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.OSC_SQUARE, 127)
    s1.cc(CC.NOISE_LEVEL, 127) # Add white noise
    s1.cc(CC.LFO_RATE, 127)
    s1.cc(CC.LFO_MODE, 127)
    s1.cc(CC.PITCH, 40) # Pseudo-FM
    
    # 2. High-pass filter simulation
    s1.cc(CC.FILTER_CUTOFF, 115) 
    s1.cc(CC.FILTER_RES, 60)
    
    # 3. Snappy decay
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 25) # Short metallic hash for closed hat
    s1.cc(CC.AMP_SUSTAIN, 0)
    s1.cc(CC.AMP_RELEASE, 20)
    
    s1.cc(CC.REVERB_LEVEL, 10)
    s1.cc(CC.DELAY_LEVEL, 0)

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)
    init_patch(s1)
    
    print("TR-808 Hi-Hat patch loaded.")

if __name__ == "__main__":
    main()
