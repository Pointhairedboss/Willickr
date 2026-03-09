"""
Agent: Beta (Ambient Sound Design)
Patch: Glacial Pad
Hardware Target: Roland S-1
Mandate: Crafting spatial, meditative, and evolving environments.

Acoustic Theory & Translation Strategy:
- Polyphony Constraint: The S-1 is 4-voice polyphonic. This script is fully generative
  and relies heavily on randomized time intervals (ranging from 1.5 to 4 seconds) to slowly
  stack sparse notes.
- Voice-Stealing / Clicks: To mitigate clicks when a 5th note steals a voice, `AMP_RELEASE`
  (CC 72) is kept mathematically short. The perception of an infinite pad is delegated
  entirely to the Reverb (CC 91) parameter pushed to maximum.
- Glacial Movement: Employs a sub-Hz LFO (CC 3 set very low) mapped to Filter Cutoff
  (CC 25) with high Resonance (CC 71) to create slowly evolving spectral shifts.
- Origin: Oscillator mix emphasizes the Sub and Saw for a thick foundation.

Taxonomic Application:
[Origin: Oscillator mix] + [Behavior: Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Pad]
"""

import time
import random
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class AgentBetaGlacialPadCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
             "afo:Loudness": CC.VOLUME,          
             "afo:SpectralCentroid": CC.FILTER_CUTOFF, 
             "afo:ModulationRate": CC.LFO_RATE,  
             "afo:RoomSize": CC.REVERB_LEVEL    
        }

    def init_synth_primitive(self, s1: Midi):
        print("Initializing Agent Beta: Glacial Pad S-1 Parameters...")

        # --- 1. Master Mix & Oscillators ---
        s1.cc(CC.VOLUME, self.get_val("afo:Loudness"))
        s1.cc(CC.SUB_LEVEL, 110)      # Strong foundational bass
        s1.cc(CC.SAW_LEVEL, 90)       # Warm harmonic content
        s1.cc(CC.OSC_SQUARE, 20)      # Slight pulse edge
        s1.cc(CC.NOISE_LEVEL, 10)     # Whispering background noise

        # --- 2. Envelopes (VCA / VCF Shared) ---
        s1.cc(CC.AMP_ATTACK, 100)     # Very slow, swelling attack
        s1.cc(CC.AMP_DECAY, 90)
        s1.cc(CC.AMP_SUSTAIN, 100)
        s1.cc(CC.AMP_RELEASE, 60)     # Kept relatively short to prevent voice-stealing clicks

        # --- 3. Filter Dynamics (Glacial Movement) ---
        s1.cc(CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid"))   # Dark fundamental tone
        s1.cc(CC.FILTER_RES, 80)      # High resonance to emphasize the LFO sweep
        s1.cc(CC.FILTER_ENV, 0)       # No envelope modulation on filter
        s1.cc(CC.FILTER_LFO, 60)      # LFO drives the filter movement

        # --- 4. LFO (Sub-Hz Speeds) ---
        s1.cc(CC.LFO_MODE, 0)         # Normal mode (not Audio-Rate)
        s1.cc(CC.LFO_SHAPE, 0)        # Sine wave for smooth sweeping
        s1.cc(CC.LFO_RATE, self.get_val("afo:ModulationRate"))         # Extremely slow, sub-Hz rate (Glacial)

        # --- 5. Spatial Effects (The Ambient Mandate) ---
        s1.cc(CC.CHORUS_LEVEL, 80)    # Widen the stereo field
        s1.cc(CC.REVERB_LEVEL, self.get_val("afo:RoomSize"))   # Infinite space (carries the release tails)
        s1.cc(CC.DELAY_LEVEL, 60)
        
        print("Patch Parameter Initialization Complete.")


    def execute(self, duration: float, device_id: int):
        # Initialize S-1 MIDI connection
        s1 = Midi(hint=str(device_id) if device_id else None)
        
        # Configure the preset
        self.init_synth_primitive(s1)

        print("Beginning Generative Ambient Sequence...")

        # Pentatonic scale for meditative atmosphere (C minor pentatonic: C, Eb, F, G, Bb)
        root = 48 # C3
        scale = [0, 3, 5, 7, 10]
        octaves = [0, 12] # C3, C4

        active_notes = []
        start_time = time.time()
        
        try:
            while time.time() - start_time < duration:
                # 1. Note Selection
                note_idx = random.choice(scale)
                octave = random.choice(octaves)
                midi_note = root + note_idx + octave
                
                # 2. Trigger
                velocity = random.randint(40, 70) # Soft, swelling strikes
                s1.on(midi_note, velocity)
                active_notes.append(midi_note)
                print(f"Triggering Note: {midi_note} (Velocity {velocity})")

                # 3. Handle Polyphony (Max 4 voices)
                if len(active_notes) > 3:
                    # Turn off the oldest note sequentially to allow the new note to ring out
                    # without an immediate hard clip. Reverb will mask the release cut.
                    oldest_note = active_notes.pop(0)
                    s1.off(oldest_note)
                    print(f"Releasing Note: {oldest_note}")

                # 4. Generative Timing
                # Sleep for a long, variable duration to create an evolving soundscape
                sleep_time = random.uniform(2.5, 6.0)
                actual_sleep = min(sleep_time, duration - (time.time() - start_time))
                if actual_sleep > 0:
                    time.sleep(actual_sleep)

        except KeyboardInterrupt:
            print("\nSequence Terminated.")
            
        finally:
            for note in active_notes:
                s1.off(note)
            s1.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = AgentBetaGlacialPadCartridge()
    cartridge.execute(duration=10.0, device_id=hw_hint)
