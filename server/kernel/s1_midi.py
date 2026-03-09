import rtmidi
import mido
import time

# Shared CC Dictionary for the Roland S-1 ACB Engine
# Agent Gamma subclasses (P, K, W) MUST use this centralized mapping.

class CC:
    # --- Oscillators & Mix ---
    VOLUME        = 7     # Master level
    PITCH         = 17    # LFO -> Pitch depth
    SUB_LEVEL     = 19    # Sub-osc volume
    SAW_LEVEL     = 20    # Sawtooth volume
    OSC_SQUARE    = 21    # Square volume
    NOISE_LEVEL   = 23    # White/Pink Noise volume
    
    # --- Filter (VCF) ---
    FILTER_LFO    = 25    # LFO -> Filter Cutoff depth
    FILTER_ENV    = 26    # Envelope -> Filter Cutoff depth
    FILTER_RES    = 71    # Resonance (127 = self oscillation)
    FILTER_CUTOFF = 74    # Cutoff frequency
    
    # --- Envelopes (ENV) - Note S-1 shares VCA and VCF envelopes ---
    AMP_ATTACK    = 73
    AMP_DECAY     = 75
    AMP_SUSTAIN   = 70
    AMP_RELEASE   = 72
    
    # --- LFO ---
    LFO_RATE      = 3
    LFO_SHAPE     = 12    # Sine, Tri, Saw, Square, S&H, Random
    LFO_MODE      = 79    # Normal vs Audio-Rate (Fast)
    
    # --- Effects Engine ---
    CHORUS_LEVEL  = 93
    REVERB_LEVEL  = 91
    DELAY_LEVEL   = 92
    
    # --- Textural Operations (DRAW / CHOP) ---
    OSC_DRAW_MULT = 102
    CHOP_OVER     = 103
    CHOP_COMB     = 104


class Midi:
    """Unified MIDI interface for parallel Gamma patches."""
    def __init__(self, hint=None, channel=2, output_filename="virtual_sequence.mid"):
        self.ch = channel  # S-1 defaults to 0-indexed channel 2 (MIDI Ch 3)
        self.is_offline = (hint == "offline")
        self.output_filename = output_filename
        
        self._o = None
        self.offline_file = None
        self.offline_track = None
        self.last_event_time = 0
        self.ticks_per_second = 960  # 120 bpm = 2 beats/sec, 480 ticks/beat -> 960 ticks/sec
        
        if self.is_offline:
            self.offline_file = mido.MidiFile(ticks_per_beat=480)
            self.offline_track = mido.MidiTrack()
            self.offline_file.tracks.append(self.offline_track)
            
            # Insert initialization events (tempo 120 bpm)
            self.offline_track.append(mido.MetaMessage('set_tempo', tempo=mido.bpm2tempo(120), time=0))
            self.last_event_time = time.time()
            print(f"Opened Virtual MIDI Buffer: {self.output_filename}")
        else:
            self._o = rtmidi.MidiOut()
            ports = self._o.get_ports()
            opened = False
            
            # User defined hint string
            if hint:
                for i, p in enumerate(ports):
                    if hint.lower() in p.lower():
                        self._o.open_port(i)
                        print(f"Opened specific S-1 port via hint: {p}")
                        opened = True
                        break
                        
            # Auto-detect S-1
            if not opened:
                for i, p in enumerate(ports):
                    if any(k in p.upper() for k in ('S-1', 'S1', 'ROLAND', 'AIRA')):
                        self._o.open_port(i)
                        print(f"Auto-connected to Hardware S-1: {p}")
                        opened = True
                        break
                        
            if not opened:
                try:
                    self._o.open_virtual_port("S1-Gamma-Parallel")
                    print("Warning: Hardware unsupported. Opened virtual port 'S1-Gamma-Parallel'")
                except NotImplementedError:
                    print("Warning: Hardware unsupported. Virtual ports not supported on this OS. Running dry.")

    def _get_delta_ticks(self):
        now = time.time()
        delta_seconds = now - self.last_event_time
        ticks = int(delta_seconds * self.ticks_per_second)
        self.last_event_time = now
        return ticks

    def cc(self, command, value):
        """Sends a Control Change message."""
        val = max(0, min(127, int(value)))
        if self.is_offline:
            self.offline_track.append(mido.Message('control_change', channel=self.ch, control=command, value=val, time=self._get_delta_ticks()))
        elif self._o:
            self._o.send_message([0xB0 | self.ch, command, val])

    def on(self, note, velocity=75):
        """Sends a Note On message."""
        vel = max(1, min(127, int(velocity)))
        if self.is_offline:
            self.offline_track.append(mido.Message('note_on', channel=self.ch, note=note & 127, velocity=vel, time=self._get_delta_ticks()))
        elif self._o:
            self._o.send_message([0x90 | self.ch, note & 127, vel])

    def off(self, note):
        """Sends a Note Off message."""
        if self.is_offline:
            self.offline_track.append(mido.Message('note_off', channel=self.ch, note=note & 127, velocity=0, time=self._get_delta_ticks()))
        elif self._o:
            self._o.send_message([0x80 | self.ch, note & 127, 0])

    def panic(self):
        """All Notes Off."""
        if self.is_offline:
            self.offline_track.append(mido.Message('control_change', channel=self.ch, control=123, value=0, time=self._get_delta_ticks()))
            self.save_offline()
        elif self._o:
            self._o.send_message([0xB0 | self.ch, 123, 0])

    def save_offline(self):
        """Write the virtual buffer to disk."""
        if self.is_offline and self.offline_file:
            # End of Track
            self.offline_track.append(mido.MetaMessage('end_of_track', time=self._get_delta_ticks()))
            self.offline_file.save(self.output_filename)
            print(f"Saved Virtual MIDI Buffer to {self.output_filename}")
