import mido
import sys

def parse_highest_melody(filename):
    print(f"Parsing highest notes from {filename} Track 3...")
    notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Error loading MIDI: {e}")
        return

    for t_idx, track in enumerate(mid.tracks):
        current_time = 0
        note_events = []
        for msg in track:
            current_time += msg.time
            if msg.type == 'note_on' and msg.velocity > 0:
                note_events.append({'time': current_time, 'note': msg.note})
        
        if not note_events:
            continue
            
        melody_line = []
        THRESHOLD = 20
        current_chord = []
        last_time = -1
        
        for ev in note_events:
            if last_time == -1 or (ev['time'] - last_time) < THRESHOLD:
                current_chord.append(ev['note'])
            else:
                highest_note = max(current_chord)
                octave = (highest_note // 12) - 1
                melody_line.append(f"{notes[highest_note % 12]}{octave}")
                current_chord = [ev['note']]
            last_time = ev['time']
            
        if current_chord:
            highest_note = max(current_chord)
            octave = (highest_note // 12) - 1
            melody_line.append(f"{notes[highest_note % 12]}{octave}")

        print(f"\nTrack {t_idx} ({track.name}):")
        print(" -> ".join(melody_line[:30]))

pass

if __name__ == "__main__":
    if len(sys.argv) > 1:
        parse_highest_melody(sys.argv[1])
    else:
        print("Usage: python parse_midi2.py <filename.mid>")
