import sys
import os
import time

# Ensure imports resolve
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from s1_midi import Midi, CC

def init_8bit_square(s1: Midi):
    """
    Configures the Roland S-1 to mimic a Nintendo Entertainment System (NES) Pulse Channel.
    - Pure Square Wave
    - No filtering
    - Instant Gate Envelope (On/Off)
    - Absolutely no spatial effects (dry)
    """
    print("--- Loading Patch: 8-Bit NES Pulse Channel ---")

    # 1. Oscillator Mix: 100% Square Wave
    s1.cc(CC.SAW_LEVEL, 0)
    s1.cc(CC.OSC_SQUARE, 127) # The classic video game channel
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 0)

    # 2. Envelope: Instant Gate
    s1.cc(CC.AMP_ATTACK, 0)   # Instant snap on
    s1.cc(CC.AMP_DECAY, 64)   # (Doesn't matter with full sustain)
    s1.cc(CC.AMP_SUSTAIN, 127)# Hold at maximum volume while key is pressed
    s1.cc(CC.AMP_RELEASE, 0)  # Instant snap off

    # 3. Filter: Fully Open (No muffling)
    s1.cc(CC.FILTER_CUTOFF, 127) 
    s1.cc(CC.FILTER_RES, 0)
    s1.cc(CC.FILTER_ENV, 0)

    # 4. Effects: Completely Dry
    s1.cc(CC.CHORUS_LEVEL, 0) 
    s1.cc(CC.REVERB_LEVEL, 0)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("8-Bit patch parameters configured.")

def play_mario():
    s1 = Midi()

    # Apply the NES patch
    s1.panic()
    time.sleep(0.1)
    init_8bit_square(s1)
    time.sleep(0.2) 

    # --- Musical Timing Setup ---
    BPM = 100
    BEAT = 60.0 / BPM
    
    # Koji Kondo's Mario revolves around heavily syncopated 16th/8th notes.
    T_16 = BEAT / 4.0   # A 16th note length
    T_8  = BEAT / 2.0   # An 8th note length
    
    # We define a helper so the note sounds "staccato" (bouncy) like the original game.
    # It will only hold the note down for 60% of its duration, remaining silent for 40%.
    def p(note, duration_ticks):
        """Play a staccato note for a specific number of 16th-note ticks."""
        total_time = duration_ticks * T_16
        strike_time = total_time * 0.6
        rest_time = total_time * 0.4
        
        if note > 0:
            s1.on(note, 90)
            time.sleep(strike_time)
            s1.off(note)
            time.sleep(rest_time)
        else:
            # If note is 0, it's a pure musical rest
            time.sleep(total_time)

    # Note Definitions
    E5 = 76
    C5 = 72
    G5 = 79
    G4 = 67
    E4 = 64
    A4 = 69
    B4 = 71
    Bb4= 70
    A5 = 81
    F5 = 77
    D5 = 74

    print("\n--- Playing Super Mario Bros Level 1-1 ---")

    try:
        # ==========================================
        # THE INTRO
        # ==========================================
        print("Playing: Intro")
        
        p(E5, 1) # e
        p(E5, 2) # e
        p(E5, 2) # e
        p(C5, 1) # c
        p(E5, 2) # e
        
        p(G5, 4) # HIGH G
        p(G4, 4) # LOW G

        print("Playing: Section A")
        # ==========================================
        # SECTION A (Part 1)
        # ==========================================
        p(C5, 3) 
        p(G4, 2) 
        p(0,  1) # rest
        p(E4, 3) 
        
        p(A4, 2) 
        p(B4, 2) 
        p(Bb4, 1)
        p(A4, 2) 
        
        p(G4, 1.5) # slightly swung triplet feel
        p(E5, 1.5)
        p(G5, 1) 
        
        p(A5, 2) 
        p(F5, 1) 
        p(G5, 2) 
        
        p(E5, 2) 
        p(C5, 1) 
        p(D5, 1) 
        p(B4, 3)

        # ==========================================
        # SECTION A (Part 2 - Repeat)
        # ==========================================
        p(C5, 3) 
        p(G4, 2) 
        p(0,  1) # rest
        p(E4, 3) 
        
        p(A4, 2) 
        p(B4, 2) 
        p(Bb4, 1)
        p(A4, 2) 
        
        p(G4, 1.5) 
        p(E5, 1.5)
        p(G5, 1) 
        
        p(A5, 2) 
        p(F5, 1) 
        p(G5, 2) 
        
        p(E5, 2) 
        p(C5, 1) 
        p(D5, 1) 
        p(B4, 3)

    except KeyboardInterrupt:
        print("\nGameplay interrupted.")
    finally:
        s1.panic()
        print("1-up!")


if __name__ == "__main__":
    play_mario()
