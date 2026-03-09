"""
Gordon Reid "Synth Secrets" Chapter 50: Synthesizing Pan Pipes
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
A pan pipe is a cylindrical pipe closed at one end, which generates only odd harmonics 
(similar to a square/triangle wave). Excitng the air across a sharp edge creates intense 
turbulence (breathy noise). A characteristic "chiff" (percussive burst of noise) heard at the 
start of the note is fundamental to its authentic sound.

S-1 Hardware Translation:
1. Core sound: Square wave (CC 21) only, to isolate odd harmonics. No Sawtooth.
2. Moderate constant Noise (CC 22) to emulate the continuous air stream.
3. The "Chiff": Since we can't easily patch an independent secondary envelope to the noise generator, 
   we handle the chiff programmatically. The Python script injects a high level of Noise for a few 
   milliseconds at Note On, then rapidly scales it back down to the sustained breath level.
4. Filter (CC 74) is rolled off to round the square into a flute-like tone.

Taxonomic Application:
[Origin: Edge-Blown] + [Behavior: Percussive Attack] + [Emotion: Meditative] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]
"""

import time
from server.kernel.s1_midi import Midi, CC

def run_pan_pipes_patch():
    print("Agent Gamma-W: Initializing Pan Pipes (Ch 50) Patch...")
    s1 = Midi()
    
    # Base Oscillator: Square wave for odd harmonics + base noise
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.OSC_SQUARE, 127)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 30) # Sustained breath noise
    
    # Filter 
    s1.cc(CC.FILTER_CUTOFF, 65) # Round off the square
    s1.cc(CC.FILTER_RES, 15)    # Slight resonance for edge
    s1.cc(CC.FILTER_ENV, 0)
    s1.cc(CC.FILTER_LFO, 0)
    
    # Envelope: Fast attack, max sustain
    s1.cc(CC.AMP_ATTACK, 10)
    s1.cc(CC.AMP_DECAY, 20)
    s1.cc(CC.AMP_SUSTAIN, 100)
    s1.cc(CC.AMP_RELEASE, 35)
    
    # LFO
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_SHAPE, 1)      
    s1.cc(CC.LFO_RATE, 65)      
    s1.cc(CC.PITCH, 3) # Very subtle pitch instability
    
    # Effects
    s1.cc(CC.CHORUS_LEVEL, 0)
    s1.cc(CC.REVERB_LEVEL, 75)
    s1.cc(CC.DELAY_LEVEL, 40)
    
    print("Patch initialized. Engaging programmatic Chiff...")
    
    notes = [72, 74, 76, 79, 76, 72] # Pentatonic phrase
    
    for note in notes:
        # The Chiff: Peak noise at the beginning
        s1.cc(CC.NOISE_LEVEL, 127)
        s1.on(note, velocity=100)
        
        # Rapid decay of the noise chiff
        time.sleep(0.04)
        s1.cc(CC.NOISE_LEVEL, 80)
        time.sleep(0.04)
        s1.cc(CC.NOISE_LEVEL, 40)
        
        # Sustain note with constant breath noise
        time.sleep(0.4)
        s1.off(note)
        time.sleep(0.1)

    print("Pan Pipes sequence complete.")

if __name__ == "__main__":
    run_pan_pipes_patch()
