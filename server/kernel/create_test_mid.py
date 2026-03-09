import mido
from mido import Message, MidiFile, MidiTrack

def create_test_midi(filename):
    mid = MidiFile()
    track = MidiTrack()
    mid.tracks.append(track)
    
    # 1. C Major Chord (4 voices max, playing safe)
    # Note on all together
    track.append(Message('note_on', note=48, velocity=64, time=0))  # C3
    track.append(Message('note_on', note=55, velocity=64, time=0))  # G3
    track.append(Message('note_on', note=60, velocity=64, time=0))  # C4
    track.append(Message('note_on', note=64, velocity=64, time=0))  # E4
    
    # Hold for ~2 seconds (960 ticks per beat conceptually here, using arbitrary wait in ticks)
    track.append(Message('note_off', note=48, velocity=64, time=1920)) 
    track.append(Message('note_off', note=55, velocity=64, time=0))
    track.append(Message('note_off', note=60, velocity=64, time=0))
    track.append(Message('note_off', note=64, velocity=64, time=0))
    
    # Very short pause
    track.append(Message('note_on', note=41, velocity=64, time=480)) # F2, delay start

    # 2. F Major Chord 
    # Note on all together
    track.append(Message('note_on', note=53, velocity=64, time=0))  # F3
    track.append(Message('note_on', note=57, velocity=64, time=0))  # A3
    track.append(Message('note_on', note=60, velocity=64, time=0))  # C4
    
    # Note off
    track.append(Message('note_off', note=41, velocity=64, time=1920)) 
    track.append(Message('note_off', note=53, velocity=64, time=0))
    track.append(Message('note_off', note=57, velocity=64, time=0))
    track.append(Message('note_off', note=60, velocity=64, time=0))
    
    mid.save(filename)
    print(f"Successfully generated test MIDI file: {filename}")

if __name__ == "__main__":
    create_test_midi("test.mid")
