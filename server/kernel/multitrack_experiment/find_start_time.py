import mido
import sys
import os

def find_start_time(filename):
    print(f"Analyzing {os.path.basename(filename)}...")
    
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
        
        if msg.type == 'note_on' and msg.velocity > 0:
            print(f"The first note starts at exactly: {current_time_sec:.2f} seconds.")
            # Convert MIDI integer back to a note name for readability
            notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
            octave = (msg.note // 12) - 1
            note_name = f"{notes[msg.note % 12]}{octave}"
            print(f"The first note is: {note_name} (MIDI {msg.note})")
            return

if __name__ == "__main__":
    if len(sys.argv) > 1:
        find_start_time(sys.argv[1])
    else:
        print("Usage: python find_start_time.py <filename.mid>")
