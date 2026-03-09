#!/usr/bin/env python3
"""
Agent Epsilon — Patch 002: "The Buffer Overload (Zipper Glitch)"

Objective: To intentionally stress the S-1's MIDI buffer and processor 
handling by flooding it with high-density control change (CC) data 
while simultaneously demanding maximum polyphony and FX processing.

Theory of Operation (Hardware Glitching):
- The S-1 handles standard MIDI CC automation well. However, when multiple 
  parameters are swept simultaneously rapidly, the processor must prioritize 
  voice generation over control smoothing.
- **The "Zipper Noise"**: By forcing rapid, non-musical steps in the Filter Cutoff (`CC74`) 
  and Resonance (`CC71`) via Python looping, we intentionally induce "zipper noise" — 
  the audible artifact of digital parameter stepping lacking interpolation latency.
- **The CPU Drain**: To ensure the processor struggles, we trigger 4-voice chords 
  (max polyphony) while sweeping Reverb (`CC91`) and Delay (`CC92`) sizes. 
  The struggle of the hardware forms the texture of the patch.

Taxonomic Application:
[Origin: Artifacting/Failure-State] + [Behavior: Unstable] + [Emotion: Dread] + [Role: FX] + [Stress: Glitch-State]
"""

import rtmidi
import time
import random

CH = 2

class CC:
    FILTER_CUTOFF= 74; FILTER_RES   = 71
    REVERB_LEVEL = 91; DELAY_LEVEL  = 92
    SAW_LEVEL    = 20; SQ_LEVEL     = 21
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
            self._o.open_virtual_port("S1-Epsilon-Glitch"); print("Virtual port")

    def cc(self, c, v): self._o.send_message([0xB0 | CH, c, max(0, min(127, int(v)))])
    def on(self, n, v=75): self._o.send_message([0x90 | CH, n & 127, max(1, min(127, v))])
    def off(self, n): self._o.send_message([0x80 | CH, n & 127, 0])

def build_foundation(midi: Midi):
    print("\n[Agent Epsilon] Constructing high-drain foundational patch...")
    # Heavy oscillators and long envelopes to ensure the voices stay active
    midi.cc(CC.SAW_LEVEL, 127)
    midi.cc(CC.SQ_LEVEL, 127)
    midi.cc(CC.AMP_ATTACK, 5)
    midi.cc(CC.AMP_DECAY, 127)
    midi.cc(CC.AMP_SUSTAIN, 127)
    midi.cc(CC.AMP_RELEASE, 110)
    midi.cc(CC.REVERB_LEVEL, 127)
    midi.cc(CC.DELAY_LEVEL, 127)
    midi.cc(CC.VOLUME, 100)
    time.sleep(0.1)

def stress_test_buffer(midi: Midi):
    build_foundation(midi)
    
    print("\n[Agent Epsilon] Triggering max polyphony (4 voices).")
    chord = [48, 55, 60, 63] # C, G, C, Eb
    for n in chord:
        midi.on(n, 120)
        
    print("[Agent Epsilon] Initiating high-density CC flood to induce zipper artifacting...")
    
    # Send rapid, conflicting CC data to choke the smoothing algorithms
    # We use very short sleep times to flood the USB MIDI buffer
    for _ in range(300):
        midi.cc(CC.FILTER_CUTOFF, random.randint(10, 120))
        midi.cc(CC.FILTER_RES, random.randint(80, 127))
        # Rapidly changing delay sizes forces the DSP to recalculate the buffer
        midi.cc(CC.DELAY_LEVEL, random.choice([0, 127])) 
        time.sleep(0.005) # 5ms loop = ~600 CC messages per second

    print("\n[Agent Epsilon] Releasing chord.")
    for n in chord:
        midi.off(n)
        
    # Let the glitched Verb/Delay tails ring out
    time.sleep(2.0)
    # Clean up
    midi.cc(CC.REVERB_LEVEL, 0); midi.cc(CC.DELAY_LEVEL, 0); midi.cc(CC.FILTER_CUTOFF, 80)
    print("[Agent Epsilon] Demonstration concluded.")

if __name__ == "__main__":
    m = Midi()
    stress_test_buffer(m)
