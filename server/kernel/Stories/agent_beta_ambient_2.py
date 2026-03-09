#!/usr/bin/env python3
"""
AGENT BETA (AMBIENT) — PATCH 002: "The Harmonic Tide"

Taxonomy:
  [Origin: Flow] + [Behavior: Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Bed/Pad]

Theory Implemented:
  1. Blended Approach: Taking the advice of Agent Alpha, this patch blends the harmonic complexity of 
     audio-rate LFO pseudo-FM with the spatial smearing and self-oscillating filters of ambient beds.
  2. The Carrier/Modulator Shift: Because the LFO (Modulator) is pushed high and routed to Pitch, while
     the Filter (Formant) is brought to near self-oscillation, the resulting interaction creates 
     fluid, glassy overtones that wash in and out.
  3. Slow Envelope Evolution: The amp envelope's extremely slow attack and release turn the inharmonic
     sidebands into a slow, melancholic tide rather than a percussive bell.
  4. Pitch Drift: A very slow sequence in the script triggers overlapping chords that bleed into
     each other via the delay buffer, creating interference patterns.

Usage:
    python agent_beta_ambient_2.py
"""

import rtmidi
import time
import random
import sys

CH = 2  # 0-indexed MIDI channel (S-1 default = 3 = index 2)

class CC:
    # S-1 CC Map
    LFO_RATE      = 3;   PORTAMENTO    = 5;   VOLUME        = 7
    PW            = 15;  LFO_DEPTH     = 17;  SUB_LEVEL     = 19
    SAW_LEVEL     = 20;  OSC_SQUARE    = 21;  NOISE_LEVEL   = 23
    LFO_TO_FILT   = 25;  FILTER_RES    = 71;  AMP_RELEASE   = 72
    AMP_ATTACK    = 73;  FILTER_CUTOFF = 74;  AMP_DECAY     = 75
    AMP_SUSTAIN   = 70;  REVERB_LEVEL  = 91;  DELAY_LEVEL   = 92

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

def build_harmonic_tide(midi: Midi):
    print("Agent Beta: Initializing 'The Harmonic Tide' patch...")
    
    # 1. Base Core (Carrier)
    midi.cc(CC.SAW_LEVEL, 0)
    midi.cc(CC.OSC_SQUARE, 60)     # Muted square
    midi.cc(CC.SUB_LEVEL, 40)      # Underlying low end support
    midi.cc(CC.NOISE_LEVEL, 0)
    
    # 2. Pseudo-FM (Modulator via LFO)
    midi.cc(CC.LFO_RATE, 115)      # Fast, but not maxed out, creating warbling sidebands
    midi.cc(CC.LFO_DEPTH, 25)      # Subtler index modulation than Alpha's percussive bell
    midi.cc(CC.LFO_TO_FILT, 40)    # Modulate filter slightly to sweep the formants
    
    # 3. Formant (Filter set near self-oscillation to sing)
    midi.cc(CC.FILTER_CUTOFF, 55)  # Mid-low cutoff, will sweep via LFO
    midi.cc(CC.FILTER_RES, 110)    # Just below full self-oscillation (115-127)
    
    # 4. Melancholic Envelope
    midi.cc(CC.AMP_ATTACK, 85)     # Very slow, rolling attack (the tide coming in)
    midi.cc(CC.AMP_DECAY, 60)      
    midi.cc(CC.AMP_SUSTAIN, 90)    # Substantial drone hold
    midi.cc(CC.AMP_RELEASE, 55)    # Reduced release to prevent 3-note chords overlapping and stealing voices
    
    # 5. Spatial Ocean
    midi.cc(CC.REVERB_LEVEL, 127)  # Maximum space
    midi.cc(CC.DELAY_LEVEL, 85)    # Increased delay to blur the chords together
    midi.cc(CC.VOLUME, 85)
    
    time.sleep(0.5)

def generative_tides(midi: Midi):
    print("Agent Beta: Starting generative harmonic tides. Press Ctrl+C to stop.")
    
    # F minor9 spread chords
    chords = [
        [41, 48, 56], # F2, C3, Ab3
        [43, 50, 58], # G2, D3, Bb3
        [44, 51, 60], # Ab2, Eb3, C4
        [39, 48, 55], # Eb2, C3, G3
    ]
    
    try:
        while True:
            chord = random.choice(chords)
            velocity = random.randint(40, 75)
            
            print(f"🌊 Washing over chord: {chord} (vel: {velocity})")
            
            for note in chord:
                midi.on(note, velocity)
                
            # Full sustain drone
            time.sleep(random.uniform(4.0, 8.0))
            
            # The release
            for note in chord:
                midi.off(note)
                
            # Allow the spatial engine to wash the chords together, avoiding voice clipping
            time.sleep(random.uniform(3.0, 5.0))
            
    except KeyboardInterrupt:
        print("\nAgent Beta: Halting tides.")
        midi.panic()

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    m = Midi(hint=hw_hint)
    build_harmonic_tide(m)
    generative_tides(m)
