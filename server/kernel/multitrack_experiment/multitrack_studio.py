import sys
import os
import time
import queue
import threading
import json
import glob
import importlib.util
import inspect
import mido
import sounddevice as sd
import soundfile as sf
import numpy as np
import subprocess

# Ensure s1_midi is accessible
parent_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if parent_dir not in sys.path:
    sys.path.append(parent_dir)
from s1_midi import Midi, CC

SAMPLE_RATE = 44100

def find_s1_audio_input():
    for i, dev in enumerate(sd.query_devices()):
        if dev['max_input_channels'] > 0 and any(n in dev['name'].upper() for n in ('S-1', 'ROLAND')):
            return i, dev['name']
    return None, None

def find_s1_audio_output():
    for i, dev in enumerate(sd.query_devices()):
        if dev['max_output_channels'] > 0 and any(n in dev['name'].upper() for n in ('S-1', 'ROLAND')):
            return i, dev['name']
    return None, None

def load_track_info():
    tracks_dir = os.path.join(os.path.dirname(__file__), "isolated_tracks")
    json_path = os.path.join(tracks_dir, "track_names.json")
    tracks = {}
    if os.path.exists(json_path):
        with open(json_path, 'r') as f:
            t_names = json.load(f)
            for file, val in t_names.items():
                if isinstance(val, str):
                    tracks[file] = {"name": val, "engine": "S1", "patch": "init_clean_keys"}
                else:
                    tracks[file] = val
    
    # Grab any orphaned midis
    for f in glob.glob(os.path.join(tracks_dir, "*.mid")):
        bn = os.path.basename(f)
        if bn not in tracks:
            tracks[bn] = {"name": "Unknown Track", "engine": "S1", "patch": "init_clean_keys"}
            
    return tracks, tracks_dir

def load_patches():
    # Scan Stories and kernel for python files, load them, find patch init functions
    patches = {}
    search_dirs = [
        os.path.join(parent_dir, "Stories"),
        parent_dir # for dr_who_theme.py
    ]
    
    print("Indexing S-1 Generative Patches...")
    for sdir in search_dirs:
        if not os.path.exists(sdir): continue
        for py_file in glob.glob(os.path.join(sdir, "*.py")):
            bn = os.path.basename(py_file)
            if bn in ["s1_midi.py", "patch_app.py", "setup.py"]: continue
            
            try:
                spec = importlib.util.spec_from_file_location(bn[:-3], py_file)
                mod = importlib.util.module_from_spec(spec)
                spec.loader.exec_module(mod)
                
                for name, func in inspect.getmembers(mod, inspect.isfunction):
                    # Look for functions that sound like patch builders
                    if name.startswith("init_") or name.startswith("build_") or name.startswith("apply_"):
                        sig = inspect.signature(func)
                        # Ensure it takes at least 1 arg (the Midi object)
                        if len(sig.parameters) >= 1:
                            patches[f"{bn[:-3]}.{name}"] = func
            except Exception:
                pass
                
    return patches

def play_midi_with_patch(midi_file, patch_func, max_duration=None):
    s1 = Midi()
    print(f"Loading patch '{patch_func.__name__}' to S-1...")
    
    # Many patches aren't graceful, use try/except
    try:
        patch_func(s1)
    except Exception as e:
        print(f"Warning: Patch threw an error but might have still applied: {e}")
        
    s1.cc(CC.VOLUME, 100)
    
    try:
        mid = mido.MidiFile(midi_file)
        tempo = 500000 
        for msg in mid.tracks[0]:
            if msg.type == 'set_tempo':
                tempo = msg.tempo
                
        ticks_per_beat = mid.ticks_per_beat
        current_time_sec = 0.0
        track_to_play = mid.tracks[1] if len(mid.tracks) > 1 else mid.tracks[0]
        
        all_events = []
        for msg in track_to_play:
            delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
            current_time_sec += delta_sec
            
            if max_duration is None or current_time_sec <= max_duration:
                if msg.type in ['note_on', 'note_off']:
                    all_events.append({
                        'time': current_time_sec,
                        'msg': msg
                    })
            elif max_duration is not None and current_time_sec > max_duration:
                break
                
        all_events.sort(key=lambda item: item['time'])
        print(f"Streaming MIDI from {os.path.basename(midi_file)}...")
        start_real_time = time.time()
        
        for ev in all_events:
            target_time = ev['time']
            msg = ev['msg']
            while (time.time() - start_real_time) < target_time:
                time.sleep(0.001)
                
            if msg.type == 'note_on' and msg.velocity > 0:
                s1.on(msg.note, msg.velocity)
            else:
                s1.off(msg.note)
    except KeyboardInterrupt:
        print("\nPlayback stopped by user.")
    except Exception as e:
        print(f"Playback error: {e}")
    finally:
        s1.panic()

def record_pass(midi_file, patch_func, pass_name, duration_seconds, s1_device_id):
    print(f"\n[RECORDING PASS] {pass_name}")
    q = queue.Queue()
    
    def audio_callback(indata, frames, time_info, status):
        q.put(indata.copy())

    time.sleep(0.5)
    filename = f"{pass_name}.wav"
    print(f"Tracking to {filename} for {duration_seconds}s...")
    
    stream = sd.InputStream(
        samplerate=SAMPLE_RATE, 
        device=s1_device_id, 
        channels=2, 
        callback=audio_callback
    )
    
    with stream:
        midi_thread = threading.Thread(target=play_midi_with_patch, args=(midi_file, patch_func, duration_seconds))
        midi_thread.start()
        
        # 'w' mode overwrites existing files safely
        with sf.SoundFile(filename, mode='w', samplerate=SAMPLE_RATE, channels=2) as file: 
            start_time = time.time()
            while time.time() - start_time < duration_seconds:
                file.write(q.get())
                
        midi_thread.join(timeout=1.0)
    print(f"Saved {filename}")
    return filename

def record_tonejs_pass(midi_file, patch_name, pass_name, duration_seconds):
    print(f"\n[RECORDING TONE.JS PASS] {pass_name}")
    filename = f"{pass_name}.wav"
    print(f"Tracking to {filename} for {duration_seconds}s...")
    
    script_path = os.path.join(parent_dir, "engine_b_tonejs", "render_tonejs.js")
    
    try:
        subprocess.run(
            ["node", script_path, midi_file, patch_name, str(duration_seconds), filename],
            check=True
        )
        print(f"Saved {filename}")
        return filename
    except subprocess.CalledProcessError as e:
        print(f"Error rendering Tone.js pass: {e}")
        return None

def record_libpd_pass(midi_file, patch_name, pass_name, duration_seconds):
    print(f"\n[RECORDING libpd.wasm PASS] {pass_name}")
    filename = f"{pass_name}.wav"
    print(f"Tracking to {filename} for {duration_seconds}s...")
    
    script_path = os.path.join(parent_dir, "engine_b_tonejs", "render_libpd.js")
    
    try:
        subprocess.run(
            ["node", script_path, midi_file, patch_name, str(duration_seconds), filename],
            cwd=os.path.join(parent_dir, "engine_b_tonejs"),
            check=True
        )
        print(f"Saved {filename}")
        return filename
    except subprocess.CalledProcessError as e:
        print(f"Error rendering libpd pass: {e}")
        return None

def render_mixdown(session, duration, out_file=None):
    dev_id, dev_name = find_s1_audio_input()
    if dev_id is None:
        print("ERROR: Could not detect Roland S-1 USB Audio input interface.")
        return
        
    print(f"\n--- RENDERING {len(session)} TRACKS ({duration}s each) ---")
    wav_files = []
    
    try:
        for i, track_state in enumerate(session):
            midi_file = track_state['mid_file']
            engine = track_state['engine']
            patch_name = track_state['patch_name']
            
            pass_name = f"render_track_{i+1}_{os.path.basename(midi_file)[:-4]}"
            
            if engine == "ToneJS":
                wav = record_tonejs_pass(midi_file, patch_name, pass_name, duration)
            elif engine == "libpd":
                wav = record_libpd_pass(midi_file, patch_name, pass_name, duration)
            else:
                patch_func = track_state['patch_func']
                wav = record_pass(midi_file, patch_func, pass_name, duration, dev_id)
                
            if wav:
                wav_files.append(wav)
            
        print("\n[MIXDOWN] Loading isolated tracks for digital bounce...")
        
        arrays = []
        for wav in wav_files:
            data, fs = sf.read(wav)
            arrays.append(data)
            
        if not arrays:
            return
            
        min_len = min(len(a) for a in arrays)
        mixed_data = np.zeros((min_len, 2))
        
        for a in arrays:
            # Drop the gain slightly per track to avoid master bus clipping
            mixed_data += a[:min_len] * 0.8
            
        mixed_data = np.clip(mixed_data, -1.0, 1.0)
        
        if out_file is None:
            out_file = "master_studio_mix.wav"
        
        sf.write(out_file, mixed_data, SAMPLE_RATE)
        print(f"\n--- Bounce Complete: {out_file} ---")
        return out_file
        
    except KeyboardInterrupt:
        print("\nRender aborted.")


