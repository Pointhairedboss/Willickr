#!/usr/bin/env python3
"""
Agent Gamma-P (Percussion) — Patch 002: "The Analog Snare"

Source: SyntheoryGordonReid (Chapters 33-34: Practical Snare Drum Synthesis)
Objective: To recreate a classic analog drum machine snare using S-1 constraints.

Theory of Operation:
A snare drum consists of two primary acoustic components:
1. **The Body (Drum Skin)**: A pitched, rapidly decaying sine wave.
2. **The Snares (Wires)**: A burst of broadband high-frequency noise.

S-1 Translation:
- **The Body**: We use the self-oscillating filter (`CC71: 127`) tuned around 200Hz (`CC74: 60`).
  We sweep the cutoff downwards rapidly using the Filter Envelope (`CC26: 90`) to simulate 
  the stick hitting the tight skin.
- **The Snares**: We introduce White Noise (`CC23: 110`). The shared VCA envelope 
  provides the sharp attack (`CC73: 0`) and rapid decay (`CC75: 45`) for the noise burst.

Taxonomy (Archivist Pre-Assigned):
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]
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

        print("\n[Gamma-P] Constructing Analog Snare...")
    
        # 1. The Body (Self-oscillating Filter)
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 0)
        midi.cc(CC.SUB_LEVEL, 0)
    
        # Noise for the snare wires
        midi.cc(CC.NOISE_LEVEL, 110)
    
        # Filter setup for the fundamental "ping"
        midi.cc(CC.FILTER_RES, 127)   # Self-oscillation
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 30, 90)) # Base tuning ~200Hz
    
        # 2. Envelopes
        # The VCA envelope defines the total length of the snare burst
        midi.cc(CC.AMP_ATTACK, 0)     # Instant strike
        midi.cc(CC.AMP_DECAY, 45)     # Very fast snappy decay
        midi.cc(CC.AMP_SUSTAIN, 0)    # No sustain
        midi.cc(CC.AMP_RELEASE, 20)   # Quick release
    
        # The "Stick Impact" Pitch Envelope (via Filter Env)
        midi.cc(CC.FILTER_ENV, 90)    # Sweeps the self-oscillating filter down rapidly
    
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Gamma-P] Triggering snare backbeat pattern.")
    
        # Standard 4/4 backbeat on 2 and 4 (using sleep timing)
        for _ in range(4):
            time.sleep(0.5) # Beat 1
        
            # Beat 2
            midi.on(60, 110)
            time.sleep(0.05)
            midi.off(60)
            time.sleep(0.45)
        
            time.sleep(0.5) # Beat 3
        
            # Beat 4
            midi.on(60, 120) # Accent
            time.sleep(0.05)
            midi.off(60)
            time.sleep(0.45)
        
        print("\n[Gamma-P] Snare demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
