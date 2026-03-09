import mido
import time
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi
import dr_who_theme as dw

def play_track7():
    filename = r"C:\Users\Owner\Downloads\252_Doctor-Who.mid"
    print(f"Loading {filename}...")
    mid = mido.MidiFile(filename)
    
    s1 = Midi()
    print("Initializing Melody Patch...")
    dw.init_who_melody(s1)
    # Add portamento glide
    s1.cc(5, 75)
    
    track = mid.tracks[7]
    
    print("Playing Track 7 on the S-1...")
    
    # Track 3 has an initial delay, we might want to skip the massive silence 
    # but mido handles time deltas in ticks. Let's calculate ticks to seconds.
    tempo = 500000 # default 120 bpm
    for msg in mid.tracks[0]:
        if msg.type == 'set_tempo':
            tempo = msg.tempo
            break
            
    ticks_per_beat = mid.ticks_per_beat
    
    for msg in track:
        # sleep for the time delta
        time_seconds = mido.tick2second(msg.time, ticks_per_beat, tempo)
        if time_seconds > 0:
            time.sleep(time_seconds)
            
        if msg.type == 'note_on':
            if msg.velocity > 0:
                s1.on(msg.note, 100)
            else:
                s1.off(msg.note)
        elif msg.type == 'note_off':
            s1.off(msg.note)
            
    s1.panic()
    print("Done.")

if __name__ == "__main__":
    play_track7()
