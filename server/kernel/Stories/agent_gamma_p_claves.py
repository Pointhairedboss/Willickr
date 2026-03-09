"""
AGENT GAMMA-P: "The Claves"
Source: Gordon Reid's Synth Secrets (Chapter 39)

Taxonomic Application:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]
"""

import sys
import os
import time
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_patch(s1: Midi):
    print("--- Loading Patch: Claves (Gamma-P) ---")
    
    # 1. Pure tone for clave "knock"
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 0)
    s1.cc(CC.OSC_SQUARE, 0) 
    
    # 2. Filter Self-Oscillation
    s1.cc(CC.FILTER_RES, 127) # Self-oscillating filter for pure tone
    s1.cc(CC.FILTER_CUTOFF, 105) # High frequency resonant peak
    
    # 3. Very brief decay envelope
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 15) # Very rapid decay
    s1.cc(CC.AMP_SUSTAIN, 0)
    s1.cc(CC.AMP_RELEASE, 15)
    
    # 4. Dry acoustics
    s1.cc(CC.CHORUS_LEVEL, 0)
    s1.cc(CC.REVERB_LEVEL, 20)
    s1.cc(CC.DELAY_LEVEL, 0)

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)
    init_patch(s1)
    
    print("Claves patch loaded.")

if __name__ == "__main__":
    main()
