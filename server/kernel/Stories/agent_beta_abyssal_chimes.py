"""
Agent: Beta (Ambient Sound Design)
Patch: Abyssal Chimes
Hardware Target: Roland S-1
Mandate: Crafting spatial, meditative, and evolving environments.

Acoustic Theory & Translation Strategy:
- Inharmonic/Metallic Origin: Employs Agent Alpha rules for 'Strike/Metallic' sounds.
  We drive the LFO to its max limit (~140Hz) and route it to Pitch (CC 17). At higher
  octaves (C5+), the Carrier frequency easily exceeds 140Hz, turning the sidebands into
  a shifting, chorus-like dissonance that mimics uneven bell partials.
- Spatial sparsity: Notes are generated rarely, triggering random intervals in a high register.
- Generative Tail: Heavy reliance on Delay (CC 92) to create cascading, overlapping copies
  of the single strike without actually consuming the 4-voice polyphony limit.
- Envelope Strategy: Sharp attack (0ms), moderate decay to simulate a physical tap
  that dissipates quickly, leaving only the wash.

Taxonomic Application:
[Origin: Strike/Metallic] + [Behavior: Generative] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Bed/Pad]
"""

import time
import random
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_patch(s1: Midi):
    print("Initializing Agent Beta: Abyssal Chimes S-1 Parameters...")

    # --- 1. Master Mix & Oscillators ---
    s1.cc(CC.VOLUME, 90)
    s1.cc(CC.OSC_SQUARE, 110)     # Hollow, odd-harmonic base
    s1.cc(CC.SAW_LEVEL, 40)       # A little bite
    s1.cc(CC.SUB_LEVEL, 0)        # Bells have less fundamental weight
    s1.cc(CC.NOISE_LEVEL, 5)

    # --- 2. Transient Envelope (Strike Physics) ---
    s1.cc(CC.AMP_ATTACK, 0)       # Immediate transient
    s1.cc(CC.AMP_DECAY, 50)       # Brief sharp ring
    s1.cc(CC.AMP_SUSTAIN, 0)      # No sustained body
    s1.cc(CC.AMP_RELEASE, 40)     # Natural fade before effect tail takes over

    # --- 3. Filter Dynamics ---
    s1.cc(CC.FILTER_CUTOFF, 100)  # Open up to hear the metallic harmonics
    s1.cc(CC.FILTER_RES, 60)
    s1.cc(CC.FILTER_ENV, 80)      # Snap the filter shut quickly with the strike
    s1.cc(CC.FILTER_LFO, 0)       # Filter LFO unused.

    # --- 4. Alpha's Bell Trick (High-Rate LFO -> Pitch) ---
    s1.cc(CC.LFO_MODE, 127)       # Audio-Rate (Fast) Mode ~140Hz Cap
    s1.cc(CC.LFO_SHAPE, 0)        # Sine Modulation
    s1.cc(CC.LFO_RATE, 127)       # Max Speed
    s1.cc(CC.PITCH, 45)           # Moderate depth for clangorous sidebands

    # --- 5. Spatial Effects (The Abyss) ---
    s1.cc(CC.REVERB_LEVEL, 80)    # Wide space
    s1.cc(CC.DELAY_LEVEL, 127)    # Infinite cascades. Delay timing is manual on hardware.

    print("Patch Parameter Initialization Complete.")

def generate_abyssal_chimes():
    s1 = Midi()
    
    # Configure the preset
    init_patch(s1)

    print("Beginning Generative Ambient Sequence... (Press Ctrl+C to stop)")

    # High register bell tones (Lydian mode for ethereal quality: C, D, E, F#, G, A, B)
    root = 72 # C5
    scale = [0, 2, 4, 6, 7, 9, 11]

    try:
        while True:
            # 1. Very sparse generation
            if random.random() > 0.4:
                # Trigger a note
                note_idx = random.choice(scale)
                octave_shift = random.choice([0, 12]) # C5 or C6
                midi_note = root + note_idx + octave_shift
                
                velocity = random.randint(30, 90) # Varying strike intensities
                s1.on(midi_note, velocity)
                print(f"Strike: Note {midi_note} (Velocity {velocity})")
                
                # Note off happens very quickly to simulate a percussive strike
                time.sleep(0.1) 
                s1.off(midi_note)
            
            # 2. Generative Timing
            # Extremely long, variable wait times to let the delay do the work
            sleep_time = random.uniform(2.0, 7.0)
            time.sleep(sleep_time)

    except KeyboardInterrupt:
        print("\nSequence Terminated. Sending Panic (All Notes Off).")
        s1.panic()

if __name__ == "__main__":
    generate_abyssal_chimes()
