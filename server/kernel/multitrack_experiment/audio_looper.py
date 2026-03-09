import sys
import os
import time
import queue
import threading
import sounddevice as sd
import soundfile as sf
import numpy as np

# Ensure imports resolve to master Stories folder
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC
import dr_who_theme as dw
import mido

SAMPLE_RATE = 44100

def find_s1_audio_input():
    devices = sd.query_devices()
    for i, dev in enumerate(devices):
        if dev['max_input_channels'] > 0 and any(name in dev['name'].upper() for name in ('S-1', 'ROLAND')):
            return i, dev['name']
    return None, None

def find_s1_audio_output():
    devices = sd.query_devices()
    for i, dev in enumerate(devices):
        if dev['max_output_channels'] > 0 and any(name in dev['name'].upper() for name in ('S-1', 'ROLAND')):
            return i, dev['name']
    return None, None

def record_midi_pass(midi_func, pass_name, duration_seconds, s1_device_id):
    """
    Synchronously plays a MIDI function while recording audio from the S-1.
    """
    print(f"\n[PASS: {pass_name}] Preparing to Record...")
    
    q = queue.Queue()
    
    def audio_callback(indata, frames, time_info, status):
        # This is called by sounddevice for each audio block
        if status:
            print(status, file=sys.stderr)
        q.put(indata.copy())

    # We wait just a moment before striking the first note
    time.sleep(1)
    
    filename = f"{pass_name}.wav"
    print(f"Recording to {filename} for {duration_seconds} seconds...")
    
    # Start the Audio Recording Stream
    stream = sd.InputStream(
        samplerate=SAMPLE_RATE, 
        device=s1_device_id, 
        channels=2, 
        callback=audio_callback
    )
    
    with stream:
        # Start the MIDI performance on a separate thread so it doesn't block the stream
        midi_thread = threading.Thread(target=midi_func)
        midi_thread.start()
        
        # Open a soundfile to write the queue data to disk
        with sf.SoundFile(filename, mode='x', samplerate=SAMPLE_RATE, channels=2) as file:
            start_time = time.time()
            while time.time() - start_time < duration_seconds:
                file.write(q.get())
                
        # Wait for MIDI to finish
        midi_thread.join(timeout=1.0)
        
    print(f"[PASS: {pass_name}] Recording complete.")

def record_tonejs_pass(midi_file, patch_name, pass_name, duration_seconds):
    print(f"\n[RECORDING TONE.JS PASS] {pass_name}")
    filename = f"{pass_name}.wav"
    print(f"Tracking to {filename} for {duration_seconds}s...")
    
    script_path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "engine_b_tonejs", "render_tonejs.js")
    
    import subprocess
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
    
    script_path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "engine_b_tonejs", "render_libpd.js")
    
    import subprocess
    try:
        subprocess.run(
            ["node", script_path, midi_file, patch_name, str(duration_seconds), filename],
            cwd=os.path.dirname(script_path),
            check=True
        )
        print(f"Saved {filename}")
        return filename
    except subprocess.CalledProcessError as e:
        print(f"Error rendering libpd pass: {e}")
        return None

def run_session():
    print("--- S-1 Python DAW: Dual-Engine Orchestrator ---")
    
    dev_id, dev_name = find_s1_audio_input()
    out_dev_id, out_dev_name = find_s1_audio_output()
    
    if dev_id is None:
        print("ERROR: Could not detect Roland S-1 USB Audio input interface.")
        print("Available devices:")
        print(sd.query_devices())
        return
        
    print(f"Found S-1 Audio Input: {dev_name} (ID: {dev_id})")
    
    tracks_dir = os.path.join(os.path.dirname(__file__), "isolated_tracks")
    json_path = os.path.join(tracks_dir, "track_names.json")
    
    if not os.path.exists(json_path):
        print(f"ERROR: No routing metadata found at {json_path}. Please run audition_and_tag.py first.")
        return
        
    import json
    with open(json_path, 'r') as f:
        tracks_metadata = json.load(f)
            
    RECORD_DURATION = 45.0
    wav_files = []
    
    try:
        # Loop through mapped tracks
        for i, (midi_filename, meta) in enumerate(tracks_metadata.items()):
            midi_path = os.path.join(tracks_dir, midi_filename)
            if not os.path.exists(midi_path):
                continue
                
            # Backwards compatibility check
            if isinstance(meta, str):
                meta = {"name": meta, "engine": "S1", "patch": "init_clean_keys"}
                
            engine = meta.get("engine", "S1")
            patch_name = meta.get("patch", "init_clean_keys")
            safe_name = meta.get("name", "Unknown").replace(" ", "_").lower()
            pass_name = f"track_{i+1}_{engine}_{safe_name}"
            
            if engine == "ToneJS":
                wav = record_tonejs_pass(midi_path, patch_name, pass_name, RECORD_DURATION)
                if wav: wav_files.append(wav)
            elif engine == "libpd":
                wav = record_libpd_pass(midi_path, patch_name, pass_name, RECORD_DURATION)
                if wav: wav_files.append(wav)
            else:
                # Resolve patch function from dr_who_theme dynamically as default fallback for looper
                patch_func = getattr(dw, patch_name, dw.init_who_melody)
                
                # To support play_bass_only wrapped logic:
                def play_wrapper():
                    # Minimal wrapper replicating previous manual function
                    s1 = Midi()
                    patch_func(s1)
                    s1.cc(CC.VOLUME, 100)
                    all_events = []
                    try:
                        mid = mido.MidiFile(midi_path)
                        tempo = 500000 
                        for msg in mid.tracks[0]:
                            if msg.type == 'set_tempo':
                                tempo = msg.tempo
                        ticks_per_beat = mid.ticks_per_beat
                        current_time_sec = 0.0
                        track_to_play = mid.tracks[1] if len(mid.tracks) > 1 else mid.tracks[0]
                        for msg in track_to_play:
                            delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
                            current_time_sec += delta_sec
                            if current_time_sec <= RECORD_DURATION:
                                if msg.type in ['note_on', 'note_off']:
                                    all_events.append({'time': current_time_sec, 'msg': msg})
                    except Exception: pass
                    all_events.sort(key=lambda item: item['time'])
                    start_real_time = time.time()
                    try:
                        for ev in all_events:
                            target_time = ev['time']
                            msg = ev['msg']
                            while (time.time() - start_real_time) < target_time: time.sleep(0.001)
                            if msg.type == 'note_on' and msg.velocity > 0: s1.on(msg.note, 100)
                            else: s1.off(msg.note)
                    except KeyboardInterrupt: pass
                    finally: s1.panic()

                record_midi_pass(play_wrapper, pass_name, RECORD_DURATION, dev_id)
                wav_files.append(f"{pass_name}.wav")
        
        # Final Pass: Digital Mixdown in Python using Numpy
        print("\n[MIXDOWN] Loading isolated tracks for digital bounce...")
        
        arrays = []
        for wav in wav_files:
            if os.path.exists(wav):
                data, fs = sf.read(wav)
                arrays.append(data)
                
        if not arrays:
            print("No audio tracked.")
            return
            
        # Ensure identical sample lengths (trimming exact floating point discrepancies)
        min_len = min(len(a) for a in arrays)
        mixed_data = np.zeros((min_len, 2))
        
        for a in arrays:
            mixed_data += a[:min_len] * 0.8
            
        # Hard limit/clip to prevent analog clipping artifacts from floating point overflow
        mixed_data = np.clip(mixed_data, -1.0, 1.0)
        
        out_name = "master_mix_dual_engine.wav"
        print(f"Writing '{out_name}'...")
        sf.write(out_name, mixed_data, SAMPLE_RATE)
        
        print("\n--- Session Complete ---")
        print(f"A perfectly synchronized dual-engine digital bounce has been saved to '{out_name}'!")

    except KeyboardInterrupt:
        print("\nRecording aborted.")

if __name__ == "__main__":
    run_session()
