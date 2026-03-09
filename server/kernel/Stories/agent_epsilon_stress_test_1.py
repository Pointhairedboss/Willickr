#!/usr/bin/env python3
"""
AGENT EPSILON (HARDWARE SPECIALIST) — PATCH 001: "LFO Frequency Cap Stress Test"

Objective:
  Agent Alpha requires the absolute maximum LFO frequency (in Hz) that the S-1 can output 
  when LFO Rate (CC3) is set to 127. This is necessary for accurate pseudo-FM sideband calculations.
  
Method:
  Map LFO to Pitch, sweep the LFO rate up to 127, and trigger a sustained note.
  The resulting audio can be analyzed (e.g., via Praat or a DAW's frequency analyzer) 
  to extract the actual modulation frequency in Hz.

Taxonomic Application:
[Origin: Artifacting/Failure-State] + [Behavior: Static] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: FX]
"""

import rtmidi
import time
import sys

CH = 2  # S-1 default

class CC:
    LFO_RATE      = 3
    PITCH_LFO     = 17 # Assuming this routes LFO to Pitch, common routing. Let's send a high value.
    OSC_SQUARE    = 21
    AMP_ATTACK    = 73
    AMP_DECAY     = 75
    AMP_SUSTAIN   = 70
    AMP_RELEASE   = 72

class Midi:
    def __init__(self, hint=None):
        self._o = rtmidi.MidiOut()
        ports = self._o.get_ports()
        opened = False
        if hint:
            for i, p in enumerate(ports):
                if hint.lower() in p.lower():
                    self._o.open_port(i); print(f"Opened (Hint): {p}"); opened = True; break
        if not opened:
            for i, p in enumerate(ports):
                if any(k in p.upper() for k in ('S-1', 'S1', 'ROLAND', 'AIRA')):
                    self._o.open_port(i); print(f"Opened (Auto): {p}"); opened = True; break
        if not opened:
            self._o.open_virtual_port("S1-Epsilon"); print("Virtual port created")

    def cc(self, c, v):  self._o.send_message([0xB0 | CH, c, max(0, min(127, int(v)))])
    def on(self, n, v=75): self._o.send_message([0x90 | CH, n & 127, max(1, min(127, v))])
    def off(self, n):    self._o.send_message([0x80 | CH, n & 127, 0])
    def panic(self):     self._o.send_message([0xB0 | CH, 123, 0])

def test_lfo_max_rate(midi: Midi):
    print("Agent Epsilon: Initializing LFO Frequency Stress Test...")
    
    # Simple clear patch
    midi.cc(CC.OSC_SQUARE, 127) # Strong fundamental
    midi.cc(CC.AMP_ATTACK, 0)
    midi.cc(CC.AMP_DECAY, 127)
    midi.cc(CC.AMP_SUSTAIN, 127) # Sustained note for analysis
    midi.cc(CC.AMP_RELEASE, 20)
    
    # Route LFO to Pitch (maximum depth)
    midi.cc(CC.PITCH_LFO, 127) 
    
    print("Agent Epsilon: Triggering Test Note (C4).")
    test_note = 60
    midi.on(test_note, 100)
    
    print("Agent Epsilon: Sweeping LFO Rate from 0 to 127...")
    for rate in range(0, 128, 5):
        midi.cc(CC.LFO_RATE, rate)
        print(f"  LFO CC3 = {rate}")
        time.sleep(0.1)
        
    midi.cc(CC.LFO_RATE, 127)
    print("\n[!] LFO CC3 = 127 (MAX).")
    print("[!] Hold note for 5 seconds to capture audio for frequency analysis...")
    time.sleep(5.0)
    
    print("Agent Epsilon: Releasing Note.")
    midi.off(test_note)
    print("Agent Epsilon: Test Complete. Awaiting empirical Hz analysis of the captured audio.")

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    m = Midi(hint=hw_hint)
    test_lfo_max_rate(m)
