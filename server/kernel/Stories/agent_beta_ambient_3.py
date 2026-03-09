#!/usr/bin/env python3
"""
AGENT BETA (AMBIENT) — PATCH 003: "The Neon Buzz"

Taxonomy:
[Origin: Fracture] + [Behavior: Static] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: FX]

Theory Implemented:
  1. Textural Room Tone: To construct credible environmental spaces, standard white noise is often too 
     uniform. By exploiting the S-1's precise DRAW MULTIPLY (CC102) and CHOP (CC103) functions, we 
     generate inharmonic, metallic "dirt" simulating an electrical neon sign buzz or a failing HVAC unit.
  2. Sustained Presence: Ambient design requires continuous room tone. The envelope is mostly flat,
     allowing the texture to sit evenly in the background of a scene.
  3. Micro-ambience: Keeping the cutoff at mid-level prevents it from washing out the dialogue or 
     primary musical elements, keeping it locked to the perceptual background.

Usage:
    python agent_beta_ambient_3.py
"""

import rtmidi
import time
import sys

CH = 2  # 0-indexed MIDI channel (S-1 default = 3 = index 2)

class CC:
    # S-1 CC Map
    VOLUME        = 7;   PW            = 15
    SUB_LEVEL     = 19;  SAW_LEVEL     = 20
    OSC_SQUARE    = 21;  NOISE_LEVEL   = 23
    FILTER_RES    = 71;  AMP_RELEASE   = 72
    AMP_ATTACK    = 73;  FILTER_CUTOFF = 74
    AMP_DECAY     = 75;  AMP_SUSTAIN   = 70
    REVERB_LEVEL  = 91;  DELAY_LEVEL   = 92
    
    # Textural Oscillators
    OSC_DRAW_MULT = 102
    CHOP_OVER     = 103
    CHOP_COMB     = 104

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
            self._o.open_virtual_port("S1-Beta"); print("Virtual port")

    def cc(self, c, v):  self._o.send_message([0xB0 | CH, c, max(0, min(127, int(v)))])
    def on(self, n, v=75): self._o.send_message([0x90 | CH, n & 127, max(1, min(127, v))])
    def off(self, n):    self._o.send_message([0x80 | CH, n & 127, 0])
    def panic(self):     self._o.send_message([0xB0 | CH, 123, 0])

def build_neon_buzz(midi: Midi):
    print("Agent Beta: Initializing 'The Neon Buzz' patch...")
    
    # 1. Textural Base (Replacing standard noise)
    midi.cc(CC.SAW_LEVEL, 0)
    midi.cc(CC.OSC_SQUARE, 80)     # Carrier for the glitch texturing
    midi.cc(CC.SUB_LEVEL, 0) 
    midi.cc(CC.NOISE_LEVEL, 10)    # Minimal pure white noise
    
    # 2. DRAW & CHOP Operations (The Room Tone Dirt)
    midi.cc(CC.OSC_DRAW_MULT, 110) # Heavy overtones/multiply pushing into static
    midi.cc(CC.CHOP_OVER, 90)      # High foldover/chopping for metallic electrical buzz
    midi.cc(CC.CHOP_COMB, 60)      # Comb filtering to create resonance pockets
    
    # 3. Filter Placement
    midi.cc(CC.FILTER_CUTOFF, 65)  # Keep the buzz present but not harsh
    midi.cc(CC.FILTER_RES, 45)     # Moderate ring to emphasize the metallic comb
    
    # 4. Continuous Envelope
    midi.cc(CC.AMP_ATTACK, 20)     # Very fast fade-in
    midi.cc(CC.AMP_DECAY, 0)      
    midi.cc(CC.AMP_SUSTAIN, 100)   # Continuous volume while held
    midi.cc(CC.AMP_RELEASE, 40)    # Short-ish release, dies out when power is cut
    
    # 5. Spatial
    midi.cc(CC.REVERB_LEVEL, 30)   # Tight space (close micro-ambience rather than canyon)
    midi.cc(CC.DELAY_LEVEL, 0)
    midi.cc(CC.VOLUME, 60)         # Background level
    
    time.sleep(0.5)

def play_buzz(midi: Midi):
    print("Agent Beta: Running continuous buzz sequence. Press Ctrl+C to stop.")
    try:
        while True:
            note = 36  # C2 - deep electrical hum frequency range
            midi.on(note, 65)
            print("⚡ Room Tone ON")
            
            time.sleep(15.0)  # Hold the drone for a long time
            
            midi.off(note)
            print("⬛ Room Tone OFF (power cycle)")
            time.sleep(2.0)
            
    except KeyboardInterrupt:
        print("\nAgent Beta: Halting room tone.")
        midi.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    m = Midi(hint=hw_hint)
    build_neon_buzz(m)
    play_buzz(m)
