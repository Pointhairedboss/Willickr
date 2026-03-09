#!/usr/bin/env python3
"""
Agent Gamma — Patch 003: "The 808-Style Analog Kick"

Objective: To synthesize a pure analog kick drum relying on pitch envelope theory.

Theory of Operation (Subtractive Percussion Synthesis):
A classic kick drum (like the TR-808) is not a chaotic noise burst; it is a 
rapidly descending sine wave.
- **The Oscillator**: The S-1 filter acts as a pure sine wave when self-oscillating. 
  By pushing resonance to 127 and removing the core oscillators, the filter becomes the drum.
- **The Amplifier**: Instant attack, exponential decay. No sustain.
- **The "Snap" (Pitch Envelope)**: The crucial element. Because the S-1 lacks a dedicated 
  pitch envelope, we use the Filter Envelope (`CC26` ENV_TO_FILT) sweeping the 
  self-oscillating filter (`CC74` CUTOFF) downward.
- **The Origin**: The `Strike` relies entirely on that transient pitch-dive mimicking 
  the beater hitting the drum skin before the fundamental tone rings out.

Taxonomic Application:
[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Role: Percussive] + [Historical: Percussive-Analog]
"""

import rtmidi
import time
import sys

CH = 2

class CC:
    SAW_LEVEL    = 20; SQ_LEVEL     = 21; SUB_LEVEL    = 19; NOISE_LEVEL  = 23
    FILTER_RES   = 71; AMP_RELEASE  = 72; AMP_ATTACK   = 73
    FILTER_CUTOFF= 74; AMP_DECAY    = 75; AMP_SUSTAIN  = 70
    ENV_TO_FILT  = 26; VOLUME       = 7;  LFO_DEPTH    = 17

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

        print("\n[Agent Gamma] Constructing Analog Pitch-Envelope Kick...")
    
        # Oscillators: Muted. The filter is the oscillator.
        midi.cc(CC.SAW_LEVEL, 0)
        midi.cc(CC.SQ_LEVEL, 0)
        midi.cc(CC.SUB_LEVEL, 0)
        midi.cc(CC.NOISE_LEVEL, 0) # Could add a tiny bit for the beater click, but purely tonal here.

        # Amplifier Envelope (The Body Ring)
        midi.cc(CC.AMP_ATTACK, 0)   # Instant strike
        midi.cc(CC.AMP_DECAY, 55)   # Short exponential boom
        midi.cc(CC.AMP_SUSTAIN, 0)  # No hold
        midi.cc(CC.AMP_RELEASE, 30)

        # The Filter (The Drum Skin)
        midi.cc(CC.FILTER_RES, 127)   # Self-oscillation (Pure Sine)
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 5, 65)) # Fundamental tuned low (~50Hz)
    
        # The "Snap" (Pitch Envelope mapping via Filter Env)
        midi.cc(CC.ENV_TO_FILT, 115)  # Heavy positive depth. 
                                      # It forces the sine wave up high momentarily, 
                                      # then dives down to the 50Hz fundamental as the envelope decays.

        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Agent Gamma] Triggering 4-on-the-floor kick pattern.")
    
        test_note = 48 # Note pitch doesn't matter much since it's self-oscillating filter, 
                       # but keytracking might shift the fundamental slightly.
    
        for i in range(8):
            # The quick gate is all we need.
            midi.on(test_note, 120)
            time.sleep(0.05) 
            midi.off(test_note)
            time.sleep(0.45) # ~120 BPM quarter note timing
        
        print("\n[Agent Gamma] Demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
