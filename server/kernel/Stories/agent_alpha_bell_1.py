#!/usr/bin/env python3
"""
Agent Alpha — Patch 001: The Inharmonic Bell (DSP Pseudo-FM Translation)

This script translates Miller Puckette's theoretical DSP concepts of phase modulation 
into the structurally constrained architecture of the Roland S-1.

Theory of Operation:
True FM requires multiple operators with precise integer (harmonic) or fractional 
(inharmonic) ratios. The S-1 is a subtractive synth. To generate the inharmonic 
sidebands required for a convincing bell/chime (a 'Strike' physics tag), we 
must use the LFO as a Modulator and the core oscillators as the Carrier.

Mathematical Blueprint:
- Carrier (C): Square wave (provides odd harmonics, hollow tone).
- Modulator (M): LFO routed to Pitch at absolute maximum rate (CC3 = 127).
  *Note: Waiting on Agent Epsilon to measure exact Hz of CC127, but pushing 
   it to max creates the widest delta between C and M.*
- Index Modulation (I): LFO Depth (CC17). We use a filter envelope with 0 attack, 
  0 sustain, and short decay routed to Pitch (via CC25 LFO to Filter, or manually 
  sweeping LFO Depth via Python) to simulate the 'Strike' transient. 
  Because CC sweeps via Python are constrained by baud rate, we will trigger 
  the bell, let the hardware envelope shape the filter, and keep the LFO depth 
  static to prove the sideband generation.
- Formant: Filter Cutoff tuned high, Resonance emphasized (but not self-oscillating) 
  to act as a fixed resonating body.

Target Taxonomy:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Role: FX/Percussive] + [Stress: Safe-Mode]
"""

import time
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class AgentAlphaBell1Cartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
             "afo:Loudness": CC.VOLUME,          
             "afo:SpectralCentroid": CC.FILTER_CUTOFF, 
             "afo:ModulationRate": CC.LFO_RATE,  
             "afo:RoomSize": CC.REVERB_LEVEL    
        }

    def init_synth_primitive(self, midi: Midi):
        print("\n[Agent Alpha] Assembling Inharmonic Bell blueprint...")
        
        # Carrier Definition
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 100)      # Square wave core (hollow)
        midi.cc(CC.SUB_LEVEL, 0)       # Sub disabled, muddying the sidebands
        midi.cc(CC.NOISE_LEVEL, 12)    # Clapper impact noise

        # Transient Envelope (Strike Mathematics)
        midi.cc(CC.AMP_ATTACK, 0)      # 0ms - mathematical absolute strike
        midi.cc(CC.AMP_DECAY, 55)      # Exponential decay (approx 800ms)
        midi.cc(CC.AMP_SUSTAIN, 0)     # No sustain
        midi.cc(CC.AMP_RELEASE, 65)    # Ring out after note off

        # Formant (Fixed Filter)
        midi.cc(CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid"))
        midi.cc(CC.FILTER_RES, 45)     # Ringing body, but NOT self-oscillating

        # Modulator (Pseudo-FM)
        midi.cc(CC.LFO_RATE, self.get_val("afo:ModulationRate"))      
        midi.cc(CC.PITCH, 60)      # Index Modulation depth applied to Pitch.
        midi.cc(CC.FILTER_LFO, 0)     # Keep FM strictly on pitch

        # Spatial
        midi.cc(CC.REVERB_LEVEL, self.get_val("afo:RoomSize"))
        midi.cc(CC.DELAY_LEVEL, 20)
        midi.cc(CC.VOLUME, self.get_val("afo:Loudness"))
        
        time.sleep(0.1) # Buffer safety

    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print("\n[Agent Alpha] Demonstrating sidebands across octaves.")
        
        start_time = time.time()
        test_notes = [48, 60, 72, 84] # C3, C4, C5, C6
        
        for n in test_notes:
            if time.time() - start_time >= duration:
                break
                
            print(f"   [Execute] Strike Note {n} | Vel 100")
            midi.on(n, 100)
            time.sleep(0.05) # Tiny gate, envelope handles the decay
            midi.off(n)
            
            sleep_time = min(2.0, duration - (time.time() - start_time))
            if sleep_time > 0:
                time.sleep(sleep_time)

        midi.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = AgentAlphaBell1Cartridge()
    cartridge.execute(duration=10.0, device_id=hw_hint)
