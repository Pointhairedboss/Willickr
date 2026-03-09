"""
AGENT GAMMA-P: "The Synthesized Bell"
Source: Gordon Reid's Synth Secrets (Chapter 38)

Taxonomic Application:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Percussive/Lead] + [Historical: Percussive-Analog]
"""

import sys
import os
import time
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_patch(s1: Midi):
    print("--- Loading Patch: Synthesized Bell (Gamma-P) ---")
    
    # 1. Stretched Harmonics Base
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 0)
    s1.cc(CC.OSC_SQUARE, 100) # Muted square
    
    # 2. Pseudo-FM for inharmonic strike
    s1.cc(CC.LFO_RATE, 127) # Audio-rate to pitch
    s1.cc(CC.LFO_MODE, 127)
    s1.cc(CC.PITCH, 60) 
    
    # 3. Filter simulating the bell body
    s1.cc(CC.FILTER_CUTOFF, 80)
    s1.cc(CC.FILTER_RES, 40)
    
    # 4. Long release (ringing out)
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 50)
    s1.cc(CC.AMP_SUSTAIN, 0)
    s1.cc(CC.AMP_RELEASE, 80)
    
    # 5. Effects
    s1.cc(CC.CHORUS_LEVEL, 40)
    s1.cc(CC.REVERB_LEVEL, 80) # Long reverb to fake the subharmonic hum
    s1.cc(CC.DELAY_LEVEL, 0)

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)
    init_patch(s1)
    
    print("Bell patch loaded.")
    
if __name__ == "__main__":
    main()
