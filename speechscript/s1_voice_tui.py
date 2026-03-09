"""
S-1 Voice Synthesis TUI
=======================
Five approaches to voice/speech synthesis with the Roland S-1.

  1  TTS Audio Path     — pyttsx3/espeak audio routed to S-1 USB audio out
  2  Formant Synthesis  — text → phoneme → CC stream (filter as vocal tract)
  3  Audio Transcription— mic → aubio pitch detection → MIDI note stream
  4  Spectral PWM       — mic → FFT → CC flood (bit-bash mode optional)
  5  Dual Stream        — local synth web API (audio) + S-1 MIDI simultaneously
  6  Library Audition   — execute and audition S-1 patch scripts from stories

Requirements:
    pip install textual python-rtmidi sounddevice numpy flask pyttsx3 aubio

Usage:
    python s1_voice_tui.py
    python s1_voice_tui.py --midi "S-1" --channel 3 --audio-device 1
"""

from __future__ import annotations

import argparse
import queue
import subprocess
import sys
import threading
import time
import wave
import io
import math
import os
from dataclasses import dataclass, field
from typing import Optional

import numpy as np

# ── Optional imports with graceful fallback ────────────────────────────────────
try:
    import rtmidi
    HAS_MIDI = True
except ImportError:
    HAS_MIDI = False

try:
    import sounddevice as sd
    HAS_AUDIO = True
except ImportError:
    HAS_AUDIO = False

try:
    import aubio
    HAS_AUBIO = True
except ImportError:
    HAS_AUBIO = False

try:
    import pyttsx3
    HAS_TTS = True
except ImportError:
    HAS_TTS = False

try:
    from flask import Flask, request, jsonify, Response
    HAS_FLASK = True
except ImportError:
    HAS_FLASK = False

from textual.app import App, ComposeResult
from textual.binding import Binding
from textual.containers import Container, Horizontal, Vertical, ScrollableContainer
from textual.reactive import reactive
from textual.widgets import (
    Button, Footer, Header, Input, Label, Log,
    RichLog, Select, Static, Switch, TabbedContent, TabPane,
)
from textual.color import Color

# ═══════════════════════════════════════════════════════════════════════════════
# S-1 CC MAP
# ═══════════════════════════════════════════════════════════════════════════════

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
    "lfo_mode":       79,  # 0=normal, >63=fast (audio rate)
}

CC_PRIORITY = [
    "filter_freq", "osc_square", "filter_res", "noise_level",
    "osc_saw", "osc_sub", "lfo_rate", "lfo_depth",
    "reverb_level", "env_attack", "env_release",
]

# ═══════════════════════════════════════════════════════════════════════════════
# PHONEME → PARAMETER MAP
# ═══════════════════════════════════════════════════════════════════════════════

# Each phoneme: (filter_freq, filter_res, noise_level, osc_square, duration_ms)
PHONEMES: dict[str, tuple] = {
    # Vowels  — filter_freq, res, noise, square, ms
    "ah":  (60, 50,   0,  80, 180),
    "ee":  (90, 70,   0,  60, 180),
    "oh":  (40, 60,   0,  90, 180),
    "oo":  (25, 55,   0, 100, 180),
    "ae":  (70, 55,   0,  70, 180),  # as in "cat"
    "ih":  (75, 60,   0,  65, 140),  # as in "bit"
    "uh":  (50, 45,   0,  85, 140),  # as in "but"
    # Consonants
    "ss":  (100, 20,  90,   0, 80),
    "sh":  (80,  10,  80,  10, 80),
    "mm":  (30,  30,   0,  60, 100),
    "nn":  (35,  35,   0,  55, 100),
    "ll":  (55,  40,   0,  70, 100),
    "rr":  (50,  45,   5,  65, 100),
    "ff":  (90,  10,  70,   0,  60),
    "vv":  (60,  30,  50,  40,  80),
    "pp":  (40,  10,  20,  50,  40),   # burst
    "tt":  (70,  10,  30,  50,  40),
    "kk":  (50,  10,  25,  60,  40),
    "hh":  (80,   5,  60,   0,  60),
    "ww":  (30,  50,   0,  80, 100),
    "yy":  (85,  60,   0,  60,  80),
    "_":   (50,  10,   0,   0,  80),   # silence/glottal
}

# Simple word → phoneme sequence mapping for demo text
WORD_PHONEMES: dict[str, list[str]] = {
    "hello":    ["hh", "ee", "ll", "oh"],
    "world":    ["ww", "rr", "ll", "uh", "ll", "dd"],
    "speak":    ["ss", "pp", "ee", "kk"],
    "synthesize": ["ss", "ih", "nn", "tt", "hh", "ee", "ss", "ah", "ih", "zz"],
    "filter":   ["ff", "ih", "ll", "tt", "rr"],
    "resonance":["rr", "ee", "zz", "oh", "nn", "ah", "nn", "ss"],
    "voltage":  ["vv", "oh", "ll", "tt", "ah", "jj"],
    "roland":   ["rr", "oh", "ll", "ah", "nn", "dd"],
    "wave":     ["ww", "ae", "vv"],
    "dark":     ["dd", "ah", "rr", "kk"],
    "cold":     ["kk", "oh", "ll", "dd"],
    "machine":  ["mm", "ah", "ss", "hh", "ee", "nn"],
    "voice":    ["vv", "oh", "ih", "ss"],
    "ocean":    ["oh", "ss", "hh", "ah", "nn"],
    "i":        ["ah", "ih"],
    "am":       ["ae", "mm"],
    "the":      ["dd", "uh"],
    "of":       ["oh", "vv"],
    "a":        ["ah"],
    "and":      ["ae", "nn", "dd"],
}

def text_to_phonemes(text: str) -> list[str]:
    """Very simple text → phoneme via lookup; unknown words get spelled phonetically."""
    phonemes = []
    for word in text.lower().split():
        word = word.strip(".,!?;:")
        if word in WORD_PHONEMES:
            phonemes.extend(WORD_PHONEMES[word])
        else:
            # Crude letter-by-letter fallback
            for ch in word:
                mapped = {
                    'a':'ah','e':'ee','i':'ih','o':'oh','u':'oo',
                    's':'ss','f':'ff','m':'mm','n':'nn','l':'ll',
                    'r':'rr','v':'vv','h':'hh','w':'ww','y':'yy',
                    'p':'pp','t':'tt','k':'kk','c':'kk','b':'pp',
                    'd':'tt','g':'kk','j':'yy','q':'kk','x':'kk',
                    'z':'ss',
                }.get(ch, '_')
                phonemes.append(mapped)
        phonemes.append('_')  # word gap
    return phonemes


# ═══════════════════════════════════════════════════════════════════════════════
# MIDI MANAGER (singleton, thread-safe)
# ═══════════════════════════════════════════════════════════════════════════════

class MIDIManager:
    """
    MIDI output singleton.
    Pattern mirrors harbour_bells_v3.py which is confirmed working:
    - MidiOut created immediately in __init__
    - Auto-detects S-1/Roland/AIRA ports
    - Falls back to virtual port — never silently drops messages
    """
    _instance: Optional[MIDIManager] = None

    def __init__(self):
        self._lock     = threading.Lock()
        self.channel   = 2          # 0-indexed; S-1 default ch3
        self.connected = False
        self.port_name = "–"
        self.port_log: list[str] = []   # captured during connect for TUI display
        self._o: Optional[object] = None

    @classmethod
    def get(cls) -> MIDIManager:
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def list_ports(self) -> list[str]:
        if not HAS_MIDI:
            return []
        return rtmidi.MidiOut().get_ports() or []

    def connect(self, name_hint: Optional[str] = None) -> bool:
        self.port_log = []
        if not HAS_MIDI:
            self.connected = False
            self.port_name = "[no rtmidi]"
            self.port_log.append("rtmidi not installed")
            return False

        o = rtmidi.MidiOut()
        ports = o.get_ports()
        self.port_log.append(f"Found {len(ports)} MIDI ports")
        for i, p in enumerate(ports):
            self.port_log.append(f"  [{i}] {p}")

        opened = False

        # 1 — match by hint
        if name_hint and not opened:
            for i, p in enumerate(ports):
                if name_hint.lower() in p.lower():
                    o.open_port(i)
                    self._o = o
                    self.port_name = p
                    opened = True
                    self.port_log.append(f"Opened by hint: {p}")
                    break

        # 2 — auto-detect S-1 / Roland / AIRA keywords
        if not opened:
            for i, p in enumerate(ports):
                if any(k in p.upper() for k in ('S-1', 'S1', 'ROLAND', 'AIRA')):
                    o.open_port(i)
                    self._o = o
                    self.port_name = p
                    opened = True
                    self.port_log.append(f"Auto-detected: {p}")
                    break

        # 3 — take first available port
        if not opened and ports:
            o.open_port(0)
            self._o = o
            self.port_name = ports[0]
            opened = True
            self.port_log.append(f"Opened first port: {ports[0]}")

        # 4 — virtual port fallback (always succeeds, no messages lost)
        if not opened:
            o.open_virtual_port("S1-VoiceTUI")
            self._o = o
            self.port_name = "virtual: S1-VoiceTUI"
            opened = True
            self.port_log.append("No hardware ports — opened virtual port")

        self.connected = opened
        return opened

    # ── Send helpers (never check for None — virtual port guarantees _o exists) ──

    def cc(self, param: str, value: int):
        if param in CC:
            self._raw_cc(CC[param], value)

    def _raw_cc(self, cc_num: int, value: int):
        value = max(0, min(127, int(value)))
        if self._o is None:
            return
        with self._lock:
            self._o.send_message([0xB0 | self.channel, cc_num, value])

    def note_on(self, note: int, velocity: int = 80):
        if self._o is None:
            return
        with self._lock:
            self._o.send_message([0x90 | self.channel, note & 127, max(1, min(127, velocity))])

    def note_off(self, note: int):
        if self._o is None:
            return
        with self._lock:
            self._o.send_message([0x80 | self.channel, note & 127, 0])

    def panic(self):
        if self._o is None:
            return
        with self._lock:
            self._o.send_message([0xB0 | self.channel, 123, 0])

    def patch(self, params: dict):
        for k, v in params.items():
            self.cc(k, v)


# ═══════════════════════════════════════════════════════════════════════════════
# APPROACH 1 — TTS AUDIO PATH
# ═══════════════════════════════════════════════════════════════════════════════

class TTSAudioApproach:
    """Route TTS speech to the S-1's USB audio output while setting a vocal patch via MIDI CC."""

    VOCAL_PATCH = {
        "filter_freq": 65, "filter_res": 45, "env_attack": 10,
        "env_decay": 60, "env_sustain": 80, "env_release": 50,
        "reverb_level": 55, "reverb_time": 70, "chorus_type": 32,
        "osc_square": 70, "osc_saw": 40, "noise_level": 15,
        "poly_mode": 64,  # poly
    }

    def __init__(self):
        self.running = False
        self.status = "idle"
        self.last_text = ""
        self._thread: Optional[threading.Thread] = None

    def speak(self, text: str, audio_device: Optional[int] = None):
        """Speak text, simultaneously push vocal patch to S-1."""
        if self.running:
            return
        self.last_text = text
        self._thread = threading.Thread(target=self._run, args=(text, audio_device), daemon=True)
        self._thread.start()

    def _run(self, text: str, audio_device: Optional[int]):
        self.running = True
        self.status = "patching S-1…"
        midi = MIDIManager.get()
        midi.patch(self.VOCAL_PATCH)
        time.sleep(0.05)

        self.status = "speaking…"
        if HAS_TTS:
            try:
                engine = pyttsx3.init()
                if audio_device is not None:
                    # pyttsx3 doesn't directly support device routing;
                    # use espeak subprocess for device routing instead
                    pass
                engine.setProperty('rate', 140)
                engine.setProperty('volume', 0.9)
                engine.say(text)
                engine.runAndWait()
                self.status = "done"
            except Exception as e:
                # Try espeak fallback
                self._espeak(text)
        else:
            self._espeak(text)
        self.running = False

    def _espeak(self, text: str):
        try:
            subprocess.run(["espeak", text], check=True, capture_output=True)
            self.status = "done (espeak)"
        except (FileNotFoundError, subprocess.CalledProcessError):
            self.status = "no TTS engine available"

    def stop(self):
        self.running = False
        self.status = "stopped"


# ═══════════════════════════════════════════════════════════════════════════════
# APPROACH 2 — FORMANT SYNTHESIS
# ═══════════════════════════════════════════════════════════════════════════════

class FormantApproach:
    """Text → phoneme → CC stream + MIDI notes. S-1 filter IS the vocal tract."""

    def __init__(self):
        self.running = False
        self.status = "idle"
        self.current_phoneme = "–"
        self.cc_snapshot: dict[str, int] = {}
        self._thread: Optional[threading.Thread] = None
        self._stop_event = threading.Event()

    def speak(self, text: str, pitch: int = 55, tempo: float = 1.0):
        if self.running:
            self.stop()
            time.sleep(0.1)
        self._stop_event.clear()
        self._thread = threading.Thread(
            target=self._run, args=(text, pitch, tempo), daemon=True
        )
        self._thread.start()

    def _run(self, text: str, pitch: int, tempo: float):
        self.running = True
        midi = MIDIManager.get()

        # Base patch
        midi.patch({
            "poly_mode": 0,       # mono
            "portamento": 25,
            "portamento_sw": 64,
            "env_attack": 0,
            "env_decay": 70,
            "env_sustain": 60,
            "env_release": 40,
            "osc_square": 80,
            "osc_saw": 20,
            "filter_follow": 80,
            "reverb_level": 40,
            "lfo_rate": 20,
            "lfo_depth": 8,
        })
        midi.note_on(pitch, 90)

        phonemes = text_to_phonemes(text)
        self.status = f"singing {len(phonemes)} phonemes"

        for ph in phonemes:
            if self._stop_event.is_set():
                break
            ph = ph if ph in PHONEMES else '_'
            freq, res, noise, square, dur_ms = PHONEMES[ph]
            self.current_phoneme = ph

            midi.cc("filter_freq",   freq)
            midi.cc("filter_res",    res)
            midi.cc("noise_level",   noise)
            midi.cc("osc_square",    square)
            self.cc_snapshot = {
                "filter_freq": freq, "filter_res": res,
                "noise_level": noise, "osc_square": square,
            }

            self._stop_event.wait(timeout=(dur_ms / 1000.0) / tempo)

        midi.note_off(pitch)
        midi.cc("noise_level", 0)
        self.current_phoneme = "–"
        self.status = "done"
        self.running = False

    def stop(self):
        self._stop_event.set()
        midi = MIDIManager.get()
        midi.panic()
        self.running = False
        self.status = "stopped"


# ═══════════════════════════════════════════════════════════════════════════════
# APPROACH 3 — AUDIO TRANSCRIPTION → MIDI
# ═══════════════════════════════════════════════════════════════════════════════

class AudioTranscriptionApproach:
    """Mic → aubio pitch detection → MIDI note + filter tracking."""

    def __init__(self):
        self.running = False
        self.status = "idle"
        self.current_note = 0
        self.current_freq = 0.0
        self.current_confidence = 0.0
        self._stop_event = threading.Event()
        self._thread: Optional[threading.Thread] = None
        self.audio_device: Optional[int] = None

    def start(self, audio_device: Optional[int] = None):
        if self.running:
            return
        if not HAS_AUBIO:
            self.status = "aubio not available"
            return
        if not HAS_AUDIO:
            self.status = "sounddevice not available"
            return
        self.audio_device = audio_device
        self._stop_event.clear()
        self._thread = threading.Thread(target=self._run, daemon=True)
        self._thread.start()

    def _run(self):
        self.running = True
        self.status = "listening…"
        midi = MIDIManager.get()

        midi.patch({
            "poly_mode": 0,  # mono — we're tracking monophonic
            "portamento": 15,
            "portamento_sw": 64,
            "filter_follow": 100,
            "env_attack": 0,
            "env_decay": 40,
            "env_sustain": 70,
            "env_release": 35,
            "osc_square": 100,
            "osc_saw": 30,
            "filter_res": 40,
            "reverb_level": 35,
        })

        sr = 44100
        hop = 512
        pitch_o = aubio.pitch("yin", 2048, hop, sr)
        pitch_o.set_unit("midi")
        pitch_o.set_silence(-40)
        onset_o = aubio.onset("default", 2048, hop, sr)

        prev_note = -1
        buf = queue.Queue(maxsize=20)

        def audio_cb(indata, frames, time_info, status):
            mono = indata[:, 0] if indata.ndim > 1 else indata.flatten()
            try:
                buf.put_nowait(mono.astype(np.float32).copy())
            except queue.Full:
                pass

        try:
            with sd.InputStream(
                device=self.audio_device, channels=1,
                samplerate=sr, blocksize=hop, callback=audio_cb
            ):
                while not self._stop_event.is_set():
                    try:
                        chunk = buf.get(timeout=0.1)
                    except queue.Empty:
                        continue

                    midi_note = int(round(pitch_o(chunk)[0]))
                    confidence = pitch_o.get_confidence()
                    is_onset = onset_o(chunk)[0]

                    self.current_freq = float(pitch_o(chunk)[0])
                    self.current_confidence = float(confidence)

                    if confidence > 0.5 and 24 <= midi_note <= 96:
                        self.current_note = midi_note
                        # Filter tracks pitch: map note 24-96 → CC 0-127
                        filter_cc = int(np.interp(midi_note, [24, 96], [20, 110]))
                        midi.cc("filter_freq", filter_cc)

                        if midi_note != prev_note:
                            if prev_note >= 0:
                                midi.note_off(prev_note)
                            midi.note_on(midi_note, 80)
                            prev_note = midi_note
                            self.status = f"note {midi_note} ({midi_note:.0f})"
                    elif confidence < 0.2 and prev_note >= 0:
                        midi.note_off(prev_note)
                        prev_note = -1
                        self.current_note = 0

        except Exception as e:
            self.status = f"error: {e}"

        if prev_note >= 0:
            midi.note_off(prev_note)
        self.running = False
        self.status = "stopped"

    def stop(self):
        self._stop_event.set()
        MIDIManager.get().panic()
        self.running = False


# ═══════════════════════════════════════════════════════════════════════════════
# APPROACH 4 — SPECTRAL PWM
# ═══════════════════════════════════════════════════════════════════════════════

class SpectralPWMApproach:
    """Mic → FFT → CC flood. PWM bit-bashing for sub-7-bit resolution."""

    SR         = 44100
    FFT_WIN    = 1024
    HOP        = 512
    PWM_PERIOD = 0.020
    PWM_MIN    = 0.05
    PWM_MAX    = 0.95
    MAX_CC_HZ  = 200

    def __init__(self):
        self.running = False
        self.pwm_mode = False
        self.status = "idle"
        self.cc_snapshot: dict[str, float] = {k: 0.0 for k in CC_PRIORITY}
        self._stop_event = threading.Event()
        self._targets: dict[str, float] = {k: 0.0 for k in CC_PRIORITY}
        self._lock = threading.Lock()
        self.audio_device: Optional[int] = None

    def start(self, audio_device: Optional[int] = None, pwm: bool = False):
        if self.running:
            return
        if not HAS_AUDIO:
            self.status = "sounddevice not available"
            return
        self.audio_device = audio_device
        self.pwm_mode = pwm
        self._stop_event.clear()
        threading.Thread(target=self._analysis_loop, daemon=True).start()
        if pwm:
            threading.Thread(target=self._pwm_loop, daemon=True).start()
        self.running = True
        self.status = f"running ({'PWM' if pwm else 'direct CC'})"

    def _analyse(self, samples: np.ndarray) -> dict:
        if np.max(np.abs(samples)) < 1e-6:
            return {k: 0.0 for k in CC_PRIORITY}
        eps = 1e-10
        windowed = samples * np.hanning(len(samples))
        spectrum = np.abs(np.fft.rfft(windowed))
        freqs    = np.fft.rfftfreq(len(samples), d=1.0 / self.SR)

        rms          = float(np.sqrt(np.mean(samples**2)))
        rms_n        = float(np.clip(rms / 0.5, 0, 1))
        centroid     = float(np.sum(freqs * spectrum) / (np.sum(spectrum) + eps))
        centroid_n   = float(np.clip(centroid / (self.SR / 2), 0, 1))
        dom_freq     = float(freqs[np.argmax(spectrum)])
        dom_n        = float(np.clip(dom_freq / 8000.0, 0, 1))

        low_e  = float(np.sum(spectrum[freqs < 300]))
        mid_e  = float(np.sum(spectrum[(freqs >= 300) & (freqs < 3000)]))
        high_e = float(np.sum(spectrum[(freqs >= 3000) & (freqs < 12000)]))
        tot    = low_e + mid_e + high_e + eps

        geo   = float(np.exp(np.mean(np.log(spectrum + eps))))
        flat  = float(np.clip(geo / (np.mean(spectrum) + eps), 0, 1))
        flux  = float(np.clip(np.std(spectrum[freqs >= 3000]) / (np.mean(spectrum) + eps) / 10, 0, 1))

        return {
            "filter_freq":  dom_n,
            "osc_square":   (low_e / tot) * rms_n,
            "filter_res":   centroid_n * 0.7,
            "noise_level":  flat * (high_e / tot),
            "osc_saw":      (mid_e / tot) * rms_n,
            "osc_sub":      (low_e / tot) * (1 - centroid_n),
            "lfo_rate":     flux,
            "lfo_depth":    flux * 0.5,
            "reverb_level": (1 - flat) * 0.6,
            "env_attack":   1 - flux,
            "env_release":  1 - flux * 0.5,
        }

    def _analysis_loop(self):
        buf = queue.Queue(maxsize=8)
        buffer = np.zeros(self.FFT_WIN)

        def cb(indata, frames, ti, status):
            mono = indata[:, 0] if indata.ndim > 1 else indata.flatten()
            try:
                buf.put_nowait(mono.astype(np.float32).copy())
            except queue.Full:
                pass

        midi = MIDIManager.get()
        try:
            with sd.InputStream(
                device=self.audio_device, channels=1,
                samplerate=self.SR, blocksize=self.HOP, callback=cb
            ):
                while not self._stop_event.is_set():
                    try:
                        chunk = buf.get(timeout=0.1)
                    except queue.Empty:
                        continue
                    cl = min(len(chunk), self.FFT_WIN)
                    buffer = np.roll(buffer, -cl)
                    buffer[-cl:] = chunk[:cl]
                    features = self._analyse(buffer)
                    with self._lock:
                        self._targets.update(features)
                        self.cc_snapshot = dict(features)
                    if not self.pwm_mode:
                        for param, val in features.items():
                            midi._raw_cc(CC[param], int(val * 127))
        except Exception as e:
            self.status = f"error: {e}"
        self.running = False
        self.status = "stopped"

    def _pwm_loop(self):
        midi = MIDIManager.get()
        period = self.PWM_PERIOD
        n = len(CC_PRIORITY)
        while not self._stop_event.is_set():
            with self._lock:
                snap = dict(self._targets)
            for param in CC_PRIORITY:
                if self._stop_event.is_set():
                    break
                duty = float(np.clip(snap.get(param, 0), self.PWM_MIN, self.PWM_MAX))
                cc_n = CC[param]
                midi._raw_cc(cc_n, 127)
                time.sleep(period * duty / n)
                midi._raw_cc(cc_n, 0)
                time.sleep(period * (1 - duty) / n)
            elapsed_target = (n * 2) / self.MAX_CC_HZ
            time.sleep(max(0, elapsed_target - period))

    def stop(self):
        self._stop_event.set()
        for cc_n in [CC[p] for p in CC_PRIORITY]:
            MIDIManager.get()._raw_cc(cc_n, 0)
        self.running = False
        self.status = "stopped"


# ═══════════════════════════════════════════════════════════════════════════════
# APPROACH 5 — DUAL STREAM: LOCAL SYNTH WEB API + S-1 MIDI SIMULTANEOUSLY
# ═══════════════════════════════════════════════════════════════════════════════

def _sine_wave(freq: float, duration: float, sr: int = 44100,
               amplitude: float = 0.4) -> np.ndarray:
    """Generate a simple sine + harmonic approximating a vocal tone."""
    t = np.linspace(0, duration, int(sr * duration), endpoint=False)
    wave = (
        amplitude * 0.6 * np.sin(2 * np.pi * freq * t)
        + amplitude * 0.3 * np.sin(2 * np.pi * freq * 2 * t)
        + amplitude * 0.1 * np.sin(2 * np.pi * freq * 3 * t)
    )
    # Envelope: fast attack, medium release
    env_len = len(wave)
    atk = int(env_len * 0.02)
    rel = int(env_len * 0.15)
    env = np.ones(env_len)
    if atk > 0:
        env[:atk] = np.linspace(0, 1, atk)
    if rel > 0:
        env[-rel:] = np.linspace(1, 0, rel)
    return (wave * env).astype(np.float32)


def _phoneme_audio(ph: str, pitch_hz: float = 220, sr: int = 44100) -> np.ndarray:
    """Render a phoneme as audio using additive synthesis."""
    if ph not in PHONEMES:
        ph = '_'
    freq, res, noise_lvl, _, dur_ms = PHONEMES[ph]
    duration = dur_ms / 1000.0

    # Tonal component
    tone = _sine_wave(pitch_hz, duration, sr, amplitude=0.3)

    # Resonant formant — modulate with filter-frequency-derived overtone
    formant_hz = 200 + (freq / 127.0) * 2000
    formant = _sine_wave(formant_hz, duration, sr, amplitude=0.2 * (res / 127.0))

    # Noise component
    noise = (np.random.randn(len(tone)).astype(np.float32)
             * 0.3 * (noise_lvl / 127.0))

    combined = tone + formant + noise
    peak = np.max(np.abs(combined))
    if peak > 0:
        combined /= peak
    return (combined * 0.7).astype(np.float32)


def _build_flask_server() -> Flask:
    """Build the local synthesiser web API."""
    app = Flask(__name__)

    @app.route('/status', methods=['GET'])
    def status():
        return jsonify({"status": "ok", "engine": "S-1 Dual Stream Local Synth"})

    @app.route('/synthesize', methods=['POST'])
    def synthesize():
        """
        POST { text, pitch_hz, play }
        Returns audio/wav if play=false, else plays locally and returns {ok}.
        """
        data = request.get_json(force=True) or {}
        text      = data.get('text', '')
        pitch_hz  = float(data.get('pitch_hz', 220.0))
        do_play   = bool(data.get('play', True))

        phonemes  = text_to_phonemes(text)
        sr        = 44100
        segments  = [_phoneme_audio(ph, pitch_hz, sr) for ph in phonemes]
        audio     = np.concatenate(segments) if segments else np.zeros(sr // 10)

        if do_play and HAS_AUDIO:
            try:
                sd.play(audio, samplerate=sr)
            except Exception:
                pass
            return jsonify({"ok": True, "phonemes": phonemes, "samples": len(audio)})
        else:
            # Return raw WAV
            buf = io.BytesIO()
            with wave.open(buf, 'wb') as wf:
                wf.setnchannels(1)
                wf.setsampwidth(2)
                wf.setframerate(sr)
                wf.writeframes((audio * 32767).astype(np.int16).tobytes())
            buf.seek(0)
            return Response(buf.read(), mimetype='audio/wav')

    @app.route('/phoneme', methods=['POST'])
    def phoneme_single():
        """
        POST { phoneme, pitch_hz }
        Play a single phoneme immediately, return CC parameters.
        """
        data    = request.get_json(force=True) or {}
        ph      = data.get('phoneme', 'ah')
        pitch   = float(data.get('pitch_hz', 220.0))
        ph_data = PHONEMES.get(ph, PHONEMES['_'])
        audio   = _phoneme_audio(ph, pitch)
        if HAS_AUDIO:
            try:
                sd.play(audio, samplerate=44100)
            except Exception:
                pass
        return jsonify({
            "phoneme": ph,
            "filter_freq": ph_data[0],
            "filter_res":  ph_data[1],
            "noise_level": ph_data[2],
            "osc_square":  ph_data[3],
            "duration_ms": ph_data[4],
        })

    return app


class DualStreamApproach:
    """
    Starts a local Flask synth server.
    For each phoneme: POST → server plays audio AND we send MIDI CC to S-1.
    Both streams are simultaneous — audio from local synth, synthesis from S-1.
    """

    SERVER_PORT = 5174

    def __init__(self):
        self.running = False
        self.server_running = False
        self.status = "idle"
        self.current_phoneme = "–"
        self.server_url = f"http://127.0.0.1:{self.SERVER_PORT}"
        self._stop_event = threading.Event()
        self._server_thread: Optional[threading.Thread] = None
        self._speak_thread: Optional[threading.Thread] = None
        self._flask_app: Optional[Flask] = None

    def start_server(self):
        if self.server_running or not HAS_FLASK:
            return
        self._flask_app = _build_flask_server()
        self._server_thread = threading.Thread(
            target=lambda: self._flask_app.run(
                host='127.0.0.1', port=self.SERVER_PORT,
                debug=False, use_reloader=False
            ),
            daemon=True
        )
        self._server_thread.start()
        time.sleep(0.8)  # let Flask start
        self.server_running = True
        self.status = f"server up at :{self.SERVER_PORT}"

    def speak(self, text: str, pitch_hz: float = 220.0, tempo: float = 1.0):
        """Simultaneously play audio via local synth API + send CCs to S-1."""
        if not self.server_running:
            self.start_server()
        if self.running:
            self.stop()
            time.sleep(0.1)
        self._stop_event.clear()
        self._speak_thread = threading.Thread(
            target=self._run, args=(text, pitch_hz, tempo), daemon=True
        )
        self._speak_thread.start()

    def _run(self, text: str, pitch_hz: float, tempo: float):
        self.running = True
        import urllib.request
        import json as _json

        midi = MIDIManager.get()
        midi.patch({
            "poly_mode": 0, "portamento": 20, "portamento_sw": 64,
            "env_attack": 0, "env_decay": 65, "env_sustain": 65,
            "env_release": 45, "osc_square": 85, "osc_saw": 25,
            "filter_follow": 85, "reverb_level": 45, "lfo_rate": 18,
        })

        phonemes = text_to_phonemes(text)
        # Map pitch_hz → MIDI note
        midi_note = int(round(69 + 12 * math.log2(pitch_hz / 440.0)))
        midi_note = max(24, min(96, midi_note))
        midi.note_on(midi_note, 85)

        self.status = f"dual-streaming {len(phonemes)} phonemes"

        for ph in phonemes:
            if self._stop_event.is_set():
                break
            self.current_phoneme = ph
            ph_data = PHONEMES.get(ph, PHONEMES['_'])
            dur_ms = ph_data[4]

            # ── Thread 1: POST to local synth API (audio render) ──────────
            def _post(ph=ph, pitch_hz=pitch_hz):
                try:
                    payload = _json.dumps({"phoneme": ph, "pitch_hz": pitch_hz}).encode()
                    req = urllib.request.Request(
                        f"{self.server_url}/phoneme",
                        data=payload,
                        headers={"Content-Type": "application/json"},
                        method="POST"
                    )
                    urllib.request.urlopen(req, timeout=0.5)
                except Exception:
                    pass

            audio_thread = threading.Thread(target=_post, daemon=True)
            audio_thread.start()

            # ── Thread 2: Send MIDI CCs to S-1 immediately ───────────────
            midi.cc("filter_freq",  ph_data[0])
            midi.cc("filter_res",   ph_data[1])
            midi.cc("noise_level",  ph_data[2])
            midi.cc("osc_square",   ph_data[3])

            self._stop_event.wait(timeout=(dur_ms / 1000.0) / tempo)

        midi.note_off(midi_note)
        midi.cc("noise_level", 0)
        self.current_phoneme = "–"
        self.status = "done"
        self.running = False

    def stop(self):
        self._stop_event.set()
        MIDIManager.get().panic()
        self.running = False
        self.status = "stopped"

    def api_url(self) -> str:
        return self.server_url


# ═══════════════════════════════════════════════════════════════════════════════
# TEXTUAL TUI
# ═══════════════════════════════════════════════════════════════════════════════

MIDI_CSS = """
Screen {
    background: #0d0d1a;
}
Header {
    background: #1a1a3a;
    color: #7af;
}
Footer {
    background: #1a1a3a;
}

/* ── Shared layout ─────── */
.panel {
    border: round #2a2a5a;
    padding: 1 2;
    margin: 0 0 1 0;
    background: #111128;
}
.panel-title {
    color: #7af;
    text-style: bold;
    margin-bottom: 1;
}
.label {
    color: #aaa;
}
.value {
    color: #7f7;
    text-style: bold;
}
.warn {
    color: #fa7;
}
.error {
    color: #f55;
}

/* ── Buttons ─────────────── */
Button {
    margin: 0 1 0 0;
    min-width: 12;
}
Button.go {
    background: #1a4a1a;
    color: #7f7;
    border: tall #2a7a2a;
}
Button.go:hover {
    background: #2a6a2a;
}
Button.stop {
    background: #4a1a1a;
    color: #f77;
    border: tall #7a2a2a;
}
Button.stop:hover {
    background: #6a2a2a;
}
Button.neutral {
    background: #1a2a4a;
    color: #7af;
    border: tall #2a4a7a;
}

/* ── Inputs ──────────────── */
Input {
    background: #0a0a1f;
    border: round #2a2a5a;
    color: #eee;
}

/* ── CC bar ──────────────── */
.cc-bar-row {
    height: 1;
    margin-bottom: 0;
}
.cc-name {
    width: 16;
    color: #88a;
}
.cc-bar {
    width: 1fr;
    color: #4af;
}
.cc-val {
    width: 5;
    color: #7f7;
    text-align: right;
}

/* ── Log ─────────────────── */
RichLog {
    background: #050510;
    border: round #1a1a3a;
    height: 10;
}

/* ── Tab titles ──────────── */
TabbedContent > TabPane {
    padding: 1 2;
}
"""


def _cc_bar(val: float, width: int = 30) -> str:
    """Render a CC value (0.0–1.0) as a bar string."""
    filled = int(val * width)
    return "█" * filled + "░" * (width - filled)


class MIDIStatusBar(Static):
    def compose(self) -> ComposeResult:
        yield Label("", id="midi-status-label")

    def update_status(self):
        midi = MIDIManager.get()
        if midi.connected:
            self.query_one("#midi-status-label").update(
                f"[green]●[/] MIDI: [bold]{midi.port_name}[/]  ch {midi.channel+1}"
            )
        else:
            self.query_one("#midi-status-label").update("[red]●[/] MIDI: not connected")


class Approach1Panel(Static):
    def compose(self) -> ComposeResult:
        yield Label("TTS Audio Path", classes="panel-title")
        yield Label("Route TTS speech to S-1 USB audio output while setting vocal patch via MIDI CC.", classes="label")
        yield Label("")
        yield Input(value="hello i am the voice of roland", id="tts-text", placeholder="Text to speak…")
        yield Label("")
        yield Horizontal(
            Button("▶  Speak", id="tts-speak", classes="go"),
            Button("■  Stop",  id="tts-stop",  classes="stop"),
        )
        yield Label("")
        yield Label("Status: idle", id="tts-status", classes="label")
        yield Label("")
        yield Label("[dim]Sends VOCAL_PATCH CCs to S-1, then speaks via pyttsx3 / espeak[/]", markup=True, classes="label")

    def on_button_pressed(self, event: Button.Pressed) -> None:
        approach = self.app._approach1
        if event.button.id == "tts-speak":
            text = self.query_one("#tts-text", Input).value.strip()
            if text:
                approach.speak(text)
                self.app.log_msg(f"[A1] Speaking: {text!r}")
        elif event.button.id == "tts-stop":
            approach.stop()

    def refresh_status(self, approach: TTSAudioApproach):
        self.query_one("#tts-status").update(f"Status: {approach.status}")


class Approach2Panel(Static):
    def compose(self) -> ComposeResult:
        yield Label("Formant Synthesis", classes="panel-title")
        yield Label("Text → phonemes → CC stream. The S-1 filter IS the vocal tract.", classes="label")
        yield Label("")
        yield Input(value="dark cold machine voice", id="form-text", placeholder="Text to sing…")
        yield Horizontal(
            Label("Pitch (MIDI): ", classes="label"),
            Input(value="48", id="form-pitch", placeholder="24-96", restrict=r"\d+"),
            Label("  Tempo: ", classes="label"),
            Input(value="1.0", id="form-tempo", placeholder="0.5–3.0", restrict=r"[\d.]+"),
        )
        yield Label("")
        yield Horizontal(
            Button("▶  Sing",  id="form-sing",  classes="go"),
            Button("■  Stop",  id="form-stop",  classes="stop"),
        )
        yield Label("")
        yield Label("Status: idle",     id="form-status",  classes="label")
        yield Label("Phoneme: –",       id="form-phoneme", classes="value")
        yield Label("")
        yield Label("Live CCs:", classes="label")
        for cc_name in ("filter_freq", "filter_res", "noise_level", "osc_square"):
            yield Horizontal(
                Label(cc_name, classes="cc-name"),
                Label("░" * 30, id=f"form-bar-{cc_name}", classes="cc-bar"),
                Label("  0",    id=f"form-val-{cc_name}", classes="cc-val"),
                classes="cc-bar-row",
            )

    def on_button_pressed(self, event: Button.Pressed) -> None:
        approach = self.app._approach2
        if event.button.id == "form-sing":
            text  = self.query_one("#form-text", Input).value.strip()
            try:
                pitch = int(self.query_one("#form-pitch", Input).value)
                tempo = float(self.query_one("#form-tempo", Input).value)
            except ValueError:
                pitch, tempo = 48, 1.0
            if text:
                approach.speak(text, pitch=pitch, tempo=tempo)
                self.app.log_msg(f"[A2] Formant sing: {text!r} pitch={pitch}")
        elif event.button.id == "form-stop":
            approach.stop()

    def refresh_status(self, approach: FormantApproach):
        self.query_one("#form-status").update(f"Status: {approach.status}")
        self.query_one("#form-phoneme").update(f"Phoneme: {approach.current_phoneme}")
        for cc_name, val in approach.cc_snapshot.items():
            nval = val / 127.0
            try:
                self.query_one(f"#form-bar-{cc_name}").update(_cc_bar(nval))
                self.query_one(f"#form-val-{cc_name}").update(f"{val:3d}")
            except Exception:
                pass


class Approach3Panel(Static):
    def compose(self) -> ComposeResult:
        yield Label("Audio Transcription → MIDI", classes="panel-title")
        yield Label("Mic → aubio pitch detection → MIDI note + filter tracking.", classes="label")
        yield Label("")
        yield Horizontal(
            Label("Audio device idx: ", classes="label"),
            Input(value="", id="trans-device", placeholder="blank=default", restrict=r"\d*"),
        )
        yield Label("")
        yield Horizontal(
            Button("▶  Start",   id="trans-start",  classes="go"),
            Button("■  Stop",    id="trans-stop",   classes="stop"),
        )
        yield Label("")
        yield Label("Status: idle",          id="trans-status",     classes="label")
        yield Label("Note: –",               id="trans-note",       classes="value")
        yield Label("Freq: – Hz",            id="trans-freq",       classes="label")
        yield Label("Confidence: –",         id="trans-conf",       classes="label")
        if not HAS_AUBIO:
            yield Label("[yellow]⚠ aubio not available — install: pip install aubio[/]",
                        markup=True, classes="warn")

    def on_button_pressed(self, event: Button.Pressed) -> None:
        approach = self.app._approach3
        if event.button.id == "trans-start":
            dev_str = self.query_one("#trans-device", Input).value.strip()
            dev = int(dev_str) if dev_str.isdigit() else None
            approach.start(audio_device=dev)
            self.app.log_msg(f"[A3] Audio transcription started (device={dev})")
        elif event.button.id == "trans-stop":
            approach.stop()
            self.app.log_msg("[A3] Stopped")

    def refresh_status(self, approach: AudioTranscriptionApproach):
        self.query_one("#trans-status").update(f"Status: {approach.status}")
        self.query_one("#trans-note").update(f"Note: {approach.current_note or '–'}")
        self.query_one("#trans-freq").update(f"Freq: {approach.current_freq:.1f} Hz")
        conf = approach.current_confidence
        bar  = "█" * int(conf * 20) + "░" * (20 - int(conf * 20))
        self.query_one("#trans-conf").update(f"Confidence: {bar} {conf:.2f}")


class Approach4Panel(Static):
    def compose(self) -> ComposeResult:
        yield Label("Spectral PWM (Bit-Bashing)", classes="panel-title")
        yield Label("Mic → FFT → CC flood. PWM mode drives S-1 like a 1-bit DAC.", classes="label")
        yield Label("")
        yield Horizontal(
            Label("Audio device idx: ", classes="label"),
            Input(value="", id="spec-device", placeholder="blank=default", restrict=r"\d*"),
            Label("  PWM mode: ", classes="label"),
            Switch(id="spec-pwm", value=False),
        )
        yield Label("")
        yield Horizontal(
            Button("▶  Start",  id="spec-start",  classes="go"),
            Button("■  Stop",   id="spec-stop",   classes="stop"),
        )
        yield Label("")
        yield Label("Status: idle", id="spec-status", classes="label")
        yield Label("")
        yield Label("Live parameter values:", classes="label")
        for cc_name in CC_PRIORITY[:8]:
            yield Horizontal(
                Label(cc_name[:14].ljust(14), classes="cc-name"),
                Label("░" * 28,  id=f"spec-bar-{cc_name}",  classes="cc-bar"),
                Label("  0.00", id=f"spec-val-{cc_name}",  classes="cc-val"),
                classes="cc-bar-row",
            )

    def on_button_pressed(self, event: Button.Pressed) -> None:
        approach = self.app._approach4
        if event.button.id == "spec-start":
            dev_str = self.query_one("#spec-device", Input).value.strip()
            dev = int(dev_str) if dev_str.isdigit() else None
            pwm = self.query_one("#spec-pwm", Switch).value
            approach.start(audio_device=dev, pwm=pwm)
            self.app.log_msg(f"[A4] Spectral PWM started (pwm={pwm}, device={dev})")
        elif event.button.id == "spec-stop":
            approach.stop()
            self.app.log_msg("[A4] Stopped")

    def refresh_status(self, approach: SpectralPWMApproach):
        self.query_one("#spec-status").update(f"Status: {approach.status}")
        for cc_name, val in approach.cc_snapshot.items():
            try:
                self.query_one(f"#spec-bar-{cc_name}").update(_cc_bar(float(val), 28))
                self.query_one(f"#spec-val-{cc_name}").update(f"{float(val):.2f}")
            except Exception:
                pass


class Approach5Panel(Static):
    def compose(self) -> ComposeResult:
        yield Label("Dual Stream: Local Synth API + S-1 MIDI", classes="panel-title")
        yield Label(
            "Flask server renders phoneme audio. Same phoneme stream → S-1 MIDI simultaneously.",
            classes="label"
        )
        yield Label("")
        yield Horizontal(
            Button("⚙  Start Server", id="dual-server", classes="neutral"),
            Label("", id="dual-server-status", classes="label"),
        )
        yield Label("")
        yield Input(value="voice of the machine speaks", id="dual-text", placeholder="Text for dual stream…")
        yield Horizontal(
            Label("Pitch Hz: ", classes="label"),
            Input(value="220", id="dual-pitch", placeholder="Hz", restrict=r"[\d.]+"),
            Label("  Tempo: ", classes="label"),
            Input(value="1.0", id="dual-tempo", placeholder="0.5–3.0", restrict=r"[\d.]+"),
        )
        yield Label("")
        yield Horizontal(
            Button("▶  Stream",  id="dual-speak",  classes="go"),
            Button("■  Stop",    id="dual-stop",   classes="stop"),
        )
        yield Label("")
        yield Label("Status: idle",     id="dual-status",   classes="label")
        yield Label("Phoneme: –",       id="dual-phoneme",  classes="value")
        yield Label("")
        yield Label("API endpoints (once server is up):", classes="label")
        yield Label(f"  GET  /status", classes="label")
        yield Label(f"  POST /synthesize  {{text, pitch_hz, play}}", classes="label")
        yield Label(f"  POST /phoneme     {{phoneme, pitch_hz}}", classes="label")
        if not HAS_FLASK:
            yield Label("[yellow]⚠ flask not available — install: pip install flask[/]",
                        markup=True, classes="warn")

    def on_button_pressed(self, event: Button.Pressed) -> None:
        approach = self.app._approach5
        if event.button.id == "dual-server":
            if not approach.server_running:
                approach.start_server()
                self.app.log_msg(f"[A5] Server starting on :{DualStreamApproach.SERVER_PORT}")
        elif event.button.id == "dual-speak":
            text = self.query_one("#dual-text", Input).value.strip()
            try:
                pitch = float(self.query_one("#dual-pitch", Input).value)
                tempo = float(self.query_one("#dual-tempo", Input).value)
            except ValueError:
                pitch, tempo = 220.0, 1.0
            if text:
                approach.speak(text, pitch_hz=pitch, tempo=tempo)
                self.app.log_msg(f"[A5] Dual stream: {text!r} pitch={pitch:.0f}Hz")
        elif event.button.id == "dual-stop":
            approach.stop()

    def refresh_status(self, approach: DualStreamApproach):
        srv = "up" if approach.server_running else "down"
        self.query_one("#dual-server-status").update(
            f"  [{'green' if approach.server_running else 'red'}]● server {srv}[/]  "
            f"{approach.server_url}",
        )
        self.query_one("#dual-status").update(f"Status: {approach.status}")
        self.query_one("#dual-phoneme").update(f"Phoneme: {approach.current_phoneme}")


class LibraryAuditionApproach:
    """Approach 6: Scans and executes generated S-1 Python patches."""
    def __init__(self):
        self.status = "idle"
        self._process: Optional[subprocess.Popen] = None
        self.available_scripts = []
        self.script_taxonomies = {}
        self._scan_scripts()

    def _scan_scripts(self):
        base_dir = os.path.dirname(os.path.abspath(__file__))
        stories_dir = os.path.join(os.path.dirname(base_dir), "server", "kernel", "Stories")
        self.available_scripts = []
        self.script_taxonomies = {}
        if os.path.exists(stories_dir):
            for file in os.listdir(stories_dir):
                if file.endswith(".py") and file != "__init__.py":
                    path = os.path.join(stories_dir, file)
                    self.available_scripts.append(path)
                    
                    # Parse Archivist taxonomy
                    tax = ""
                    try:
                        with open(path, "r", encoding="utf-8") as f:
                            for _ in range(20):
                                line = f.readline()
                                if not line: break
                                if "[" in line and "]" in line and "Origin:" in line:
                                    tax = line.strip()
                                    break
                    except Exception:
                        pass
                    self.script_taxonomies[path] = tax
        self.available_scripts.sort()

    def play(self, script_path: str, midi_port_name: str):
        self.stop()
        if not isinstance(script_path, str) or not script_path or not os.path.exists(script_path):
            self.status = "error: file not found"
            return
            
        self.status = f"playing {os.path.basename(script_path)}"
        # Execute the script as a separate process to prevent blocking the TUI
        try:
            cmd = [sys.executable, script_path]
            # If the script accepts a midi port arg, we'd pass it here. 
            # For now, we assume s1_midi.py or similar handles connection via default/config.
            self._process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        except Exception as e:
            self.status = f"error: {str(e)}"

    def stop(self):
        if self._process:
            self.status = "stopping..."
            self._process.terminate()
            try:
                self._process.wait(timeout=1.0)
            except subprocess.TimeoutExpired:
                self._process.kill()
            self._process = None
            
        self.status = "idle"
        # Always send panic when stopping an audition
        MIDIManager.get().panic()


class Approach6Panel(Static):
    def compose(self) -> ComposeResult:
        yield Label("Library Audition", classes="panel-title")
        yield Label("Execute and audition S-1 patch scripts from the stories library.", classes="label")
        yield Label("")
        
        approach = self.app._approach6
        options = [(os.path.basename(p), p) for p in approach.available_scripts]
        if not options:
            options = [("No scripts found in server/kernel/Stories", "")]
            
        yield Horizontal(
            Label("Patch: ", classes="label"),
            Select(options, id="audition-select", prompt="Select patch..."),
            Button("↻ Refresh", id="audition-refresh", classes="neutral")
        )
        yield Label("", id="audition-taxonomy", classes="label")
        yield Label("")
        yield Horizontal(
            Button("▶  Play",  id="audition-play",  classes="go"),
            Button("■  Stop",  id="audition-stop",  classes="stop"),
        )
        yield Label("")
        yield Label("Status: idle", id="audition-status", classes="label")

    def on_button_pressed(self, event: Button.Pressed) -> None:
        approach = self.app._approach6
        if event.button.id == "audition-refresh":
            approach._scan_scripts()
            sel = self.query_one("#audition-select", Select)
            options = [(os.path.basename(p), p) for p in approach.available_scripts]
            sel.set_options(options if options else [("No scripts found", "")])
            self.app.log_msg("[A6] Refreshed script list")
        elif event.button.id == "audition-play":
            script_path = self.query_one("#audition-select", Select).value
            if isinstance(script_path, str) and script_path != "":
                # Pass the connected MIDI port name if possible
                midi_port = MIDIManager.get().port_name if MIDIManager.get().connected else ""
                approach.play(script_path, midi_port)
                self.app.log_msg(f"[A6] Auditioning: {os.path.basename(script_path)}")
        elif event.button.id == "audition-stop":
            approach.stop()
            self.app.log_msg("[A6] Stopped audition")

    def refresh_status(self, approach: LibraryAuditionApproach):
        self.query_one("#audition-status").update(f"Status: {approach.status}")
        
        # Check taxonomy of current selection
        try:
            sel = self.query_one("#audition-select", Select)
            path = sel.value
            tax = approach.script_taxonomies.get(path, "") if isinstance(path, str) else ""
            self.query_one("#audition-taxonomy").update(f"[dim]{tax}[/]" if tax else "")
        except Exception:
            pass
        
        # Check if process ended naturally
        if approach._process and approach._process.poll() is not None:
            approach.status = "finished"
            approach._process = None
            MIDIManager.get().panic()


class S1VoiceTUI(App):
    CSS = MIDI_CSS
    BINDINGS = [
        Binding("q",      "quit",   "Quit"),
        Binding("p",      "panic",  "MIDI Panic"),
        Binding("ctrl+c", "quit",   "Quit", show=False),
    ]

    def __init__(self, midi_hint: Optional[str], midi_channel: int,
                 audio_device: Optional[int]):
        super().__init__()
        self._midi_hint    = midi_hint
        self._midi_channel = midi_channel
        self._audio_device = audio_device

        self._approach1 = TTSAudioApproach()
        self._approach2 = FormantApproach()
        self._approach3 = AudioTranscriptionApproach()
        self._approach4 = SpectralPWMApproach()
        self._approach5 = DualStreamApproach()
        self._approach6 = LibraryAuditionApproach()

    def compose(self) -> ComposeResult:
        yield Header(show_clock=True)
        with Container():
            with Horizontal(classes="panel"):
                yield Label("● MIDI: connecting…", id="midi-bar")
                yield Label("   ", id="midi-spacer")
                yield Label("", id="audio-devices-hint", classes="label")
            with TabbedContent():
                with TabPane("1 · TTS Audio",      id="tab1"):
                    yield ScrollableContainer(Approach1Panel(id="a1"))
                with TabPane("2 · Formant",        id="tab2"):
                    yield ScrollableContainer(Approach2Panel(id="a2"))
                with TabPane("3 · Transcription",  id="tab3"):
                    yield ScrollableContainer(Approach3Panel(id="a3"))
                with TabPane("4 · Spectral PWM",   id="tab4"):
                    yield ScrollableContainer(Approach4Panel(id="a4"))
                with TabPane("5 · Dual Stream",    id="tab5"):
                    yield ScrollableContainer(Approach5Panel(id="a5"))
                with TabPane("6 · Audition",       id="tab6"):
                    yield ScrollableContainer(Approach6Panel(id="a6"))
            yield RichLog(id="main-log", highlight=True, markup=True)
        yield Footer()

    def on_mount(self) -> None:
        # Connect MIDI — mirrors harbour_bells_v3 pattern (virtual port fallback)
        midi = MIDIManager.get()
        midi.channel = self._midi_channel - 1
        ok = midi.connect(self._midi_hint)
        bar = self.query_one("#midi-bar")
        is_virtual = "virtual" in midi.port_name.lower()
        if ok and not is_virtual:
            bar.update(f"[green]●[/] MIDI: [bold]{midi.port_name}[/]  ch {midi.channel+1}")
        elif ok and is_virtual:
            bar.update(f"[yellow]●[/] MIDI: [bold]{midi.port_name}[/]  (no hardware - virtual)")
        else:
            bar.update("[red]●[/] MIDI: connection failed")
        for line in midi.port_log:
            self.call_after_refresh(self.log_msg, f"[dim]{line}[/]")

        # Audio devices hint
        if HAS_AUDIO:
            devs = sd.query_devices()
            hints = [f"[{i}] {d['name'][:25]}" for i, d in enumerate(devs)
                     if d['max_input_channels'] > 0][:4]
            self.query_one("#audio-devices-hint").update(
                "  Audio inputs: " + "  ".join(hints)
            )

        self.set_interval(0.15, self._tick)
        self.log_msg("[bold cyan]S-1 Voice Synthesis TUI ready.[/]")
        self.log_msg(f"[dim]6 approaches | MIDI: {midi.port_name} | "
                     f"aubio={'yes' if HAS_AUBIO else 'no'} | "
                     f"tts={'yes' if HAS_TTS else 'no'} | "
                     f"flask={'yes' if HAS_FLASK else 'no'}[/]")

    def _tick(self) -> None:
        """Refresh all live approach panels."""
        try:
            self.query_one("#a1", Approach1Panel).refresh_status(self._approach1)
        except Exception:
            pass
        try:
            self.query_one("#a2", Approach2Panel).refresh_status(self._approach2)
        except Exception:
            pass
        try:
            self.query_one("#a3", Approach3Panel).refresh_status(self._approach3)
        except Exception:
            pass
        try:
            self.query_one("#a4", Approach4Panel).refresh_status(self._approach4)
        except Exception:
            pass
        try:
            self.query_one("#a5", Approach5Panel).refresh_status(self._approach5)
        except Exception:
            pass
        try:
            self.query_one("#a6", Approach6Panel).refresh_status(self._approach6)
        except Exception:
            pass

    def log_msg(self, text: str):
        try:
            ts = time.strftime("%H:%M:%S")
            self.query_one("#main-log", RichLog).write(f"[dim]{ts}[/]  {text}")
        except Exception:
            pass

    def action_panic(self) -> None:
        MIDIManager.get().panic()
        self.log_msg("[red]MIDI panic sent — all notes off[/]")

    def action_quit(self) -> None:
        # Clean up all running approaches
        for a in (self._approach2, self._approach3, self._approach4, self._approach5, self._approach6):
            try:
                a.stop()
            except Exception:
                pass
        MIDIManager.get().panic()
        self.exit()


# ═══════════════════════════════════════════════════════════════════════════════
# ENTRY POINT
# ═══════════════════════════════════════════════════════════════════════════════

def main():
    parser = argparse.ArgumentParser(
        description="S-1 Voice Synthesis TUI — 5 approaches to voice synthesis"
    )
    parser.add_argument("--midi",         type=str,  default=None,
                        help="MIDI port name hint (e.g. 'S-1')")
    parser.add_argument("--channel",      type=int,  default=3,
                        help="MIDI channel 1–16 (default 3, S-1 default)")
    parser.add_argument("--audio-device", type=int,  default=None,
                        help="Audio input device index")
    parser.add_argument("--list-devices", action="store_true",
                        help="List MIDI ports and audio devices then exit")
    args = parser.parse_args()

    if args.list_devices:
        if HAS_MIDI:
            mout = rtmidi.MidiOut()
            print("\n── MIDI Output Ports ──")
            for i, p in enumerate(mout.get_ports()):
                print(f"  [{i}] {p}")
        if HAS_AUDIO:
            print("\n── Audio Input Devices ──")
            devs = sd.query_devices()
            for i, d in enumerate(devs):
                if d['max_input_channels'] > 0:
                    print(f"  [{i}] {d['name']}")
        return

    app = S1VoiceTUI(
        midi_hint=args.midi,
        midi_channel=args.channel,
        audio_device=args.audio_device,
    )
    app.run()


if __name__ == "__main__":
    main()
