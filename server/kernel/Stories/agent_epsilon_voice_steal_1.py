#!/usr/bin/env python3
"""
Agent Epsilon — Patch 003: "The Voice-Stealing Rhythm"

Objective: To weaponize the 4-voice polyphony limit of the S-1 ACB engine 
by intentionally triggering a 5th simultaneous note.

Theory of Operation (Voice Mechanics):
- The S-1 is strictly 4-voice polyphonic. When a 5th note is triggered while 
  4 are already sounding, the synth must steal a voice. 
- **The Click**: By setting a very long release tail (`CC72`), playing a sustained 
  3-note chord, and then rapidly firing two alternating sequenced notes, we force 
  the S-1 to constantly steal voices that are in the middle of their release phase.
- Because the envelope is interrupted instantly rather than decaying naturally, 
  it produces an audible "click" or drop-out.
- Instead of treating this as a flaw, we quantize the 5th-note triggers to 
  create a rhythmic, generative clicking texture atop the chord.

Taxonomic Application:
[Origin: Artifacting/Failure-State] + [Behavior: Rhythmic] + [Emotion: Tension] + [Role: Rhythmic] + [Stress: Edge-Case]
"""

import rtmidi
import time

CH = 2

class CC:
    FILTER_CUTOFF= 74; FILTER_RES   = 71; SAW_LEVEL    = 20
    AMP_ATTACK   = 73; AMP_RELEASE  = 72; AMP_DECAY = 75; AMP_SUSTAIN = 70
    VOLUME       = 7

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
            self._o.open_virtual_port("S1-Epsilon-Steal"); print("Virtual port")

    def cc(self, c, v): self._o.send_message([0xB0 | CH, c, max(0, min(127, int(v)))])
    def on(self, n, v=75): self._o.send_message([0x90 | CH, n & 127, max(1, min(127, v))])
    def off(self, n): self._o.send_message([0x80 | CH, n & 127, 0])

def build_pad(midi: Midi):
    print("\n[Agent Epsilon] Constructing foundation with long release tails...")
    midi.cc(CC.SAW_LEVEL, 127)
    midi.cc(CC.FILTER_CUTOFF, 40) # Dark pad
    midi.cc(CC.FILTER_RES, 0)
    
    midi.cc(CC.AMP_ATTACK, 40)
    midi.cc(CC.AMP_DECAY, 127)
    midi.cc(CC.AMP_SUSTAIN, 127)
    midi.cc(CC.AMP_RELEASE, 115) # Very long tail, takes ~5 seconds to clear
    
    midi.cc(CC.VOLUME, 100)
    time.sleep(0.1)

def exploit_voice_stealing(midi: Midi):
    build_pad(midi)
    
    # 3 voices consumed by the pad
    pad_notes = [60, 64, 67] # C major
    print("\n[Agent Epsilon] Triggering 3-voice pad (Voices 1, 2, 3 occupied).")
    for n in pad_notes:
        midi.on(n, 80)
        
    time.sleep(1.0) # Let the pad swell
    
    print("[Agent Epsilon] Releasing pad to let the long Release tail hold the voices.")
    for n in pad_notes:
        midi.off(n)
        
    # Voices 1, 2, 3 are now in RELEASE phase, but still occupying hardware slots
    # Voice 4 is free.
    
    print("[Agent Epsilon] Triggering rapid 2-note sequence (demanding Voices 4 AND 5).")
    print("This will force the hardware to cut off the pad tails with an audible click.")
    
    seq_notes = [48, 55] # Low C, Low G
    
    for i in range(16):
        n = seq_notes[i % 2]
        # We fire the note
        midi.on(n, 120)
        time.sleep(0.125) # 16th note timing
        # We release the note, but its release tail (115) means it doesn't free the voice instantly
        midi.off(n)
        time.sleep(0.125)
        
    print("\n[Agent Epsilon] Demonstration concluded. Listen for the rhythmic dropouts.")

if __name__ == "__main__":
    m = Midi()
    exploit_voice_stealing(m)
