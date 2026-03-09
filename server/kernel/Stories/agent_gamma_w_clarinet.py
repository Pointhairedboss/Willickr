"""
AGENT GAMMA-W: "The Clarinet"
Source: Gordon Reid's Synth Secrets (Chapter 23)

Taxonomic Application:
[Origin: Breath] + [Behavior: Evolving] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]
"""

import sys
import os
import time
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_patch(s1: Midi):
    print("--- Loading Patch: Clarinet (Gamma-W) ---")
    
    # 1. Harmonic Base (Square wave = Odd harmonics)
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 10) # Breath noise
    s1.cc(CC.OSC_SQUARE, 127)
    
    # 2. Emphasize body formants
    s1.cc(CC.FILTER_CUTOFF, 60) # Emphasize lower throat formants
    s1.cc(CC.FILTER_RES, 30)
    
    # 3. Breath Envelope
    s1.cc(CC.AMP_ATTACK, 20) # Soft attack
    s1.cc(CC.AMP_DECAY, 40)
    s1.cc(CC.AMP_SUSTAIN, 80)
    s1.cc(CC.AMP_RELEASE, 30)
    
    # 4. Modulations
    s1.cc(CC.LFO_RATE, 65) # Vibrato
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.PITCH, 10)
    
    s1.cc(CC.REVERB_LEVEL, 60)
    s1.cc(CC.DELAY_LEVEL, 0)

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)
    init_patch(s1)
    
    print("Clarinet patch loaded.")

if __name__ == "__main__":
    main()
