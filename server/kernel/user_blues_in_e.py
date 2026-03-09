import sys
import os
import time

# Ensure imports resolve
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi
from Stories.gamma_k_guitar_1 import init_patch

def play_chord(s1, notes, duration, velocity=80):
    """Strikes a chord and holds it for the specified duration before releasing."""
    for note in notes:
        s1.on(note, velocity)
    time.sleep(duration)
    for note in notes:
        s1.off(note)

def play_12_bar_blues():
    """
    Plays a 12-bar blues progression in E major at 90 BPM.
    12-Bar Structure:
    I   - I   - I   - I
    IV  - IV  - I   - I
    V   - IV  - I   - V
    """

    s1 = Midi()

    # 1. Initialize the Guitar Patch
    init_patch(s1)
    # Give S-1 a moment to register CCs
    time.sleep(0.2)

    print("\n--- Starting 12-Bar Blues Live Performance ---")
    print("Tempo: 90 BPM")
    print("Key: E")

    # 2. Determine Timing (90 BPM)
    beats_per_minute = 90
    seconds_per_beat = 60.0 / beats_per_minute
    
    # We will play an alternating 'shuffle' pattern per beat
    # A quarter note gets split into a dotted eighth and a sixteenth, 
    # but for simplicity of polyphony, we'll just strike the chord once per beat.
    # We will hold the chord for 80% of the beat's length to allow the envelope 
    # to punch, leaving a 20% gap for rhythm.
    strike_duration = seconds_per_beat * 0.8
    rest_duration = seconds_per_beat * 0.2

    # 3. Define Guitar Voicings (Max 4 voices for S-1)
    # E7: E2 (40), G#3 (56), D4 (62), E4 (64)
    E7 = [40, 56, 62, 64]
    
    # A7: A2 (45), G3 (55), C#4 (61), E4 (64)
    A7 = [45, 55, 61, 64]
    
    # B7: B2 (47), D#3 (51), A3 (57), D#4 (63)
    B7 = [47, 51, 57, 63]

    # The blueprint of the 12 bars (4 beats per bar)
    progression = [
        E7, E7, E7, E7, # Bar 1-4
        A7, A7, E7, E7, # Bar 5-8
        B7, A7, E7, B7  # Bar 9-12
    ]

    try:
        bar_count = 1
        for chord in progression:
            # Print status periodically
            if chord == E7: name = "E7 (I)"
            elif chord == A7: name = "A7 (IV)"
            else: name = "B7 (V)"
            
            print(f"Bar {bar_count}: Playing {name}")
            
            # Play 4 beats per bar
            for _ in range(4):
                # Strumming: Slightly humanize the velocity
                vel = 85 if _ == 0 else 70 # Accent the one
                play_chord(s1, chord, strike_duration, velocity=vel)
                time.sleep(rest_duration)
                
            bar_count += 1

    except KeyboardInterrupt:
        print("\nPerformance interrupted.")
    finally:
        s1.panic()
        print("Performance complete.")


if __name__ == "__main__":
    play_12_bar_blues()
