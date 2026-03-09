import mido
import time
import sys
import os
import glob
import json

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_clean_keys(midi: Midi):
    # Clean, simple square-wave organ sound
    midi.cc(CC.SAW_LEVEL, 0)
    midi.cc(CC.OSC_SQUARE, 80)     
    midi.cc(CC.SUB_LEVEL, 0)     
    midi.cc(CC.NOISE_LEVEL, 0)     
    
    # Filter wide open
    midi.cc(CC.FILTER_CUTOFF, 100)  
    midi.cc(CC.FILTER_RES, 0)      
    
    # Fast attack, instant release
    midi.cc(CC.AMP_ATTACK, 0)      
    midi.cc(CC.AMP_DECAY, 5)       
    midi.cc(CC.AMP_SUSTAIN, 100)   
    midi.cc(CC.AMP_RELEASE, 5)     
    
    # Zero Effects
    midi.cc(5, 0) # Portamento OFF
    midi.cc(CC.CHORUS_LEVEL, 0)   
    midi.cc(CC.REVERB_LEVEL, 10)
    
    time.sleep(0.5)

def play_track_segment(s1, filename):
    print(f"\n=========================================")
    print(f"LOADING: {os.path.basename(filename)}")
    print("Playing from 0:10 to 0:25...")
    
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Error loading {filename}: {e}")
        return False

    tempo = 500000 
    for msg in mid.tracks[0]:
        if msg.type == 'set_tempo':
            tempo = msg.tempo
            break
            
    ticks_per_beat = mid.ticks_per_beat
    
    current_time_sec = 0.0
    start_playback_sec = 10.0
    stop_playback_sec = 25.0
    
    try:
        track_to_play = mid.tracks[1] if len(mid.tracks) > 1 else mid.tracks[0]
        
        for msg in track_to_play:
            if msg.type == 'note_on' or msg.type == 'note_off':
                delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
                current_time_sec += delta_sec
                
                if current_time_sec > stop_playback_sec:
                    break 
                    
                if current_time_sec >= start_playback_sec:
                    if delta_sec > 0:
                        time.sleep(delta_sec)
                        
                    if msg.type == 'note_on' and msg.velocity > 0:
                        s1.on(msg.note, 100)
                    else:
                        s1.off(msg.note)
            else:
                # Still need to increment time for non-note events!
                delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
                current_time_sec += delta_sec
                if current_time_sec > stop_playback_sec:
                    break
                    
    except KeyboardInterrupt:
        s1.panic()
        print("\nPlayback interrupted by user.")
        
    s1.panic()
    print("\n--- Playback Finished ---")
    return True

def audition_tracks():
    directory = "isolated_tracks"
    json_file = os.path.join(directory, "track_names.json")
    
    track_names = {}
    if os.path.exists(json_file):
        with open(json_file, "r") as f:
            raw_data = json.load(f) or {}
            # Backwards compatibility migration
            for k, v in raw_data.items():
                if isinstance(v, str):
                    track_names[k] = {"name": v, "engine": "S1", "patch": "init_clean_keys"}
                else:
                    track_names[k] = v

    midi_files = glob.glob(os.path.join(directory, "*.mid"))
    midi_files.sort()
    
    if not midi_files:
        print("No .mid files found in isolated_tracks/")
        return
        
    print("--- Interactive MIDI Audition ---")
    print("Connecting to S-1...")
    s1 = Midi()
    init_clean_keys(s1)
    
    for filename in midi_files:
        basename = os.path.basename(filename)
        
        if basename in track_names:
            print(f"Skipping {basename} (Already tagged as: {track_names[basename]['name']})")
            continue
            
        while True:
            success = play_track_segment(s1, filename)
            if not success:
               break
               
            response = input(f"What is the name for {basename}? (or type 'replay' / 'skip'): ").strip()
            
            if response.lower() == 'replay':
                print("Replaying...")
                # Loop continues, track plays again
            elif response.lower() == 'skip':
                print("Skipping...")
                break
            elif response != "":
                engine = input("Engine? (S1/ToneJS/libpd) [default: S1]: ").strip()
                if not engine: engine = "S1"
                
                patch = input("Patch Name? [default: init_clean_keys]: ").strip()
                if not patch: patch = "init_clean_keys"
                
                track_names[basename] = {
                    "name": response, 
                    "engine": engine, 
                    "patch": patch
                }
                
                with open(json_file, "w") as f:
                    json.dump(track_names, f, indent=4)
                print(f"Saved -> {response} ({engine}: {patch})")
                break

    print("\nAll tracks audited!")

if __name__ == "__main__":
    audition_tracks()
