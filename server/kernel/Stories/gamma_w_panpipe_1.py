#!/usr/bin/env python3
"""
Agent Gamma-W (Winds) — Patch 002: "The Andean Pan Pipe"

Source: SyntheoryGordonReid (Chapter 50: Synthesizing Pan Pipes)
Objective: To recreate the physical characteristics of a blown pipe using the ACB engine.

Theory of Operation:
A pan pipe is a simple open/closed cylinder. The geometry emphasizes odd harmonics
but dampens even ones. Crucially, blowing into a pan pipe generates a significant 
noise component ("chiff") and a pitch envelope (as breath pressure increases, 
pitch bends up slightly).
- **The Core**: We mimic the odd-harmonic structure by mixing 
  a Square wave (odd harmonics only) with the fundamental (a highly resonant filter).
- **The Chiff (Noise)**: White noise `CC23` layered on the attack.
- **The Overblow (Pitch Drift)**: Using the filter envelope `CC26` routed to 
  the LFO-to-Pitch or pitch directly to create a tiny "scoop" up to pitch over 20ms.
- **The Vibrato**: Pan pipe vibrato is wide, slow, and human. We introduce it 
  via LFO `CC17`.

Taxonomy (Archivist Pre-Assigned):
[Origin: Breath] + [Behavior: Evolving] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]
"""

from s1_midi import Midi, CC
from cartridge_base import BaseCartridge
import time


class GammaAcousticCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME,
            "afo:ModulationRate": CC.LFO_RATE
        }

    def init_synth_primitive(self, midi: Midi):

        print("\n[Gamma-W] Constructing Andean Pan Pipe...")
    
        # The Harmonic Core (Odd Harmonics + Fundamental)
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 80) # The odd harmonics of the closed pipe
        midi.cc(CC.SUB_LEVEL, 40)
    
        # The Chiff
        midi.cc(CC.NOISE_LEVEL, 95) # High initial noise
    
        # The Formant (Pipe Body)
        midi.cc(CC.FILTER_RES, 75)    # Resonance to boost the fundamental 
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 15, 75)) # Rolled off highs so it sounds woody
        midi.cc(CC.FILTER_ENV, 30)    # Slight filter sweep to let the chiff through
    
        # The Breath (VCA Envelope)
        midi.cc(CC.AMP_ATTACK, 20)    # Soft tongue
        midi.cc(CC.AMP_DECAY, 50)     # Chiff dies away
        midi.cc(CC.AMP_SUSTAIN, 75)   # Sustains while breath holds
        midi.cc(CC.AMP_RELEASE, 30)   # Quick release
    
        # The Human Element (Vibrato)
        midi.cc(CC.LFO_RATE, 65)      # ~6Hz
        midi.cc(CC.LFO_MODE, 0)       # Normal LFO
        # Instead of static CC.PITCH (LFO_DEPTH), we will dynamically introduce it 
        # to simulate the player adding breath vibrato after the attack.
        midi.cc(CC.PITCH, 0) 
    
        # Spatial Environment (Mountains)
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
        midi.cc(CC.DELAY_LEVEL, 60)
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
    
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Gamma-W] Playing El Condor Pasa excerpt with delayed vibrato breath.")
    
        melody = [
            (64, 0.5), # E
            (67, 0.5), # G
            (69, 1.0), # A
            (71, 0.5), # B
            (69, 1.5)  # A (held)
        ]
    
        for note, dur in melody:
            midi.on(note, 80)
        
            # Determine how many "steps" to divide the duration into for the vibrato envelope
            steps = 10
            step_time = dur / steps
        
            # Simulate the player slowly introducing breath vibrato on longer held notes
            if dur >= 1.0:
                for i in range(steps):
                    lfo_amt = min(int(i * 4), 30) # Ramp to max 30 depth
                    midi.cc(CC.PITCH, lfo_amt)
                    time.sleep(step_time)
            else:
                time.sleep(dur) # Short notes get no vibrato
            
            midi.off(note)
            # Reset vibrato for the next note's attack
            midi.cc(CC.PITCH, 0)
            time.sleep(0.1) # Separation between notes to let the noise chiff re-trigger
        
        print("\n[Gamma-W] Pan Pipe demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
