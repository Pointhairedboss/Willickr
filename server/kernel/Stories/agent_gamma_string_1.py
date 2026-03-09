#!/usr/bin/env python3
"""
Agent Gamma — Patch 002: "The Solina Bow"

Objective: To recreate the classic 70s String Machine (e.g., Solina, ARP Omni) 
utilizing Gordon Reid's structural acoustic principles for bowed strings.

Theory of Operation (Subtractive String Synthesis):
A bowed string is not a percussive strike; it is a continuously excited harmonic 
system.
- **The Oscillators**: A strict SAW waveform. A square wave lacks the even harmonics 
  necessary for the complex rosined friction of a bow.
- **The Amplifier**: A slow, linear attack simulating the bow catching the string, 
  and a moderate release. The sound must not clamp shut immediately.
- **The Filter**: Unlike brass, the filter does not sweep aggressively, nor does it close. 
  It stays relatively open with high resonance to act as the wooden body of the cello/violin.
- **The Vibrato (Crucial)**: Without LFO pitch modulation, it sounds like an organ. 
  A delayed LFO (introduced via CC over time, or inherent S-1 delay) modulating pitch 
  mimics the player's vibrato applied *after* the note speaks.

Taxonomic Application:
[Origin: Bow] + [Behavior: Evolving] + [Emotion: Melancholia] + [Role: Lead] + [Historical: String-Machine]
"""

import rtmidi
import time
import sys
import threading

CH = 2

class CC:
    LFO_RATE     = 3;  PORTAMENTO   = 5;  VOLUME       = 7
    PW           = 15; LFO_DEPTH    = 17; SUB_LEVEL    = 19
    SAW_LEVEL    = 20; SQ_LEVEL     = 21; NOISE_LEVEL  = 23
    LFO_TO_FILT  = 25; FILTER_RES   = 71; AMP_RELEASE  = 72
    AMP_ATTACK   = 73; FILTER_CUTOFF= 74; AMP_DECAY    = 75
    AMP_SUSTAIN  = 70; ENV_TO_FILT  = 26
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

        print("\n[Agent Gamma] Constructing Classic String Machine...")
    
        # Oscillators: Pure Sawtooth
        midi.cc(CC.SAW_LEVEL, 127)  
        midi.cc(CC.SQ_LEVEL, 0)
        midi.cc(CC.SUB_LEVEL, 15)  # Very slight sub for cello weight
        midi.cc(CC.NOISE_LEVEL, 0)

        # Amplifier Envelope (The Bow)
        midi.cc(CC.AMP_ATTACK, 50)  # Slow build
        midi.cc(CC.AMP_DECAY, 127)  # No decay drop-off
        midi.cc(CC.AMP_SUSTAIN, 127)# Full sustain while bowed
        midi.cc(CC.AMP_RELEASE, 65) # Lyrical fade out

        # The Filter (The Wooden Body)
        midi.cc(self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", 55, 115)) # Mostly open, letting the saw through
        midi.cc(CC.FILTER_RES, 45)    # Resonant peak for formant body
        midi.cc(CC.ENV_TO_FILT, 64)   # Neutral (12 noon), no sweep
    
        # The Vibrato (LFO)
        midi.cc(CC.LFO_RATE, 75)   # Standard ~5-6Hz human vibrato speed
        midi.cc(CC.LFO_TO_FILT, 0) # Keep off the filter
        midi.cc(CC.LFO_DEPTH, 0)   # Start at 0, introduced dynamically
    
        # Spatial
        midi.cc(self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100)) # Heavy ensemble chorus/verb emulation
        midi.cc(CC.DELAY_LEVEL, 0)
        midi.cc(self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127))
    
        time.sleep(0.1)



    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive(midi)
        
        print(f"\n[Agent Gamma] Triggering sequence for {duration}s.")
        print("\n[Agent Gamma] Playing slow melody, fading in pitch vibrato manually.")
    
        notes = [(60, 2.0), (62, 1.5), (63, 3.0)] # C, D, Eb (C minor line)
    
        for note, duration in notes:
            print(f"  Bowing note: {note}")
            midi.on(note, 90)
        
            # Simulate delayed vibrato by ramping CC17 over the duration
            for step in range(10):
                lfo_amt = int(step * 3.5) # Ramp 0 to ~35 depth
                midi.cc(CC.LFO_DEPTH, lfo_amt)
                time.sleep(duration / 10.0)
            
            midi.off(note)
        
            # Reset vibrato for the next "bow stroke"
            midi.cc(CC.LFO_DEPTH, 0)
            time.sleep(0.5) # Breath between notes
        
        time.sleep(2.0)
        print("\n[Agent Gamma] Demonstration concluded.")


if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4})
    cartridge.execute(duration=5.0, device_id=hw_hint)
