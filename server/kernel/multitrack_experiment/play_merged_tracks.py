import mido
import time
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi
import dr_who_theme as dw

def play_merged_tracks(s1, track_files):
    print(f"\n=========================================")
    print(f"PLAYING MERGED TRACKS:")
    for f in track_files:
        print(f" - {os.path.basename(f)}")
    print("Playing from 0:00 to 1:00...")
    print(f"=========================================")
    
    # We need to flatten all tracks into a single list of absolute-time events
    # so we can play them back chronologically.
    all_events = []
    
    for filename in track_files:
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
        
        track_to_play = mid.tracks[1] if len(mid.tracks) > 1 else mid.tracks[0]
        
        for msg in track_to_play:
            delta_sec = mido.tick2second(msg.time, ticks_per_beat, tempo)
            current_time_sec += delta_sec
            
            if current_time_sec > 60.0:
                break # Cap at 1 minute
                
            if msg.type in ['note_on', 'note_off']:
                all_events.append({
                    'time': current_time_sec,
                    'msg': msg
                })
                
    # Sort all events chronologically
    all_events.sort(key=lambda item: item['time'])
    
    print("Beginning synchronized playback...")
    
    start_real_time = time.time()
    
    try:
        for ev in all_events:
            target_time = ev['time']
            msg = ev['msg']
            
            # Wait until we reach the event's precise timestamp
            while (time.time() - start_real_time) < target_time:
                time.sleep(0.001)
                
            if msg.type == 'note_on' and msg.velocity > 0:
                s1.on(msg.note, 100)
            else:
                s1.off(msg.note)
                    
    except KeyboardInterrupt:
        print("\nPlayback interrupted by user.")
        
    finally:
        s1.panic()
        time.sleep(1)
        print("Done.")

def main():
    print("Connecting to S-1...")
    s1 = Midi()
    
    print("Loading the Static, Clean Doctor Who Melody Patch...")
    dw.init_who_melody(s1)
    
    tracks_to_merge = [
        r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\kernel\multitrack_experiment\isolated_tracks\Track_03_Instrument3.mid",
        r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\kernel\multitrack_experiment\isolated_tracks\Track_04_Instrument4.mid",
    ]
    
    play_merged_tracks(s1, tracks_to_merge)

if __name__ == "__main__":
    main()
