"""
Agent Gamma-K: Acoustic Piano Transcription
Source: Gordon Reid's Synth Secrets (Chapters 40-43)

Acoustic Theory & Translation Strategy:
- The acoustic piano's primary characteristic is its hammered string physics. The hammer strike is an extremely fast transient followed by a complex evolving decay.
- To avoid S-1 voice-stealing clicks on 4-voice chords, we use a relatively short AMP_RELEASE. 
- The initial hammer transient is simulated by a sharp, fast decay on the FILTER_ENV, starting bright and snapping to a darker sustain.
- We simulate the complex "tricord" by mixing the Sawtooth and Sub oscillators.

Taxonomic Application:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]
"""

import time
from s1_midi import Midi, CC

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)

    print("--- Loading Patch: Acoustic Piano (Gamma-K) ---")

    # 1. Oscillator Mix: Rich harmonic base
    s1.cc(CC.SAW_LEVEL, 110)
    s1.cc(CC.SUB_LEVEL, 60)
    s1.cc(CC.OSC_SQUARE, 10)
    s1.cc(CC.NOISE_LEVEL, 5) # Slight mechanical hammer noise

    # 2. Envelope: Sharp strike, decaying sustain, short release
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 65)
    s1.cc(CC.AMP_SUSTAIN, 20)
    s1.cc(CC.AMP_RELEASE, 25) # Short enough to prevent clicking on chord changes

    # 3. Filter: Pluck simulation (Hammer strike)
    s1.cc(CC.FILTER_CUTOFF, 40) # Dark body
    s1.cc(CC.FILTER_RES, 10)
    s1.cc(CC.FILTER_ENV, 80) # Strong envelope depth for the hammer 'ping'

    # 4. LFO: Negligible for straight acoustic piano
    s1.cc(CC.PITCH, 0)
    s1.cc(CC.FILTER_LFO, 0)

    # 5. Effects: Room / Soundboard resonance
    s1.cc(CC.REVERB_LEVEL, 60)
    s1.cc(CC.DELAY_LEVEL, 10)
    s1.cc(CC.CHORUS_LEVEL, 5)

    print("Acoustic Piano patch loaded.")

    # Demonstration
    demo_chords = [
        [48, 55, 60, 64], # C major
        [50, 57, 62, 65], # D minor
        [43, 50, 55, 59], # G major
        [48, 55, 60, 64]  # C major
    ]

    for chord in demo_chords:
        for note in chord:
            s1.on(note, velocity=90)
        time.sleep(1.2)
        for note in chord:
            s1.off(note)
        time.sleep(0.2)
        
    print("Demo complete.")

if __name__ == "__main__":
    main()
