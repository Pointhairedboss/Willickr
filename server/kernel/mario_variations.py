import sys
import os
import time
import random
import importlib

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from s1_midi import Midi, CC

# List of explicitly verified patches that contain an init_patch(s1) method.
# We are dynamically importing to keep this script isolated and modular!
PATCHES_TO_USE = [
    "Stories.agent_gamma_brass_1",
    "Stories.agent_gamma_k_piano_electric",
    "Stories.gamma_k_guitar_1",
    "Stories.agent_beta_glacial_pad",
    "Stories.agent_beta_abyssal_chimes",
]

# Note Definitions
E5 = 76; C5 = 72; G5 = 79; G4 = 67; E4 = 64
A4 = 69; B4 = 71; Bb4= 70; A5 = 81; F5 = 77; D5 = 74

MARIO_INTRO = [
    (E5, 1), (E5, 2), (E5, 2), (C5, 1), (E5, 2), (G5, 4), (G4, 4)
]

MARIO_A_SECTION = [
    (C5, 3), (G4, 2), (0, 1), (E4, 3), (A4, 2), (B4, 2), (Bb4, 1), (A4, 2),
    (G4, 1.5), (E5, 1.5), (G5, 1), (A5, 2), (F5, 1), (G5, 2),
    (E5, 2), (C5, 1), (D5, 1), (B4, 3)
]

def play_marathon():
    s1 = Midi()
    
    BPM = 100
    BEAT = 60.0 / BPM
    T_16 = BEAT / 4.0
    
    print("\n==============================================")
    print("=  SUPER MARIO MULTIVERSE (10 VARIATIONS)    =")
    print("==============================================")
    print("Rest assured: No Agent script source code is being modified.")
    print("We are simply reading their parameters and playing them.\n")

    try:
        for iteration in range(1, 11):
            # Select a patch (Cycle through the 5 patches twice)
            patch_name = PATCHES_TO_USE[(iteration - 1) % len(PATCHES_TO_USE)]
            
            # Dynamically import the patch module
            module = importlib.import_module(patch_name)
            
            s1.panic()
            time.sleep(0.2)
            
            print(f"\n--- Variation {iteration} / 10 ---")
            print(f"Applying Patch: {patch_name.split('.')[-1]}")
            module.init_patch(s1)
            time.sleep(0.3)
            
            # --- Generative Inclusions for this iteration ---
            # 1. Base Velocity Variance:
            velocity_base = random.randint(70, 110)
            
            # 2. Additive Octave Jumps: (10% chance to jump an octave high)
            octave_chaos = True if iteration > 3 else False
            
            # 3. Time Manipulation: Slightly swing the BPM on later iterations
            current_bpm = BPM + random.randint(-10, 15)
            current_t_16 = (60.0 / current_bpm) / 4.0
            
            # 4. Filter Modulation: For ambient patches, we might force the filter slightly
            if "beta" in patch_name:
                print(" -> Injecting generative ambient glitch (Slow filter sweep)")
                s1.cc(CC.LFO_RATE, random.randint(10, 30))
                s1.cc(CC.FILTER_LFO, 60)
            
            print(f" -> Tempo: {current_bpm} BPM | Base Vel: {velocity_base}")

            def play_sequence(sequence):
                for note, duration_ticks in sequence:
                    total_time = duration_ticks * current_t_16
                    strike_time = total_time * 0.7
                    rest_time = total_time * 0.3
                    
                    if note > 0:
                        # Generative Octave Jump
                        play_note = note
                        if octave_chaos and random.random() > 0.90:
                            play_note += 12 # Jump an octave!
                            
                        # Humanize the velocity
                        vel = min(127, max(10, int(velocity_base + random.uniform(-15, 15))))
                        
                        s1.on(play_note, vel)
                        time.sleep(strike_time)
                        s1.off(play_note)
                        time.sleep(rest_time)
                    else:
                        time.sleep(total_time)

            # Play intro and A section twice
            play_sequence(MARIO_INTRO)
            play_sequence(MARIO_A_SECTION)
            play_sequence(MARIO_A_SECTION)
            
            time.sleep(1.0) # Rest between variations

    except KeyboardInterrupt:
        print("\nMarathon aborted.")
    finally:
        s1.panic()
        print("\nMultiverse playback complete.")

if __name__ == "__main__":
    play_marathon()
