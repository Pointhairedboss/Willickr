import sys
import os
import time

# Ensure imports resolve to master Stories folder
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi
import dr_who_theme as dw

def test_melody():
    print("--- Isolated Doctor Who Melody Test ---")
    s1 = Midi()
    
    print("Initializing Melody Patch...")
    dw.init_who_melody(s1)
    time.sleep(0.5)
    
    # The massive glissando needs portamento!
    s1.cc(5, 75)  # Add significant glide for the 2-octave swoop
    
    BPM = 110
    BEAT = 60.0 / BPM
    B2 = 47  # Low B
    A5 = 81; B5 = 83; C6 = 84; D6 = 86 # High octave
    
    print("Playing Note: Low B2 (The Start of the Glissando)")
    s1.on(B2, 100); time.sleep(BEAT * 1.5)
    
    print("Playing Note: High C6 (The Swoop Up!)")
    # We do NOT send an off() for B2 yet, we just trigger C6 so the portamento glides
    s1.on(C6, 100); 
    s1.off(B2) # Now off the B2
    time.sleep(BEAT * 1.5); 
    
    print("Playing Note: High B5 (The Rest)")
    s1.off(C6)
    s1.on(B5, 100); time.sleep(BEAT * 1.5); s1.off(B5)

    print("Playing Note: High D6 (The Ascend)")
    s1.on(D6, 100); time.sleep(BEAT * 1.5); 
    
    print("Playing Note: Low A3 (The Swoop Down!)")
    A3 = 57 # Two octaves down
    s1.on(A3, 100)
    s1.off(D6)
    time.sleep(BEAT * 1.5)
    s1.off(A3)

    print("--- Melody Test Complete ---")
    s1.panic()

if __name__ == "__main__":
    test_melody()
