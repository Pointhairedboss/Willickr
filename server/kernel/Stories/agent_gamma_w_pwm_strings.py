"""
Gordon Reid "Synth Secrets" Chapter 45: PWM & String Sounds
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
Pulse Wave Modulation (PWM) is the core of synthesizing lush analog patches without the DSP cost 
of multiple oscillators. Modulating a pulse width creates beating frequencies and sidebands that 
mimic chorusing and double-tracking perfectly.

S-1 Hardware Translation:
1. We emulate the "chorusing" of PWM by pitting the core Sawtooth oscillator against a heavily 
   LFO-modulated Square wave. 
2. LFO (CC 12: 1 = Triangle) is routed mapped to Pitch (CC 17) at a slightly higher rate than the 
   previous String Machine patch, providing the cyclic beating intrinsic to true hardware PWM.
3. Envelope shares the same "String Pad" DNA: soft attack (CC 73), full sustain (CC 70), 
   and a gentle release (CC 72).
4. Filter (CC 74) is opened slightly more to allow the upper harmonic sidebands of the beating 
   to cut through the mix.

Taxonomic Application:
[Origin: Emulation/Synthesis] + [Behavior: Rhythmic] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Pad] + [Historical: PWM-Synthesis]
"""

import time
from server.kernel.s1_midi import Midi, CC

def run_pwm_strings_patch():
    print("Agent Gamma-W: Initializing PWM Strings (Ch 45) Patch...")
    s1 = Midi()
    
    # Base Oscillator Mix: Focus heavily on the interaction between Saw and Square
    s1.cc(CC.SAW_LEVEL, 110)
    s1.cc(CC.OSC_SQUARE, 110)
    s1.cc(CC.SUB_LEVEL, 30)    # Add slight 16' weight
    s1.cc(CC.NOISE_LEVEL, 0)
    
    # Filter: More open than the String Machine to reveal PWM harmonics
    s1.cc(CC.FILTER_CUTOFF, 85)
    s1.cc(CC.FILTER_RES, 0)
    s1.cc(CC.FILTER_ENV, 0)
    s1.cc(CC.FILTER_LFO, 0)
    
    # Envelope: Smooth pad
    s1.cc(CC.AMP_ATTACK, 50)
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)
    s1.cc(CC.AMP_RELEASE, 75)
    
    # LFO Pitch Modulation: Triangle wave for cyclic PWM imitation
    s1.cc(CC.LFO_MODE, 0)      # Normal
    s1.cc(CC.LFO_SHAPE, 1)     # 1 = Tri/Sine for smooth sweeping
    s1.cc(CC.LFO_RATE, 45)     # Beating chorus rate
    s1.cc(CC.PITCH, 18)        # Noticeable cyclic beating depth
    
    # Effects: Let the DSP do its job
    s1.cc(CC.CHORUS_LEVEL, 70)
    s1.cc(CC.REVERB_LEVEL, 60)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("Patch initialized. Playing test chord sequence...")
    
    # Test Sequence: Lush extended chords
    chords = [
        [48, 55, 59, 64], # Cmaj7
        [43, 50, 53, 58], # Gmin7
        [41, 48, 52, 57], # Fmaj7
        [45, 52, 55, 60]  # Amin7
    ]
    
    for chord in chords:
        for note in chord:
            s1.on(note, velocity=64)
        time.sleep(3.0) 
        
        for note in chord:
            s1.off(note)
        time.sleep(1.5) 

    print("PWM Strings sequence complete.")

if __name__ == "__main__":
    run_pwm_strings_patch()
