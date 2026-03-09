"""
Gordon Reid "Synth Secrets" Chapter 52: Practical Flute Synthesis
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
The orchestral flute is an open cylinder with complex harmonics up to about 2kHz. 
Most importantly: A flute does not get significantly louder or softer as blowing pressure changes; 
it becomes brighter or duller. Therefore, traditional Pitch Vibrato (FM) and Amp Tremolo (AM) are 
wrong. A flute requires "Tonal Vibrato" — cyclic changes in brightness.

S-1 Hardware Translation:
1. Core Sound: Sawtooth/Square mix, but heavily low-pass filtered.
2. The Envelope is a rectangular block (Gate): Fast attack, full sustain, fast release to prevent "sucking".
3. Vibrato: We route a 5-6Hz LFO strictly to the Filter Cutoff (CC 28) and ensure Pitch/Amp LFO are 0.
4. No white noise! Unlike the pan-pipes, adding generic white noise to the modern silver flute 
   destroys its pure tone.

Taxonomic Application:
[Origin: Edge-Blown] + [Behavior: Tremulous] + [Emotion: Ethereal] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]
"""

import time
from server.kernel.s1_midi import Midi, CC

def run_flute_patch():
    print("Agent Gamma-W: Initializing Orchestral Flute (Ch 52) Patch...")
    s1 = Midi()
    
    # Base Oscillator: Mixed, heavy on square for hollow depth
    s1.cc(CC.SAW_LEVEL, 60)
    s1.cc(CC.OSC_SQUARE, 110)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 0) # No noise! Silver flutes are relatively pure.
    
    # Filter: Low pass set around "2kHz" visual equivalent
    s1.cc(CC.FILTER_CUTOFF, 75) 
    s1.cc(CC.FILTER_RES, 25)    # Acts slightly like a high-pass to thin the low end
    s1.cc(CC.FILTER_ENV, 0)     # No discrete envelope tracking
    
    # The Secret Sauce: Tonal Vibrato (Brightness Modulation)
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_SHAPE, 1)      # Sine/Triangle for smooth vibrato
    s1.cc(CC.LFO_RATE, 65)      # 5-6 Hz
    s1.cc(CC.PITCH, 0)          # NO PITCH VIBRATO
    s1.cc(CC.FILTER_LFO, 18)    # LFO modulates Cutoff to simulate breath pressure variance
    
    # Envelope: Almost a block wave
    s1.cc(CC.AMP_ATTACK, 18)    # Not instant, but fast
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)  # Full sustain
    s1.cc(CC.AMP_RELEASE, 30)   # Quick release to prevent unnatural sucking
    
    # Effects
    s1.cc(CC.CHORUS_LEVEL, 10)
    s1.cc(CC.REVERB_LEVEL, 85)
    s1.cc(CC.DELAY_LEVEL, 20)
    
    print("Patch initialized. Playing phrase with cyclic Tonal Vibrato...")
    
    # Lyrical phrase
    notes = [72, 76, 79, 74, 76]
    
    for note in notes:
        s1.on(note, velocity=80)
        time.sleep(1.2) # Allow tonal vibrato to cycle multiple times
        s1.off(note)
        time.sleep(0.1)

    print("Orchestral Flute sequence complete.")

if __name__ == "__main__":
    run_flute_patch()
