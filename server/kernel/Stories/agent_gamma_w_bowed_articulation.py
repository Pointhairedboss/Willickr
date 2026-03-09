"""
Gordon Reid "Synth Secrets" Chapter 49: Articulation & Bowed-string Synthesis
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
Taking the Ondes Martenot approach: Instead of using VCA (Volume) to articulate individual notes, 
we use the VCF (Filter Cutoff). The filter is completely closed between notes (silence), and 
notes are articulated by physically sweeping the filter open. This simultaneously increases volume 
and high-frequency harmonic content, perfectly mimicking the behavior of a physical bowed string.

S-1 Hardware Translation:
1. Amp Envelope is again bypassed (set to instant attack/sustain).
2. The VCF Cutoff (CC 74) replaces the VCA as our main volume/articulation control. 
3. When CC 74 is 0, the synth is silent. As the sequencer sweeps CC 74 up, the tone gets louder 
   and brighter.
4. Python script sends CC 74 sweeps to articulate a connected legato phrase, simulating a 
   single continuous bow stroke across multiple notes.

Taxonomic Application:
[Origin: Bow/Friction] + [Behavior: Rhythmic/Generative] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Ondes-Martenot]
"""

import time
from server.kernel.s1_midi import Midi, CC

def run_bowed_articulation_patch():
    print("Agent Gamma-W: Initializing Bowed Articulation (Ch 49) Filter-Swept Patch...")
    s1 = Midi()
    
    # Base Oscillator: Sawtooth + Sub for extra resonant richness
    s1.cc(CC.SAW_LEVEL, 127)
    s1.cc(CC.SUB_LEVEL, 60)
    s1.cc(CC.OSC_SQUARE, 0)
    
    # Filter setup: No envelope tracking. Cutoff starts at 0 (Silence)
    s1.cc(CC.FILTER_ENV, 0)
    s1.cc(CC.FILTER_LFO, 0)
    s1.cc(CC.FILTER_RES, 35)    
    s1.cc(CC.FILTER_CUTOFF, 0) 
    
    # Envelope: Hard Gate 
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)
    s1.cc(CC.AMP_RELEASE, 30) 
    
    # LFO Pitch settings
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_SHAPE, 1)      
    s1.cc(CC.LFO_RATE, 68)      
    s1.cc(CC.PITCH, 0)
    
    # Effects
    s1.cc(CC.CHORUS_LEVEL, 0)
    s1.cc(CC.REVERB_LEVEL, 85)
    
    print("Patch initialized. Articulating via Filter Cutoff (CC 74)...")
    
    # Legato sequence
    notes = [60, 62, 64]
    
    # Start the sound engine (VCA is open, but silent due to filter)
    for note in notes:
        s1.on(note, velocity=100)
    
    # Because we want a legato phrase, we'll sweep the filter for each note 
    # while the underlying notes change.
    
    for note in notes:
        # Stop previous notes
        s1.panic() 
        s1.on(note, velocity=100)
        
        # Swell Filter Open
        for i in range(0, 100, 4):
            s1.cc(CC.FILTER_CUTOFF, i)
            s1.cc(CC.PITCH, int((i/100.0) * 12)) # Vibrato scales with brightness
            time.sleep(0.03)
            
        time.sleep(0.4) # Hold
        
        # Swell Filter Closed
        for i in range(100, 0, -5):
            s1.cc(CC.FILTER_CUTOFF, i)
            s1.cc(CC.PITCH, int((i/100.0) * 12))
            time.sleep(0.02)
            
    s1.off(notes[-1])
    s1.panic()
    
    # Restore defaults
    s1.cc(CC.FILTER_CUTOFF, 127)
    s1.cc(CC.PITCH, 0)
    print("Filter Articulated Bowed Strings sequence complete.")

if __name__ == "__main__":
    run_bowed_articulation_patch()
