import mido
import time
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

def init_clean_keys(midi: Midi):
    # A very basic, clean, square-wave organ sound based on Gamma-K
    midi.cc(CC.SAW_LEVEL, 0)
    midi.cc(CC.OSC_SQUARE, 80)     
    midi.cc(CC.SUB_LEVEL, 0)     
    midi.cc(CC.NOISE_LEVEL, 0)     
    
    # Filter wide open to hear the pure notes clearly
    midi.cc(CC.FILTER_CUTOFF, 100)  
    midi.cc(CC.FILTER_RES, 0)      
    
    # Fast attack, instant release
    midi.cc(CC.AMP_ATTACK, 0)      
    midi.cc(CC.AMP_DECAY, 5)       
    midi.cc(CC.AMP_SUSTAIN, 100)   
    midi.cc(CC.AMP_RELEASE, 5)     
    
    # No portamento, chorus, or weird LFOs
    midi.cc(5, 0) # Portamento OFF
    midi.cc(CC.CHORUS_LEVEL, 0)   
    midi.cc(CC.REVERB_LEVEL, 10)
    
    time.sleep(0.5)

def play_all_tracks():
    filename = r"C:\Users\Owner\Downloads\252_Doctor-Who.mid"
    print(f"Loading {filename} for mass auditioning...")
    
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Failed to load MIDI: {e}")
        return
        
    s1 = Midi()
    print("Setting S-1 to Clean Keys Audition Patch...")
    init_clean_keys(s1)
    
    tempo = 500000 # default 120 bpm
    for msg in mid.tracks[0]:
        if msg.type == 'set_tempo':
            tempo = msg.tempo
            break
            
    ticks_per_beat = mid.ticks_per_beat
    
    # Track 0 is usually metadata, start at 1
    for i in range(1, len(mid.tracks)):
        track = mid.tracks[i]
        
        # Check if the track actually has note events before we bother waiting
        has_notes = False
        for msg in track:
            if msg.type == 'note_on' and msg.velocity > 0:
                has_notes = True
                break
                
        if not has_notes:
            continue
            
        print(f"\n======================================")
        print(f"AUDITIONING TRACK {i}: {track.name}")
        print("Playing 10 seconds. Listen closely...")
        print(f"======================================")
        
        start_time = time.time()
        
        try:
            for msg in track:
                if time.time() - start_time > 10.0:
                    break # Stop playing this track after 10 real-time seconds
                    
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
                    
        except KeyboardInterrupt:
            s1.panic()
            print("\nSkipping to next track...")
            time.sleep(1)
            
        s1.panic()
        print("Track audition complete. Moving to next...")
        time.sleep(1.5) # Give the user a breath
        
    print("\n--- Audition Sequence Complete ---")

if __name__ == "__main__":
    play_all_tracks()
