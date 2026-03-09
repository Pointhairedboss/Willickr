import time
import random
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

"""
Agent Delta: Stochastic Pseudo-FM Sequencer

Acoustic Theory & Synthesis Strategy:
This script employs a stochastic probability matrix to generate an unpredictable
sequence of MIDI notes and pseudo-FM modulation properties. The Roland S-1 lacks a
true FM matrix, but we create "Index Modulation" by running the LFO in Audio-Rate 
mode (Fast) and patching it to Pitch.

Because the maximum LFO rate is ~140Hz, true FM sidebands are only created in the 
bass/tenor registers. We use Python as a parameter-locking sequencer to occasionally
shift the LFO rate, morphing the M:C ratio and producing glitchy, inharmonic
textures that drift towards chorusing in higher octaves.

Taxonomic Application:
[Origin: System] + [Behavior: Generative] + [Emotion: Abrasive] + [Stress: Edge-Case] + [Role: Lead]
"""

def get_next_note(current_note, scale):
    """Simple 1st-order Markov chain / stochastic step."""
    # 60% chance to move a step in the scale, 20% to jump, 20% stay
    r = random.random()
    idx = scale.index(current_note) if current_note in scale else 0
    if r < 0.6:
        # Step up or down
        idx += random.choice([-1, 1])
    elif r < 0.8:
        # Jump
        idx += random.choice([-3, 3])
    
    # Wrap index safely
    idx = max(0, min(len(scale) - 1, idx))
    return scale[idx]

def run_stochastic_fm_patch():
    print("Agent Delta: Initializing Stochastic Pseudo-FM patch...")
    try:
        synth = Midi()
    except Exception as e:
        print(f"Failed to connect: {e}")
        return

    # Basic setup
    synth.cc(CC.VOLUME, 100)
    synth.cc(CC.OSC_SQUARE, 0)
    synth.cc(CC.SAW_LEVEL, 127) # Saw carrier
    synth.cc(CC.SUB_LEVEL, 60)
    
    # Filter Setup - Open
    synth.cc(CC.FILTER_CUTOFF, 127)
    synth.cc(CC.FILTER_RES, 0)
    synth.cc(CC.FILTER_ENV, 0)
    
    # Envelope Setup - Pluck physics
    synth.cc(CC.AMP_ATTACK, 0)
    synth.cc(CC.AMP_DECAY, 50)
    synth.cc(CC.AMP_SUSTAIN, 0)
    synth.cc(CC.AMP_RELEASE, 30)
    
    # --- Pseudo-FM Setup ---
    synth.cc(CC.LFO_MODE, 127) # Audio-rate mode
    synth.cc(CC.LFO_SHAPE, 0) # Sine wave
    synth.cc(CC.PITCH, 100) # Deep modulation index
    
    # Stochastic limits
    minor_pentatonic = [33, 36, 38, 40, 43, 45, 48, 50, 52, 55, 57, 60, 62, 64, 67]
    bpm = 90
    step_time = (60.0 / bpm) / 4.0
    
    print("Beginning generative sequence. Press Ctrl+C to stop.")
    
    # State tracking
    current_note = 48
    
    try:
        step = 0
        while True:
            # Stochastically choose note
            current_note = get_next_note(current_note, minor_pentatonic)
            
            # Stochastic parameter locks for M:C Ratio (LFO Rate)
            # Roughly every 8 steps, alter the "modulator" frequency
            if random.random() < 0.15:
                # Randomize LFO rate (Modulator) to alter sidebands
                # In fast mode, 0-127 maps roughly to 10Hz-140Hz
                new_modulator = random.randint(40, 127) 
                synth.cc(CC.LFO_RATE, new_modulator)
                print(f"[Lock] LFO Rate -> {new_modulator} (Morphing FM Ratio)")
                
            # Randomize velocity for dynamic index
            velocity = random.randint(50, 127)
            
            # Dynamic decay based on note height (higher notes = pluckier)
            if current_note > 50:
                synth.cc(CC.AMP_DECAY, random.randint(20, 40))
            else:
                synth.cc(CC.AMP_DECAY, random.randint(50, 90))
                
            synth.on(current_note, velocity)
            
            # Random chance for a 'glitch' ratcheting delay
            if random.random() < 0.05:
                # Play note again rapidly
                time.sleep(step_time / 4)
                synth.off(current_note)
                synth.on(current_note, velocity)
                time.sleep((step_time * 3) / 4)
            else:
                time.sleep(step_time)
                
            synth.off(current_note)
            step += 1
            
    except KeyboardInterrupt:
        print("\nAgent Delta sequence terminated.")
        synth.cc(CC.PITCH, 0) # Reset pitch mod
        synth.panic()

if __name__ == "__main__":
    run_stochastic_fm_patch()
