#!/usr/bin/env python3
"""
AGENT GAMMA-W (WINDS/STRINGS) — PATCH 003: "The Bowed Violin"
Source: SyntheoryGordonReid - Chapter 46-49 (Synthesizing Bowed Strings)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Bow] + [Behavior: Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Bowed-String]

Theory Implemented:
  1. The Rosin Friction: The slip-stick mechanism of a bowed string generates a near-perfect Sawtooth wave 
     as the string is dragged and then snaps back. Consequently, we rely 100% on the ACB Sawtooth core, 
     muting Square and Sub.
  2. Articulation: A bow builds energy across the string. Standard instant synth attacks destroy this illusion. 
     We require a sloped 80-100ms AMP_ATTACK to simulate the bow catching the string.
  3. Dynamic Vibrato: Real string players invariably apply vibrato *after* the note has stabilized, never instantly. 
     Without a built-in LFO Delay parameter on the S-1, we script the delayed vibrato swell via python MIDI sequencing.

Usage:
    python gamma_w_violin_1.py
"""

import sys
import time
import os
import threading

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
from cartridge_base import BaseCartridge


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

            print("Agent Gamma-W: Initializing 'The Bowed Violin' patch...")
    
            # 1. Harmonic Core
            midi.cc(CC.SAW_LEVEL, 127)     # Pure Sawtooth (slip-stick emulation)
            midi.cc(CC.OSC_SQUARE, 0)
            midi.cc(CC.SUB_LEVEL, 0)
            midi.cc(CC.NOISE_LEVEL, 5)     # Very subtle bow scrape
    
            # 2. Resonant Body Filtering
            midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 35, 95))  # Mellow out the harsh raw saw to simulate wood dampening
            midi.cc(CC.FILTER_RES, 20)     # Slight resonant bump for the violin "formant"
    
            # 3. Bow Articulation
            midi.cc(CC.AMP_ATTACK, 45)     # Moderate swell (~100ms)
            midi.cc(CC.AMP_DECAY, 20)      
            midi.cc(CC.AMP_SUSTAIN, 95)    # Continuous holding pressure
            midi.cc(CC.AMP_RELEASE, 40)    # Soft string ring out
    
            # 4. LFO Baseline (Vibrato)
            midi.cc(CC.LFO_RATE, 65)       # Standard human 5-6Hz vibrato
            midi.cc(CC.LFO_MODE, 0)
            midi.cc(CC.PITCH, 0)           # Start with ZERO vibrato! We fade this in dynamically via Python.
    
            # 5. Room
            midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))
            midi.cc(CC.DELAY_LEVEL, 0)
    
            time.sleep(0.5)

        def delayed_vibrato(midi: Midi, target_depth=25, delay=0.4, swell_time=0.3):
            """Python-driven envelope to fake an LFO delay parameter."""
            time.sleep(delay)
            steps = 10
            step_time = swell_time / steps
            for i in range(1, steps + 1):
                midi.cc(CC.PITCH, int((i / steps) * target_depth))
                time.sleep(step_time)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-W: Playing string adagio with programmatic delayed vibrato.")
    
        phrase = [
            (64, 2.5), # E4
            (65, 1.0), # F4
            (62, 1.5), # D4
            (60, 3.0), # C4
        ]
    
        try:
            for note, dur in phrase:
                midi.cc(CC.PITCH, 0) # Reset vibrato
                midi.on(note, 80)
            
                # Start dynamic vibrato thread in parallel
                t = threading.Thread(target=delayed_vibrato, args=(midi, 25, 0.5, 0.4))
                t.start()
            
                time.sleep(dur)
                midi.off(note)
                t.join() # Ensure vibrato script completes before next note
                time.sleep(0.2) # Bow lift
            
        except KeyboardInterrupt:
            print("\nAgent Gamma-W: Halting phrase.")
            midi.panic()


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
