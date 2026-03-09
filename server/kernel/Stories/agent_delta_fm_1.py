#!/usr/bin/env python3
"""
Agent Delta — Patch 002: "The Carrier-Modulator Illusion"

Objective: To emulate complex multi-operator FM synthesis by carefully balancing
subtractively generated waveforms using LFO and Envelope routing.

Theory of Operation (Oscillator Balancing):
- We cannot do true FM on the core oscillators. However, we can create the *illusion* 
  of a 2-operator algorithm (Carrier + Modulator) by separating the S-1's sound sources.
- **The "Carrier"**: Our fundamental tone. We use the pure Sine wave of the self-oscillating 
  Filter (`CC71: 127`, `CC74: tuned to fundamental`). 
- **The "Modulator"**: The harmonic complexity. We use the Square wave (`CC21`).
- **The Illusion**: True FM creates dynamic overtone changes as the Modulator's volume 
  increases via its own envelope. We simulate this by applying the S-1's single Envelope 
  strictly to the VCA (Amplifier), but applying the LFO (`CC3`) slowly to the Filter Cutoff (`CC25`). 
  As the LFO moves the fundamental Sine wave out of phase with the static Square wave, 
  and the Envelope shapes the total volume, it mimics the evolving metallic wash of classic digital FM.

Taxonomic Application:
[Origin: Flow] + [Behavior: Evolving] + [Emotion: Euphoria] + [Role: Pad] + [Stress: Safe-Mode]
"""

import rtmidi
import time
import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class CarrierModulatorCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:ModulationRate": CC.LFO_RATE,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME
        }

    def init_synth_primitive(self, midi: Midi):
        print("\n[Agent Delta] Constructing FM Carrier/Modulator Illusion...")
    
        # 1. The "Modulator" (Harmonic Source)
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 60) # Reduced volume so it doesn't overpower the sine
        
        # 2. The "Carrier" (Fundamental Sine)
        midi.cc(CC.FILTER_RES, 127)   # Self-oscillation for pure sine
        midi.cc(CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 40, 90)) # Base tuning
        
        # 3. The Envelope (Controls overall Operator Output)
        midi.cc(CC.AMP_ATTACK, 80)    # Slow build like a DX7 sweep
        midi.cc(CC.AMP_DECAY, 127)
        midi.cc(CC.AMP_SUSTAIN, 127)
        midi.cc(CC.AMP_RELEASE, 90)   # Long release
        
        # 4. The Algorithm (Dynamic Movement)
        midi.cc(CC.LFO_RATE, self.get_val("afo:ModulationRate", 10, 80)) # Swept rate
        midi.cc(CC.FILTER_LFO, 50)   # Sweeps the Carrier Sine against the Modulator Square
        # midi.cc(CC.LFO_DEPTH, 0)      # Keep off pitch
        
        midi.cc(CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 20, 110))
        midi.cc(CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
        time.sleep(0.1)

    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Delta] Triggering sustained chord to demonstrate phase shifts for {duration}s.")
        chord = [48, 55, 64] # C, G, E
        
        try:
            for n in chord:
                midi.on(n, 90)
                
            time.sleep(duration) # Hold to let the LFO shift the Carrier against the Modulator
            
        except KeyboardInterrupt:
            print("\n[Agent Delta] Transport halted.")
        finally:
            for n in chord:
                midi.off(n)
            
            time.sleep(1.0) # Let the tail resolve
            midi.panic()
            
        print("\n[Agent Delta] Demonstration concluded.")
        
if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = CarrierModulatorCartridge()
    cartridge.apply_ontology({
        "afo:SpectralCentroid": 0.4, 
        "afo:ModulationRate": 0.3, # Slow sweep
        "afo:RoomSize": 0.8
    })
    cartridge.execute(duration=6.0, device_id=hw_hint)
