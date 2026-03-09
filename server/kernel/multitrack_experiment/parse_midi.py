import mido
import sys

def parse_melody(filename):
    print(f"Parsing {filename}...")
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Error loading MIDI: {e}")
        return

    # Print out track names to find the melody
    print("Available Tracks:")
    for i, track in enumerate(mid.tracks):
        print(f"  Track {i}: {track.name}")

    print("\n--- Scanning for Note Events ---")
    
    track = mid.tracks[3]
    print(f"\n--- Scanning Track 3: {track.name} ---")
    note_count = 0
    for msg in track:
        if msg.type == 'note_on' and msg.velocity > 0:
            notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
            octave = (msg.note // 12) - 1
            note_name = f"{notes[msg.note % 12]}{octave}"
            print(f"Note ON:  {msg.note} ({note_name}) | Time Delta: {msg.time}")
            note_count += 1
            if note_count > 100:
                break

if __name__ == "__main__":
    if len(sys.argv) > 1:
        parse_melody(sys.argv[1])
    else:
        print("Usage: python parse_midi.py <filename.mid>")
