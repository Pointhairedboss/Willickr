"""
Agent Gamma-K: Transistor Combo Organ Transcription
Source: Gordon Reid's Synth Secrets (Adaptation)

Acoustic Theory & Translation Strategy:
- 1960s Transistor Combo organs (Vox Continental, Farfisa) used divide-down oscillators, fundamentally producing square and pulse waves.
- They possess a thinner, brighter, "cheesier" tone compared to the mighty Hammond.
- We rely heavily on the Square wave and a fast, wide Pitch Vibrato (LFO) which is a signature of the combo organ sound.
- No key click is synthesized, as their contact mechanics differed and their filters were often completely static or rudimentary.
- The Amplifier remains a strict Gate.

Taxonomic Application:
[Origin: Strike] + [Behavior: Static] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Transistor-Combo]
"""

import time
from s1_midi import Midi, CC

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)

    print("--- Loading Patch: 60s Combo Organ (Gamma-K) ---")

    # 1. Oscillator Mix: Thin, buzzy square wave dominance
    s1.cc(CC.SAW_LEVEL, 20)
    s1.cc(CC.SUB_LEVEL, 30)
    s1.cc(CC.OSC_SQUARE, 127) # Core of the combo sound
    s1.cc(CC.NOISE_LEVEL, 0)

    # 2. Envelope (VCA): Pure Gate
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)
    s1.cc(CC.AMP_RELEASE, 0)

    # 3. Filter: Wide open, static, bright
    s1.cc(CC.FILTER_CUTOFF, 110)
    s1.cc(CC.FILTER_RES, 0)
    s1.cc(CC.FILTER_ENV, 0) # No key click

    # 4. LFO: Deep, fast vibrato (Signature Vox/Farfisa effect)
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_RATE, 75)  # Fast vibrato
    s1.cc(CC.PITCH, 18)     # Noticeable pitch wobble

    # 5. Effects: Short spring reverb imitation
    s1.cc(CC.CHORUS_LEVEL, 10)
    s1.cc(CC.REVERB_LEVEL, 40)
    s1.cc(CC.DELAY_LEVEL, 0)

    print("Combo Organ patch loaded.")

    # Demonstration (Classic 60s rhythmic stabs)
    demo_chords = [
        [60, 64, 67], # C
        [60, 64, 67],
        [65, 69, 72], # F
        [65, 69, 72],
        [67, 71, 74], # G
        [60, 64, 67]  # C
    ]

    for chord in demo_chords:
        for note in chord:
            s1.on(note, velocity=100)
        time.sleep(0.2)
        for note in chord:
            s1.off(note)
        time.sleep(0.3)

    print("Demo complete.")

if __name__ == "__main__":
    main()
