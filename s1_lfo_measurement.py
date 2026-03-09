"""
S-1 LFO Empirical Measurement (Agent Epsilon)
=============================================
This script measures the actual maximum Hz the Roland S-1 LFO can achieve.
Agent Alpha requires this data for pseudo-FM sideband calculations.

Methodology:
1. Set the S-1 to emit a pure sine/triangle wave (sub-osc only, no filter).
2. Apply maximum LFO depth to Pitch.
3. Step through LFO Rate via CC (from 0 to 127).
4. Analyze the pitch excursion of the incoming audio to calculate the real LFO frequency in Hz.

Requirements:
    pip install rtmidi sounddevice numpy scipy
"""

import time
import queue
import argparse
import numpy as np
import sounddevice as sd
from scipy.signal import find_peaks

try:
    import rtmidi
except ImportError:
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
    "lfo_pitch_depth": 18, # Assuming standard mapping, will verify manually
    "lfo_mode":       79,
}

class MIDIManager:
    """Simplified MIDIManager for sending measurement CCs."""
    def __init__(self, channel=2):
        self.channel = channel
        self._out = None
        self.port_name = "None"

    def connect(self):
        try:
            mout = rtmidi.MidiOut()
            ports = mout.get_ports()
            if not ports: return False
            for i, p in enumerate(ports):
                if any(k in p.upper() for k in ('S-1', 'S1', 'ROLAND')):
                    mout.open_port(i)
                    self._out = mout
                    self.port_name = p
                    return True
            mout.open_port(0)
            self._out = mout
            self.port_name = ports[0]
            return True
        except Exception as e:
            print(f"MIDI Error: {e}")
            return False

    def cc(self, cc_num: int, value: int):
        if not self._out: return
        self._out.send_message([0xB0 | self.channel, cc_num, max(0, min(127, int(value)))])

    def note_on(self, note: int):
        if not self._out: return
        self._out.send_message([0x90 | self.channel, note, 100])

    def note_off(self, note: int):
        if not self._out: return
        self._out.send_message([0x80 | self.channel, note, 0])

def analyze_lfo_frequency(audio_device=None, duration=2.0, sr=44100):
    """
    Captures audio, detects the dominant frequency fluctuation, and returns the LFO Hz.
    This uses a simple zero-crossing or envelope peak detection method.
    """
    q = queue.Queue()
    
    def audio_callback(indata, frames, time, status):
        """This is called for each audio block by sounddevice."""
        if status:
            pass # ignore status for now
        q.put(indata.copy())
        
    print("Capturing Audio...")
    with sd.InputStream(device=audio_device, channels=1, samplerate=sr, callback=audio_callback):
        time.sleep(duration)
        
    # Gather chunks
    chunks = []
    while not q.empty():
        chunks.append(q.get())
        
    if not chunks:
        return 0.0
        
    audio_data = np.concatenate(chunks).flatten()
    
    # Simple amplitude envelope given pitch depth creates amplitude variations in bandpass
    # Alternatively, perform FM demodulation (complex). 
    # For a rough measurement, if it's clicking/pulsing at extreme rates, peak detection on the rect signal works.
    
    rectified = np.abs(audio_data)
    # Low pass filter the rectified signal to get the envelope shape
    window_size = sr // 100  # 10ms window
    envelope = np.convolve(rectified, np.ones(window_size)/window_size, mode='same')
    
    # Find peaks in the envelope
    peaks, _ = find_peaks(envelope, distance=sr//500) # Max 500Hz detection
    
    if len(peaks) < 2:
        return 0.0
        
    # Calculate average distance between peaks in seconds
    avg_distance_samples = np.mean(np.diff(peaks))
    lfo_hz = sr / avg_distance_samples
    
    return float(lfo_hz)

def run_measurement_sweep():
    midi = MIDIManager(channel=2)
    if not midi.connect():
        print("S-1 MIDI missing.")
        return
        
    print(f"Connected to {midi.port_name}")
    
    # Flatten synth to a pure tone
    midi.cc(CC["osc_square"], 0)
    midi.cc(CC["osc_saw"], 0)
    midi.cc(CC["osc_sub"], 127)
    midi.cc(CC["noise_level"], 0)
    midi.cc(CC["filter_freq"], 127)
    midi.cc(CC["filter_res"], 0)
    
    # Set LFO params
    midi.cc(CC["lfo_depth"], 127) # Max pitch depth if routed, or filter depth
    
    test_rates = [0, 32, 64, 96, 127]
    results = {}
    
    print("\n--- Starting Sweep (Normal Mode) ---")
    midi.cc(CC["lfo_mode"], 0) # Normal Mode
    for rate in test_rates:
        midi.cc(CC["lfo_rate"], rate)
        time.sleep(0.5)
        midi.note_on(60)
        time.sleep(0.5)
        
        hz = analyze_lfo_frequency(duration=1.5)
        results[f"Normal_CC{rate}"] = hz
        print(f"CC {rate:3d} -> ~{hz:6.2f} Hz")
        midi.note_off(60)

    print("\n--- Starting Sweep (Fast Mode) ---")
    midi.cc(CC["lfo_mode"], 127) # Audiorate/Fast Mode
    for rate in test_rates:
        midi.cc(CC["lfo_rate"], rate)
        time.sleep(0.5)
        midi.note_on(60)
        time.sleep(0.5)
        
        hz = analyze_lfo_frequency(duration=1.5)
        results[f"Fast_CC{rate}"] = hz
        print(f"CC {rate:3d} -> ~{hz:6.2f} Hz")
        midi.note_off(60)

    print("\nMeasurement Summary:")
    print("Agent Alpha, these are the sideband modulating frequencies available:")
    for key, val in results.items():
        print(f"{key}: {val:.2f} Hz")

if __name__ == "__main__":
    run_measurement_sweep()
