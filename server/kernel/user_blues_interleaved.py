import sys
import os
import time

# Ensure imports resolve
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def fast_guitar_init(s1):
    """Directly sets ONLY the parameters needed to swap to Guitar mode."""
    s1.cc(CC.SAW_LEVEL, 127)     
    s1.cc(CC.OSC_SQUARE, 60)     
    s1.cc(CC.SUB_LEVEL, 40)      
    s1.cc(CC.NOISE_LEVEL, 0)
    s1.cc(CC.FILTER_CUTOFF, 15)  
    s1.cc(CC.FILTER_ENV, 100)    
    s1.cc(CC.FILTER_RES, 30)     
    s1.cc(CC.AMP_ATTACK, 0)      
    s1.cc(CC.AMP_DECAY, 65)      
    s1.cc(CC.AMP_SUSTAIN, 0)     
    s1.cc(CC.AMP_RELEASE, 55)    

def fast_brass_init(s1):
    """Directly sets ONLY the parameters needed to swap to Brass mode."""
    s1.cc(CC.SAW_LEVEL, 127)  
    s1.cc(CC.OSC_SQUARE, 0)
    s1.cc(CC.SUB_LEVEL, 40)   
    s1.cc(CC.NOISE_LEVEL, 0)
    s1.cc(CC.AMP_ATTACK, 25)  
    s1.cc(CC.AMP_DECAY, 80)
    s1.cc(CC.AMP_SUSTAIN, 95) 
    s1.cc(CC.AMP_RELEASE, 30) 
    s1.cc(CC.FILTER_CUTOFF, 15) 
    s1.cc(CC.FILTER_RES, 25)    
    s1.cc(CC.FILTER_ENV, 110)   

def play_interleaved_blues():
    s1 = Midi()

    print("\n--- Starting Interleaved Hardware Hijack ---")
    print("WARNING: Parameter locking the S-1 multiple times per beat!")

    # Base Reverb for the whole patch to try and glue the choppy transitions together
    s1.cc(CC.REVERB_LEVEL, 50)   
    s1.cc(CC.DELAY_LEVEL, 0)
    
    # 2. Determine Timing (90 BPM)
    beats_per_minute = 90
    seconds_per_beat = 60.0 / beats_per_minute
    
    # We slice the beat into 8th notes to fit two instruments
    eighth_note_duration = seconds_per_beat / 2.0
    
    # We must cut off notes strictly *before* CC manipulation to avoid the hardware 
    # warping the tail of the chord when the envelope snaps to the new patch.
    strike_duration = eighth_note_duration * 0.7
    rest_duration = eighth_note_duration * 0.3

    E7 = [40, 56, 62, 64]
    A7 = [45, 55, 61, 64]
    B7 = [47, 51, 57, 63]

    progression = [
        E7, E7, E7, E7,
        A7, A7, E7, E7,
        B7, A7, E7, B7
    ]

    # The pentatonic-ish melody phrase played over 4 beats
    brass_melody_offsets = [0, 3, 0, 5]

    def get_melody_base(chord):
        if chord == E7: return 64
        if chord == A7: return 69
        return 71

    try:
        bar_count = 1
        for chord in progression:
            melody_base = get_melody_base(chord)
            print(f"Bar {bar_count}: Parameter-Locking Guitar/Brass")
            for beat in range(4):
                
                # ===== ON BEAT: GUITAR CHORD =====
                fast_guitar_init(s1)
                
                vel_g = 85 if beat == 0 else 70
                # Play Guitar
                for note in chord:
                    s1.on(note, vel_g)
                time.sleep(strike_duration)
                
                # HARD CHOP (Silence the S-1 voices)
                for note in chord:
                    s1.off(note)
                time.sleep(rest_duration)

                # ===== OFF BEAT: BRASS VOCAL =====
                fast_brass_init(s1)
                
                melody_note = melody_base + brass_melody_offsets[beat]
                # Play Brass
                s1.on(melody_note, 100) # Brass sweeps need hard velocity
                time.sleep(strike_duration)
                
                # HARD CHOP
                s1.off(melody_note)
                time.sleep(rest_duration)

            bar_count += 1
    except KeyboardInterrupt:
        print("\nPerformance interrupted.")
    finally:
        s1.panic()
        print("Performance complete.")


if __name__ == "__main__":
    play_interleaved_blues()
