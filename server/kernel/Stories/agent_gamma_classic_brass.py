#!/usr/bin/env python3
"""
Agent Gamma — Patch 004: "The Classic Synthetic Brass"

Objective: To synthesize a classic acoustic brass physical model 
(e.g., Prophet-5 style analog brass emulation) adhering strictly to Gordon Reid's 
structural acoustic principles and the S-1 constraints.

Theory of Operation:
- **The Oscillators**: A rich SAW basis is absolutely required for the even + odd harmonics.
- **The "Blat"**: The defining characteristic of synthesized brass. It is achieved 
  by setting the filter cutoff very low, but driving the Filter Envelope Depth 
  high (`CC26`), alongside a moderately slow (but not sluggish) filter attack and a quick decay. 
  This forces the upper harmonics to sweep open and close rapidly at the onset of the note.
- **The Amplifier**: Mirrors the filter envelope but with a slightly softer 
  attack so the fundamental doesn't "click" before the harmonics arrive.

Taxonomic Application:
[Origin: Breath] + [Behavior: Decaying] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Brass-Subtractive]
"""

import rtmidi
import time

CH = 2

class CC:
    PORTAMENTO   = 5;  VOLUME       = 7;  LFO_DEPTH    = 17
    SAW_LEVEL    = 20; SQ_LEVEL     = 21; SUB_LEVEL    = 19; NOISE_LEVEL  = 23
    FILTER_RES   = 71; AMP_RELEASE  = 72; AMP_ATTACK   = 73
    FILTER_CUTOFF= 74; AMP_DECAY    = 75; AMP_SUSTAIN  = 70
    PITCH_ENV    = 16; ENV_TO_FILT  = 26
    REVERB_LEVEL = 91; DELAY_LEVEL  = 92

class Midi:
    def __init__(self, hint=None):
        self._o = rtmidi.MidiOut()
        ports = self._o.get_ports()
        opened = False
        if hint:
            for i, p in enumerate(ports):
                if hint.lower() in p.lower():
                    self._o.open_port(i); print(f"Opened: {p}"); opened = True; break
        if not opened:
            for i, p in enumerate(ports):
                if any(k in p.upper() for k in ('S-1', 'S1', 'ROLAND', 'AIRA')):
                    self._o.open_port(i); print(f"Auto: {p}"); opened = True; break
        if not opened:
            self._o.open_virtual_port("S1-Gamma"); print("Virtual port")

    def cc(self, c, v): self._o.send_message([0xB0 | CH, c, max(0, min(127, int(v)))])
    def on(self, n, v=75): self._o.send_message([0x90 | CH, n & 127, max(1, min(127, v))])
    def off(self, n): self._o.send_message([0x80 | CH, n & 127, 0])


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

        print("\n[Agent Gamma] Constructing Classic Analog Brass...")
    
        # Oscillators: Rich Sawtooth basis
        midi.cc(CC.SAW_LEVEL, 127)  # Maximum harmonic content
        midi.cc(CC.SQ_LEVEL, 0)
        midi.cc(CC.SUB_LEVEL, 45)   # Thicken the fundamental just slightly
        midi.cc(CC.NOISE_LEVEL, 0)

        # Amplifier Envelope
        midi.cc(CC.AMP_ATTACK, 28)  # Slight ramp to avoid click
        midi.cc(CC.AMP_DECAY, 82)   # Moderate decay to the sustain level
        midi.cc(CC.AMP_SUSTAIN, 90) # High sustain
        midi.cc(CC.AMP_RELEASE, 35) # Natural room decay, fast enough to avoid clicking due to voice stealing

        # The Filter "Blat" Mechanics
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 0, 48))  # Very closed initially
        midi.cc(CC.FILTER_RES, 20)     # Slight bump for the sweep overtone
        midi.cc(CC.ENV_TO_FILT, 115)   # Extreme ENV depth pushing the cutoff open
    
        # The Shared Envelope: The attack of 28 allows the filter to sweep open 
        # over ~30-50ms, creating the aggressive brass blat before settling to the sustain.

        # Spatial/FX (Avoid long release tails based on Voice Stealing constraints)
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100))  # Standard short plate verb emulation
        midi.cc(CC.DELAY_LEVEL, 0)
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
    
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Agent Gamma] Triggering F Minor 9 chord to audition the filter sweep.")
    
        # Keep it to 4 voices to prevent voice stealing artifacts
        chord = [53, 60, 63, 68] # F, C, Eb, Ab
    
        # Hit the chord hard to trigger maximum envelope/filter depth
        for n in chord:
            midi.on(n, 105)
        
        time.sleep(1.8) # Hold the sustain phase
    
        for n in chord:
            midi.off(n)
        
        time.sleep(1.0)
        print("[Agent Gamma] Demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
