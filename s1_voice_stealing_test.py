"""
S-1 Voice Stealing Mechanics Test (Agent Epsilon)
=================================================
This script tests how the 4-voice Roland S-1 handles the 5th incoming note (voice stealing).
It tests:
1. Does it steal the oldest note or the lowest note?
2. How do envelope release stages affect stealing?
3. Are there audible clicks (hard stealing vs envelope smoothed stealing)?

Requirements:
    pip install rtmidi
"""

import time
import sys

try:
    import rtmidi
except ImportError:
    print("rtmidi is required: pip install rtmidi")
    sys.exit(1)

# S-1 CC Map extracted from project defaults
CC = {
    "filter_freq":    74,
    "env_attack":     73,
    "env_decay":      75,
    "env_sustain":    30,
    "env_release":    72,
    "poly_mode":      80,
    "osc_square":     19,
    "osc_saw":        20,
    "osc_sub":        21,
    "reverb_level":   91,
    "delay_level":    92,
}

class MIDIManager:
    """Simplified MIDIManager."""
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
        
    def panic(self):
        if not self._out: return
        self._out.send_message([0xB0 | self.channel, 123, 0])

def setup_synth(midi, long_release=False):
    midi.panic()
    time.sleep(0.5)
    
    # Initialize basic patch, Poly mode
    midi.cc(CC["poly_mode"], 64) # Ensure polyphony
    midi.cc(CC["osc_square"], 0)
    midi.cc(CC["osc_saw"], 127) # Saw wave for clear harmonics
    midi.cc(CC["osc_sub"], 0)
    midi.cc(CC["filter_freq"], 100) # Open filter
    midi.cc(CC["reverb_level"], 0) # Dry signal to hear clearly
    midi.cc(CC["delay_level"], 0)
    
    # Envelope settings
    midi.cc(CC["env_attack"], 10)
    midi.cc(CC["env_decay"], 64)
    midi.cc(CC["env_sustain"], 127)
    
    if long_release:
        midi.cc(CC["env_release"], 100) # Long release
        print("Set synth to LONG release.")
    else:
        midi.cc(CC["env_release"], 20) # Short release
        print("Set synth to SHORT release.")
        
    time.sleep(0.2)
        
def test_stealing_pattern(midi, title, test_notes, steal_note, delay_between=0.5):
    """Plays test notes sequentially, then plays the steal note."""
    print(f"\n--- Test: {title} ---")
    
    # Play 4 notes to fill polyphony buffer
    print("Playing initial 4 voices...")
    for note in test_notes:
        midi.note_on(note)
        time.sleep(delay_between)
        
    print(f"Holding 4 voices for 2 seconds...")
    time.sleep(2.0)
    
    # Trigger 5th note
    print(f">> Triggering 5th note: {steal_note} to force voice stealing <<")
    midi.note_on(steal_note)
    
    print("Listen to which note cut out. (Holding for 3s)")
    time.sleep(3.0)
    
    # Turn all off
    for note in test_notes:
        midi.note_off(note)
    midi.note_off(steal_note)
    time.sleep(1.0)
    
def run_tests():
    midi = MIDIManager(channel=2)
    if not midi.connect():
        print("S-1 MIDI missing.")
        return
        
    print(f"Connected to {midi.port_name}")
    
    # 1. Test chronological stealing (Oldest Note vs Lowest Note)
    # We play C3, E3, G3, B3 (Chronological). The oldest is C3 (lowest), newest is B3 (highest).
    setup_synth(midi, long_release=False)
    test_stealing_pattern(midi, "Chronological Test (C3, E3, G3, B3) -> Steal with C4", 
                          test_notes=[48, 52, 55, 59], steal_note=60, delay_between=0.5)

    # 2. Test chronological stealing reversed (Oldest Note vs Lowest Note)
    # We play B3, G3, E3, C3. The oldest is B3 (highest), newest is C3 (lowest).
    # If it steals B3, it's 'Oldest Note'. If it steals C3, it's 'Lowest Note'.
    test_stealing_pattern(midi, "Reverse Chronological Test (B3, G3, E3, C3) -> Steal with C4", 
                          test_notes=[59, 55, 52, 48], steal_note=60, delay_between=0.5)
                          
    # 3. Test Envelope Release Clicks
    # Play 4 notes, turn them off but they have long release tails. Trigger 5th note.
    # Does it brutally cut the tail (audible click) or crossfade?
    setup_synth(midi, long_release=True)
    print("\n--- Test: Release Tail Stealing ---")
    chord = [48, 52, 55, 59]
    for note in chord:
        midi.note_on(note)
    time.sleep(1.0)
    
    print("Triggering Note Offs (Release tails ringing...)")
    for note in chord:
        midi.note_off(note)
        
    time.sleep(0.5) # Wait mid-release
    print(">> Triggering 5th Note mid-release <<")
    midi.note_on(60)
    print("Listen for clicking on the stolen tail.")
    time.sleep(3.0)
    midi.note_off(60)

    midi.panic()
    print("\nTests complete.")

if __name__ == "__main__":
    run_tests()
