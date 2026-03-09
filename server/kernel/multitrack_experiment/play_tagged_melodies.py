import mido
import time
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi
import dr_who_theme as dw

def play_long_track(s1, filename, track_name):
    print(f"\n=========================================")
    print(f"PLAYING: {track_name} ({os.path.basename(filename)})")
    print("Playing from 0:00 to 1:00 to catch the delayed sweep...")
    print(f"=========================================")
    
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Error loading {filename}: {e}")
        return

    tempo = 500000 
    for msg in mid.tracks[0]:
        if msg.type == 'set_tempo':
            tempo = msg.tempo
            break
            
    ticks_per_beat = mid.ticks_per_beat
    
    current_time_sec = 0.0
    stop_playback_sec = 60.0
    
    try:
        track_to_play = mid.tracks[1] if len(mid.tracks) > 1 else mid.tracks[0]
        
        for msg in track_to_play:
            if msg.type == 'note_on' or msg.type == 'note_off':
                delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
                current_time_sec += delta_sec
                
                if current_time_sec > stop_playback_sec:
                    break 
                    
                if delta_sec > 0:
                    time.sleep(delta_sec)
                    
                if msg.type == 'note_on' and msg.velocity > 0:
                    s1.on(msg.note, 100)
                else:
                    s1.off(msg.note)
            else:
                delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
                current_time_sec += delta_sec
                if current_time_sec > stop_playback_sec:
                    break
                    
    except KeyboardInterrupt:
        s1.panic()
        print("\nPlayback interrupted by user.")
        
    s1.panic()
    time.sleep(2)

def play_target_tracks():
    print("Connecting to S-1...")
    s1 = Midi()
    
    print("Loading the Static, Clean Doctor Who Melody Patch...")
    dw.init_who_melody(s1)
    
    targets = [
        ("isolated_tracks/Track_09_Instrument9.mid", "melodyhigh")
    ]
    
    for filename, name in targets:
        if os.path.exists(filename):
            play_long_track(s1, filename, name)
        else:
            print(f"Could not find {filename}")

if __name__ == "__main__":
    play_target_tracks()
