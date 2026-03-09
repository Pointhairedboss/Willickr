import mido
import os
import sys

def split_midi(filename, output_dir):
    print(f"Splitting {filename} into individual tracks at {output_dir}...")
    
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Failed to load MIDI: {e}")
        return
        
    os.makedirs(output_dir, exist_ok=True)
    
    # Track 0 is usually metadata/tempo map. We need to preserve it for all tracks
    # so they play back at the correct speed and timing if run individually.
    meta_track = mid.tracks[0]
    
    for i in range(1, len(mid.tracks)):
        track = mid.tracks[i]
        
        # Check if the track has any actual notes before we bother saving an empty file
        has_notes = False
        for msg in track:
            if msg.type == 'note_on' and msg.velocity > 0:
                has_notes = True
                break
                
        if not has_notes:
            print(f"Skipping Track {i}: ({track.name}) - Empty/No Note Data")
            continue
            
        clean_name = track.name.strip() if track.name.strip() else f"Instrument_{i}"
        # Sanitize filename
        safe_name = "".join([c for c in clean_name if c.isalpha() or c.isdigit() or c==' ']).rstrip()
        safe_name = safe_name.replace(" ", "_")
        
        out_file = os.path.join(output_dir, f"Track_{i:02d}_{safe_name}.mid")
        
        # Create a new MIDI file containing ONLY the metadata track and this specific instrument track
        new_mid = mido.MidiFile()
        new_mid.ticks_per_beat = mid.ticks_per_beat
        new_mid.tracks.append(meta_track)
        new_mid.tracks.append(track)
        
        new_mid.save(out_file)
        print(f"Saved: {out_file}")
        
    print("\n--- Split Complete ---")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        split_midi(sys.argv[1], "isolated_tracks")
    else:
        print("Usage: python split_midi_tracks.py <filename.mid>")
