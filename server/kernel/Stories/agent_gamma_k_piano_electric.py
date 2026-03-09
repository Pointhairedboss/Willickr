"""
Agent Gamma-K: Electric Piano Transcription
Source: Gordon Reid's Synth Secrets (Adaptation for EP/Tines)

Acoustic Theory & Translation Strategy:
- Electric pianos (Rhodes/Wurlitzer) rely on tines or reeds being struck by hammers.
- They have a distinct "bell-like" harmonic at the attack phase.
- We use the S-1's Audio-Rate LFO to create Pseudo-FM on the pitch (or cross-mod emulation) to synthesize the metallic tine strike.
- The fundamental body of the sound uses a Square wave or Triangle (which we approximate with filtered Square) for a hollow, even-harmonic-missing tone.

Taxonomic Application:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]
"""

import time
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_patch(s1: Midi):
    print("--- Loading Patch: Electric Piano/Tines (Gamma-K) ---")

    # 1. Oscillator Mix: Hollow body tone
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.SUB_LEVEL, 70)
    s1.cc(CC.OSC_SQUARE, 90) # Emphasize square for hollow Rhodes-like timbre
    s1.cc(CC.NOISE_LEVEL, 0)

    # 2. Envelope: Fast attack, sustained bell ring
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 70)
    s1.cc(CC.AMP_SUSTAIN, 40)
    s1.cc(CC.AMP_RELEASE, 30)

    # 3. Filter: Darken the square wave, leave transient
    s1.cc(CC.FILTER_CUTOFF, 45)
    s1.cc(CC.FILTER_RES, 0)
    s1.cc(CC.FILTER_ENV, 65)

    # 4. LFO: Pseudo-FM for the Tine/Bell hit
    s1.cc(CC.LFO_MODE, 127) # Audio-Rate LFO
    s1.cc(CC.LFO_RATE, 100) # Fast rate giving inharmonic bell overtones
    s1.cc(CC.PITCH, 40)     # LFO to Pitch, creating the FM tine hit

    # 5. Effects: Classic Chorus and Reverb
    s1.cc(CC.CHORUS_LEVEL, 70) # Essential for the Roland EP sound
    s1.cc(CC.REVERB_LEVEL, 50)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("Electric Piano patch parameters configured.")

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)

    init_patch(s1)

    print("Electric Piano patch loaded.")

    # Demonstration
    demo_chords = [
        [60, 64, 67, 71], # Cmaj7
        [62, 65, 69, 72], # Dmin7
        [55, 59, 62, 65], # G7
        [60, 64, 67, 71]  # Cmaj7
    ]

    for chord in demo_chords:
        for note in chord:
            s1.on(note, velocity=80)
        time.sleep(1.5)
        for note in chord:
            s1.off(note)
        time.sleep(0.1)

    print("Demo complete.")

if __name__ == "__main__":
    main()
