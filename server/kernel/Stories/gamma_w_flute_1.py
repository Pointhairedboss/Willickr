#!/usr/bin/env python3
"""
AGENT GAMMA-W (WINDS/STRINGS) — PATCH 001: "The Pure Sine Flute"
Source: SyntheoryGordonReid - Chapters 50-52 (Synthesizing Flutes)

Taxonomy (Pre-Allocated by Archivist):
[Origin: Breath] + [Behavior: Evolving] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]

Theory Implemented:
  1. The Tone: A flute is fundamentally an open pipe, producing both even and odd harmonics, but leaning almost
     entirely toward a pure Sine wave once the fundamental speaks. Since the S-1 lacks a dedicated Sine oscillator, 
     we rely strictly on driving the filter to self-oscillation (CC71: 127) to generate a pristine mathematical sine,
     muting the noisy SAW/SQUARE cores entirely.
  2. The Chiff: The attack transient of a real flute involves breath hitting the embouchure hole, creating white noise 
     before the resonant body oscillates. We inject a burst of white noise (CC23) and use the filter envelope to 
     snap down hard, simulating that initial breath transient before the pure tone takes over.
  3. Physical Expression: A flute player shapes the note dynamically with their breath (Delayed Vibrato/Tremolo).
     We simulate this by mapping the LFO strictly to the VCA/Filter (Tremolo) utilizing a fading envelope rather than a static hum.

Usage:
    python gamma_w_flute_1.py
"""

import sys
import time
import os

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

        print("Agent Gamma-W: Initializing 'The Pure Sine Flute' patch...")
    
        # 1. The Harmonic Elimination (Filter as Oscillator)
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.OSC_SQUARE, 0)
        midi.cc(CC.SUB_LEVEL, 0)
    
        # Push the filter to heavy oscillation and map it 100% to key-tracking in the S-1 menu (Assumed active)
        midi.cc(CC.FILTER_RES, 127)    # Total self oscillation = Pure Sine Wave
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 70, 127)) # Open the filter wide because it is generating our pitch
    
        # 2. The Chiff (Breath Transient)
        midi.cc(CC.NOISE_LEVEL, 115)   # A massive burst of noise is needed for a fraction of a second
        midi.cc(CC.FILTER_ENV, 105)    # Negative modulation: The envelope forces the filter to choke the noise quickly
    
        # 3. Flute Envelope (Slight hesitation as air pressure builds, breath hold, soft release)
        midi.cc(CC.AMP_ATTACK, 40)     # Slow build as breath fills the pipe
        midi.cc(CC.AMP_DECAY, 30)      # Initial spike of air settles...
        midi.cc(CC.AMP_SUSTAIN, 75)    # ...into a sustained breath pressure
        midi.cc(CC.AMP_RELEASE, 55)    # Gentle fade out when breath stops
    
        # 4. Flutist Expression (Delayed Vibrato)
        midi.cc(CC.LFO_RATE, 70)       # Fast, human vibrato rate
        midi.cc(CC.LFO_MODE, 0)
        midi.cc(CC.PITCH, 35)          # Moderate pitch wobble
        midi.cc(CC.FILTER_LFO, 25)     # Very slight tremolo (volume wobble) as breath waivers
    
        # 5. Spatial Realism (Concert Hall)
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))   # Flutes require heavy room reflections to sound credible
        midi.cc(CC.DELAY_LEVEL, 0)
    
        time.sleep(0.5)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")

        print("Agent Gamma-W: Playing flute trill and sustain. Note the slow attack and sine purity.")
    
        # A classic pastoral flute phrase
        phrase = [
            (72, 0.4), # C5
            (74, 0.2), # D5 quick passing note
            (76, 1.8), # E5 sustain 
            (74, 0.4), # D5
            (72, 0.2), # C5
            (71, 0.2), # B4
            (72, 2.5), # C5 long hold
        ]
    
        try:
            for note, dur in phrase:
                midi.on(note, 65)
                time.sleep(dur)
                midi.off(note)
                time.sleep(0.05) # Breath gap
            
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
