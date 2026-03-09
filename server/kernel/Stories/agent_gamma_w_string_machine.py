"""
Gordon Reid "Synth Secrets" Chapter 44: String Machines
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
Ensemble string machines (like the Freeman String Synth or Solina) relied on mixing multiple 
detuned oscillators to simulate the random pitch variations of a human string section. 

S-1 Hardware Translation:
1. Since the S-1 has a single primary oscillator core per voice, we mix the true Sawtooth (CC 20) 
   with the Sub-oscillator or Square wave (CC 21) to maximize harmonic density.
2. The core of the "string machine" chorus is achieved by applying a Random (S&H-like) LFO (CC 12: 5) 
   to the Pitch (CC 17) at a low rate (CC 3: ~30-40) and depth (CC 17: ~5-10). 
   This avoids the periodic wobble of a sine/triangle, producing a thick "human" unstable wash.
3. Envelope is a classic pad: moderate attack (CC 73: 40) for the crescendo, maximum sustain (CC 70: 127), 
   and a long release tail (CC 72: 80).
4. VCF Cutoff (CC 74) is rolled off to roughly 50% to emulate the warm, fuzzy limitations of 
   1970s divide-down organ technology.

Taxonomic Application:
[Origin: Artifacting/Emulation] + [Behavior: Evolving] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Pad] + [Historical: String-Machine]
"""

import time
import random
from server.kernel.s1_midi import Midi, CC

def run_string_machine_patch():
    print("Agent Gamma-W: Initializing String Machine (Ch 44) Patch...")
    s1 = Midi()
    
    # Base Oscillator Mix: Sawtooth + Square for dense harmonics
    s1.cc(CC.SAW_LEVEL, 127)
    s1.cc(CC.OSC_SQUARE, 100)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 0)
    
    # Filter: Rolled off low-pass to mimic old circuitry
    s1.cc(CC.FILTER_CUTOFF, 64)
    s1.cc(CC.FILTER_RES, 0)
    s1.cc(CC.FILTER_ENV, 0)
    s1.cc(CC.FILTER_LFO, 0)
    
    # Envelope: Slow crescendo, high sustain, long tail
    s1.cc(CC.AMP_ATTACK, 45)
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)
    s1.cc(CC.AMP_RELEASE, 85)
    
    # LFO Pitch Modulation: Random/S&H wave to "humanize" detuning
    s1.cc(CC.LFO_MODE, 0)      # Normal mode
    s1.cc(CC.LFO_SHAPE, 5)     # 5 = Random (S&H) on S-1
    s1.cc(CC.LFO_RATE, 35)     # Moderate stepping drift
    s1.cc(CC.PITCH, 12)        # Subtle unstable pitch drift
    
    # Effects: Chorus is mandatory for string machines
    s1.cc(CC.CHORUS_LEVEL, 100)
    s1.cc(CC.REVERB_LEVEL, 50)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("Patch initialized. Playing test chord sequence...")
    
    # Test Sequence: I - VI - IV - V progression
    chords = [
        [48, 52, 55, 60], # C Major
        [45, 48, 52, 57], # A minor
        [41, 45, 48, 53], # F Major
        [43, 47, 50, 55]  # G Major
    ]
    
    for _ in range(2):
        for chord in chords:
            # Note on
            for note in chord:
                s1.on(note, velocity=64)
            time.sleep(2.5) # Sustained crescendo
            
            # Note off
            for note in chord:
                s1.off(note)
            time.sleep(1.0) # Let the release tail ring out

    print("String Machine sequence complete.")

if __name__ == "__main__":
    run_string_machine_patch()
