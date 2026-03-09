"""
Gordon Reid "Synth Secrets" Chapter 48: Practical Bowed-String Synthesis continued
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
A truly expressive string synthesizer bypasses ADSR envelopes in favor of continuous physical 
controllers (like a joystick or breath controller) to articulate volume and vibrato dynamically, 
creating a humanized, non-uniform volume swell and decay.

S-1 Hardware Translation:
1. We set the Amp Envelope to an immediate "Gate" shape (0 attack, max sustain) and physically 
   drive the overall S-1 Volume (CC 7) via python to emulate the bowing arm's changing pressure.
2. During the note, the python sequencer continuously sweeps Master Volume (CC 7) up and down, 
   while simultaneously mapping independent LFO Pitch depth changes (CC 17).
3. This creates a "breath-controlled" or "joystick-controlled" articulation that cannot be easily 
   duplicated with static envelopes.

Taxonomic Application:
[Origin: Bow/Friction] + [Behavior: Generative/Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Performative-Control]
"""

import time
import math
from server.kernel.s1_midi import Midi, CC

def run_bowed_strings_2_patch():
    print("Agent Gamma-W: Initializing Bowed Strings 2 (Ch 48) Continuous Control Patch...")
    s1 = Midi()
    
    # Base Oscillator: Sawtooth 
    s1.cc(CC.SAW_LEVEL, 127)
    s1.cc(CC.OSC_SQUARE, 0)
    s1.cc(CC.SUB_LEVEL, 0)
    
    # Filter 
    s1.cc(CC.FILTER_CUTOFF, 80) 
    s1.cc(CC.FILTER_RES, 20)    
    
    # Envelope: Hard Gate (The Python script will handle volume sweeping!)
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)
    s1.cc(CC.AMP_RELEASE, 20) # Slight tail for smoothness
    
    # LFO Pitch settings
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_SHAPE, 1)      
    s1.cc(CC.LFO_RATE, 65)      
    
    # Effects
    s1.cc(CC.CHORUS_LEVEL, 0)
    s1.cc(CC.REVERB_LEVEL, 70)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("Patch initialized. Performing dynamic swells via CC 7 (Volume)...")
    
    notes = [60, 67]
    
    for note in notes:
        # Start note with physical volume at 0
        s1.cc(CC.VOLUME, 0)
        s1.cc(CC.PITCH, 0)
        s1.on(note, velocity=100)
        
        # Crescendo: Sweeping volume up (mimicking bow pressure increase)
        for i in range(0, 100, 2):
            s1.cc(CC.VOLUME, i)
            # Add gradual vibrato
            vibrato = int((i / 100.0) * 15)
            s1.cc(CC.PITCH, vibrato)
            time.sleep(0.05)
            
        time.sleep(1.0) # Hold peak
        
        # Decrescendo: Sweeping volume down
        for i in range(100, -1, -2):
            s1.cc(CC.VOLUME, i)
            vibrato = int((i / 100.0) * 15)
            s1.cc(CC.PITCH, vibrato)
            time.sleep(0.05)
            
        s1.off(note)
        time.sleep(0.5)

    # Restore default volume
    s1.cc(CC.VOLUME, 100)
    s1.cc(CC.PITCH, 0)
    print("Dynamic Bowed Strings 2 sequence complete.")

if __name__ == "__main__":
    run_bowed_strings_2_patch()
