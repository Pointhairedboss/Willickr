"""
S-1 Hardware Stress Test (Agent Epsilon)
========================================
This script is designed to test the hardware limits of the Roland S-1 ACB engine.
It floods the S-1 with high-density MIDI CC data to observe:
1. Baud rate constraints (dropped messages)
2. DSP artifacting under heavy modulation
3. Voice-stealing behavior under extreme rapid parameter changes

Requirements:
    pip install rtmidi numpy

Usage:
    python s1_hardware_stress_test.py
"""

import time
import threading
import argparse
import random
import numpy as np

try:
    import rtmidi
    HAS_MIDI = True
except ImportError:
    HAS_MIDI = False
    print("rtmidi is required: pip install rtmidi")
    exit(1)

# S-1 CC Map extracted from project defaults
CC = {
    "filter_freq":    74,
    "filter_res":     71,
    "noise_level":    23,
    "osc_square":     19,
    "osc_saw":        20,
    "osc_sub":        21,
    "lfo_rate":        3,
    "lfo_depth":      17,
    "env_attack":     73,
    "env_decay":      75,
    "env_sustain":    30,
    "env_release":    72,
    "reverb_level":   91,
    "reverb_time":    89,
    "delay_level":    92,
    "poly_mode":      80,
    "portamento":      5,
    "portamento_sw":  31,
    "chorus_type":    93,
    "filter_env":     24,
    "filter_lfo":     25,
    "filter_follow":  26,
    "lfo_mode":       79,
}

class MIDIManager:
    """Simplified MIDIManager for stress testing."""
    def __init__(self, channel=2):
        self.channel = channel
        self._out = None
        self.port_name = "None"
        self.connected = False

    def connect(self, name_hint="S-1"):
        try:
            mout = rtmidi.MidiOut()
            ports = mout.get_ports()
            if not ports:
                print("No MIDI ports found.")
                return False
            
            for i, p in enumerate(ports):
                if name_hint.lower() in p.lower() or any(k in p.upper() for k in ('S-1', 'S1', 'ROLAND')):
                    mout.open_port(i)
                    self._out = mout
                    self.port_name = p
                    self.connected = True
                    return True
            
            # Fallback
            mout.open_port(0)
            self._out = mout
            self.port_name = ports[0]
            self.connected = True
            return True
        except Exception as e:
            print(f"MIDI Connection Error: {e}")
            return False

    def cc(self, cc_num: int, value: int):
        if not self._out: return
        value = max(0, min(127, int(value)))
        self._out.send_message([0xB0 | self.channel, cc_num, value])

    def note_on(self, note: int, velocity: int = 80):
        if not self._out: return
        self._out.send_message([0x90 | self.channel, note, velocity])

    def note_off(self, note: int):
        if not self._out: return
        self._out.send_message([0x80 | self.channel, note, 0])

    def panic(self):
        if not self._out: return
        self._out.send_message([0xB0 | self.channel, 123, 0])

def test_baud_rate_flood(midi, duration=5.0, params_per_cycle=10, delay_ms=1):
    """
    Floods the S-1 with rapid CC changes across multiple parameters.
    Objective: Observe zipper noise, dropped messages, or DSP freezing.
    """
    print(f"\n[Test] Starting Baud Rate Flood ({params_per_cycle} params/cycle, {delay_ms}ms delay)")
    
    # Target heavy DSP parameters
    target_ccs = [
        CC["filter_freq"], CC["filter_res"], CC["lfo_rate"], 
        CC["reverb_level"], CC["reverb_time"], CC["delay_level"],
        CC["env_attack"], CC["env_release"], CC["osc_square"], CC["osc_saw"]
    ]
    
    start_time = time.time()
    msg_count = 0
    
    # Hold a chord to clearly hear artifacts
    chord = [48, 52, 55, 60]  # C Major
    for note in chord:
        midi.note_on(note)
        
    try:
        while time.time() - start_time < duration:
            # Send block of CCs rapidly
            for _ in range(params_per_cycle):
                cc_num = random.choice(target_ccs)
                val = random.randint(0, 127)
                midi.cc(cc_num, val)
                msg_count += 1
            if delay_ms > 0:
                time.sleep(delay_ms / 1000.0)
    except KeyboardInterrupt:
        pass
        
    for note in chord:
        midi.note_off(note)
        
    actual_duration = time.time() - start_time
    rate = msg_count / actual_duration
    print(f"Finished. Sent {msg_count} CC messages in {actual_duration:.2f}s (~{rate:.0f} msgs/sec)")
    return rate

def test_audio_rate_modulation(midi, duration=3.0):
    """
    Steps parameters at extreme speeds to provoke buffer artifacts.
    """
    print(f"\n[Test] Audio-Rate CC Stepping")
    midi.cc(CC["lfo_mode"], 127)  # Try to force fast LFO mode if applicable
    
    midi.note_on(36, 127) # Low C
    
    start_time = time.time()
    val = 0
    try:
        while time.time() - start_time < duration:
            val = 127 if val == 0 else 0
            midi.cc(CC["filter_freq"], val)
            # No sleep - absolute maximum throughput
    except KeyboardInterrupt:
        pass
        
    midi.note_off(36)
    print("Audio-rate stepping complete.")

def run_all_tests():
    midi = MIDIManager(channel=2) # Channel 3
    if not midi.connect():
        print("Failed to connect to S-1. Is it plugged in?")
        return
        
    print(f"Connected to {midi.port_name} on Channel {midi.channel+1}")
    midi.panic()
    time.sleep(0.5)
    
    # 1. Baseline Flood Test
    test_baud_rate_flood(midi, duration=3.0, params_per_cycle=5, delay_ms=5)
    time.sleep(1)
    
    # 2. Extreme Flood Test (Zero Delay)
    test_baud_rate_flood(midi, duration=3.0, params_per_cycle=15, delay_ms=0)
    time.sleep(1)
    
    # 3. Audio Rate Stepping
    test_audio_rate_modulation(midi, duration=3.0)
    
    midi.panic()
    print("\nAll tests complete. Did you hear DSP artifacting or glitching?")

if __name__ == "__main__":
    run_all_tests()
