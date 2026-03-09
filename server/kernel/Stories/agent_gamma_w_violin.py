"""
Gordon Reid "Synth Secrets" Chapter 46: The Violin Family
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
A violin string is excited by a bow. Static friction drags the string until dynamic friction causes 
it to snap back. The forces applied by the string upon the bridge are perfectly represented by a true 
Sawtooth wave. A violin's acoustic body has resonances that shape this raw sawtooth.

S-1 Hardware Translation:
1. Core sound is pure Sawtooth (CC 20) to emulate the slip-stick friction model of the bridge force.
2. The bow requires drag: Amp Attack (CC 73) must be slow, imitating the build-up of physical friction.
3. Delayed Vibrato: A real violinist introduces vibrato *after* the note has settled. Since we can't 
   easily construct a multi-stage LFO delay on the S-1 via CCs alone, we manually inject Pitch LFO 
   Modulation (CC 17) via Python during the sequence runtime.
4. Filter (CC 74) acts as the violin body formant, cutting off higher, harsher overtones of the saw.

Taxonomic Application:
[Origin: Bow/Friction] + [Behavior: Evolving] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]
"""

import time
from server.kernel.s1_midi import Midi, CC

def run_violin_patch():
    print("Agent Gamma-W: Initializing Violin (Ch 46) Patch...")
    s1 = Midi()
    
    # Base Oscillator: Pure Sawtooth for slip-stick physics
    s1.cc(CC.SAW_LEVEL, 127)
    s1.cc(CC.OSC_SQUARE, 0)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 0)
    
    # Filter: Violin body emulation
    s1.cc(CC.FILTER_CUTOFF, 88)
    s1.cc(CC.FILTER_RES, 15)  # Slight peak for resin "bite"
    s1.cc(CC.FILTER_ENV, 0)
    s1.cc(CC.FILTER_LFO, 0)
    
    # Envelope: Bow drag
    s1.cc(CC.AMP_ATTACK, 35)   # Takes a moment for the bow to catch
    s1.cc(CC.AMP_DECAY, 20)
    s1.cc(CC.AMP_SUSTAIN, 100)
    s1.cc(CC.AMP_RELEASE, 40)  # Room decay, relatively short
    
    # LFO Pitch Modulation: Prepared for manual sequenced injection
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_SHAPE, 1)     # Triangle/Sine wave for player vibrato
    s1.cc(CC.LFO_RATE, 65)     # Player vibrato speed (~5-6Hz)
    s1.cc(CC.PITCH, 0)         # Start at 0, injected later
    
    # Effects: Small chamber reverb
    s1.cc(CC.CHORUS_LEVEL, 0)
    s1.cc(CC.REVERB_LEVEL, 65)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("Patch initialized. Playing test solo sequence with manual delayed vibrato...")
    
    # Test Sequence: Classical Arpeggio/Lead line
    lead_notes = [60, 64, 67, 72, 71, 67, 62, 59]
    
    for i, note in enumerate(lead_notes):
        s1.on(note, velocity=85)
        
        # Reset Vibrato
        s1.cc(CC.PITCH, 0)
        
        # Bow dragging phase (Attack)
        time.sleep(0.3)
        
        # For longer sustaining notes, introduce vibrato
        if i % 2 == 0:
            for depth in range(1, 15, 2):
                s1.cc(CC.PITCH, depth)
                time.sleep(0.05)
            time.sleep(0.6) # Hold note with vibrato
        else:
            time.sleep(0.3) # Short note without vibrato
            
        # Release
        s1.off(note)
        s1.cc(CC.PITCH, 0)
        time.sleep(0.1)

    print("Violin sequence complete.")

if __name__ == "__main__":
    run_violin_patch()
