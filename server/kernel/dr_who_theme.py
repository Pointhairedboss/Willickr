import sys
import os
import time

# Ensure imports resolve
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from s1_midi import Midi, CC

def init_who_bass(s1: Midi):
    """
    Simulates the punchy, resonant analog bass (e.g., Peter Howell's ARP Odyssey).
    - Heavy sawtooth foundation
    - Snappy filter envelope with high resonance
    - Short decay, no sustain
    """
    s1.cc(CC.SAW_LEVEL, 127)     
    s1.cc(CC.OSC_SQUARE, 0)     
    s1.cc(CC.SUB_LEVEL, 100)      # Thick sub frequency
    s1.cc(CC.NOISE_LEVEL, 0)
    
    # Snappy Filter
    s1.cc(CC.FILTER_CUTOFF, 10)  
    s1.cc(CC.FILTER_ENV, 100)    
    s1.cc(CC.FILTER_RES, 60)     # Analog "squelch" on the attack
    
    # Sharp Amplifier
    s1.cc(CC.AMP_ATTACK, 0)      
    s1.cc(CC.AMP_DECAY, 50)      
    s1.cc(CC.AMP_SUSTAIN, 0)     
    s1.cc(CC.AMP_RELEASE, 30) 
    
    # Performance
    s1.cc(5, 0)      # Bass requires absolute rigid timing (CC 5 = Portamento)

def init_who_melody(s1: Midi):
    """
    Simulates Delia Derbyshire's test-tone oscillator "swoop".
    - Pure, hollow tone (Square/Sub)
    - Fully open filter
    - Long attack and release (Swoop)
    - Extreme Portamento (Glide)
    """
    s1.cc(CC.SAW_LEVEL, 0)  
    s1.cc(CC.OSC_SQUARE, 100) # Closer to a sine/test-tone when filtered
    s1.cc(CC.SUB_LEVEL, 0)   
    s1.cc(CC.NOISE_LEVEL, 0)
    
    # Partially Closed Filter for a purer, flute-like sine wave
    s1.cc(CC.FILTER_CUTOFF, 100) # Opened higher so C6/D6 soaring notes are audible!
    s1.cc(CC.FILTER_RES, 0)    
    s1.cc(CC.FILTER_ENV, 0)   
    
    # Strip ALL modulations that cause pulsing/sirens
    s1.cc(CC.LFO_RATE, 0)
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.PITCH, 0)
    s1.cc(CC.FILTER_LFO, 0)
    s1.cc(CC.CHORUS_LEVEL, 0)
    
    # Floating Amplifier
    s1.cc(CC.AMP_ATTACK, 50)  # Fade in
    s1.cc(CC.AMP_DECAY, 60)
    s1.cc(CC.AMP_SUSTAIN, 100) 
    s1.cc(CC.AMP_RELEASE, 60) # Fade out
    
    # Performance
    s1.cc(5, 50)  # Moderate glide between notes (CC 5 = Portamento)


def play_doctor_who():
    s1 = Midi()

    print("\n--- Starting Hardware Hijack: The TARDIS Materializes ---")
    print("WARNING: Parameter locking the S-1 multiple times per beat!")

    s1.panic()
    time.sleep(0.5)

    # Base Reverb for the whole patch
    s1.cc(CC.REVERB_LEVEL, 60)   
    s1.cc(CC.DELAY_LEVEL, 40)    # Spacey tape delay!
    
    # --- Timing Setup ---
    # The Doctor Who bassline is fundamentally triplets.
    # A "dum-de-dum" block is [2-triplets length], [1-triplet length], [1/4 note length].
    BPM = 110
    BEAT = 60.0 / BPM
    T_TRIPLET = BEAT / 3.0    # One eighth-note triplet
    
    # --- Note Definitions (E Minor) ---
    E1 = 28; E2 = 40; G2 = 43; B2 = 47
    
    # Melody notes (High Octave for Soaring Lead)
    E5 = 76; G5 = 79
    B5 = 83; C6 = 84; D6 = 86; A5 = 81
    
    # We will loop just the iconic 2-bar "Intro" bass block repeatedly.
    # The Bass Block format: (Note, Triplet_Duration_Multiplier)
    bass_intro_block = [
        (E2, 2),  # "dum" (long)
        (E2, 1),  # "de"  (short)
        (E2, 3),  # "dum" (quarter note = 3 triplets)
        
        (E2, 2),  # "dum"
        (E2, 1),  # "de"
        (E2, 3),  # "dum"
        
        (E2, 1),  # "did"
        (E2, 1),  # "dly"
        (E2, 1),  # "dum"
        (G2, 2),  # "dum..." (high)
        (E1, 1),  # "...dum" (low drop)
        (E2, 3),  # "did-dy" (resolved)
    ]
    
    # Melody arrives with the famous triplet swoop (E-G-B)
    # Format: (Note, Start_Beat_Offset, Duration_In_Beats)
    melody_phrase = [
        # The Swoop (3 fast eighth-note triplets leading into beat 4)
        (E5, 3.00,  0.33),
        (G5, 3.33,  0.33),
        (B5, 3.66,  0.33),
        
        # The Main Melody
        (B5, 4.0,  1.5),  # Swells in high
        (C6, 6.0,  2.0),  # Climbs
        (B5, 8.0,  2.0),  # Drops back
        (D6, 10.0, 2.0),  # Soars high
        (A5, 12.0, 4.0)   # Resolves and holds
    ]
    
    melody_index = 0
    current_beat = 0.0

    print("Materializing the 1980s ARP Odyssey Bass...")

    try:
        # Loop the 2-Bar Bassline 4 times
        for loop in range(4):
            print(f"Time Rotor Cycle {loop+1}/4")
            
            for note, dur_multiplier in bass_intro_block:
                note_duration_seconds = dur_multiplier * T_TRIPLET
                
                # --- CHECK MELODY TRIGGER ---
                # Should the sweeping test-oscillator melody trigger right now?
                # We check if the current global beat matches the melody's requested start time.
                active_melody_note = None
                if melody_index < len(melody_phrase):
                    m_note, m_start, m_dur = melody_phrase[melody_index]
                    # Give a small epsilon window for floating point math
                    if abs(current_beat - m_start) < 0.1:
                        active_melody_note = m_note
                        melody_index += 1
                
                # --- INTERLEAVED PERFORMANCE ---
                
                # 1. Morph to Melody Patch (If needed)
                if active_melody_note:
                    init_who_melody(s1)
                    s1.on(active_melody_note, 100)
                    time.sleep(0.05) # Tiny beat to let the portamento grab
                
                # 2. Morph back to Bass Patch
                init_who_bass(s1)
                
                # 3. Strike the Bass Note
                strike_duration = note_duration_seconds * 0.8
                rest_duration = note_duration_seconds * 0.2
                
                s1.on(note, 110)
                time.sleep(strike_duration)
                
                # 4. Silence Bass (But let Melody ring because it has a long release!)
                s1.off(note)
                time.sleep(rest_duration)
                
                # Advance time
                current_beat += (dur_multiplier / 3.0) 

    except KeyboardInterrupt:
        print("\nTARDIS Engine halted manually.")
    finally:
        s1.panic()
        print("\nTime Vortex exited.")

if __name__ == "__main__":
    play_doctor_who()
