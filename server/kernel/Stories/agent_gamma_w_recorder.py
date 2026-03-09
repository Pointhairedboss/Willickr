"""
Gordon Reid "Synth Secrets" Chapter 51: Synthesizing Simple Flutes (Recorders)
Agent Gamma-W (Winds/Strings/Brass) Translation

Acoustic Principle:
A recorder is an open pipe, retaining both odd and even harmonics, but with a weak second harmonic 
(similar to a ~40% pulse wave or softened triangle). The attack of a recorder is characterized by 
brightness (high frequencies) peaking *before* loudness peaks, letting a small burst of high-frequency 
noise/harmonics through to imitate the initial air jet.

S-1 Hardware Translation:
1. Core Sound: To approximate the 40% pulse/triangle, we mix Sawtooth (CC 20) and Square (CC 21) 
   at moderate levels, rounding the wave.
2. The "Filter Burst": We use a heavily engaged Filter Envelope (CC 26) with a very fast Attack 
   and Decay. The VCA envelope has a slightly slower attack. This ensures the filter snaps open 
   and closed at the start, creating the characteristic "wood thunk" / "spit".
3. Slight LFO (CC 12: Random/S&H) applied to the filter (CC 28) to simulate blowing instabilities.

Taxonomic Application:
[Origin: Edge-Blown] + [Behavior: Plucked/Sustained] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]
"""

import time
from server.kernel.s1_midi import Midi, CC

def run_recorder_patch():
    print("Agent Gamma-W: Initializing Recorder (Ch 51) Patch...")
    s1 = Midi()
    
    # Base Oscillator: Mixture to approximate soft pulse
    s1.cc(CC.SAW_LEVEL, 70)
    s1.cc(CC.OSC_SQUARE, 100)
    s1.cc(CC.SUB_LEVEL, 0)
    s1.cc(CC.NOISE_LEVEL, 15) 
    
    # Filter: Low cutoff, driven hard by envelope for the initial "spit"
    s1.cc(CC.FILTER_CUTOFF, 45) 
    s1.cc(CC.FILTER_RES, 20)    
    s1.cc(CC.FILTER_ENV, 55)    # Strong envelope modulation
    
    # Filter LFO for breathing instability
    s1.cc(CC.FILTER_LFO, 10)
    s1.cc(CC.LFO_MODE, 0)
    s1.cc(CC.LFO_SHAPE, 5)      # Random S&H for instability
    s1.cc(CC.LFO_RATE, 60)      
    
    # Envelope: The critical difference.
    # VCA attack should be slightly slower than the filter snap (handled by CC.ENV... limits on S-1 
    # mean we share envelopes, so we rely on the VCF closing fast while the VCA holds)
    s1.cc(CC.AMP_ATTACK, 10)
    s1.cc(CC.AMP_DECAY, 30)     # Filter closes quickly to 0 + Cutoff value
    s1.cc(CC.AMP_SUSTAIN, 70)   # Body of the sound
    s1.cc(CC.AMP_RELEASE, 25)   # Wooden "thunk" at the end
    
    # Pitch vibrato (keep it very low, recorders don't have natural strong vibrato)
    s1.cc(CC.PITCH, 0)
    
    # Effects
    s1.cc(CC.CHORUS_LEVEL, 0)
    s1.cc(CC.REVERB_LEVEL, 60)
    s1.cc(CC.DELAY_LEVEL, 0)
    
    print("Patch initialized. Playing staccato/legato test...")
    
    notes = [72, 74, 76, 77, 79] 
    
    for note in notes:
        s1.on(note, velocity=90)
        time.sleep(0.5)
        s1.off(note)
        time.sleep(0.2)

    print("Recorder sequence complete.")

if __name__ == "__main__":
    run_recorder_patch()
