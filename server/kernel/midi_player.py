import sys
import os
import time
import mido
import importlib

# Ensure kernel is in path for imports
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from s1_midi import Midi

def play_midi_with_patch(midi_file_path, patch_module_name, target_channel=None):
    """
    Loads an AI-generated S-1 patch, initializes it, and then streams
    a standard `.mid` file to the synthesizer. Automatically filters to a single
    channel to prevent polyphony chaos on the 4-voice S-1.
    """
    
    s1 = Midi()

    # Optional: ensure sound is off before we start
    s1.panic()
    time.sleep(0.1)

    # 1. Dynamically load the patch module from the Stories directory
    print(f"Loading patch module: {patch_module_name}")
    
    stories_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "Stories")
    if stories_path not in sys.path:
        sys.path.append(stories_path)
        
    try:
        patch_module = importlib.import_module(patch_module_name)
    except ModuleNotFoundError as e:
        print(f"Error: Could not find patch '{patch_module_name}' in {stories_path}")
        print(e)
        return

    # 2. Initialize the patch parameters (Sends all CCs to the S-1)
    if hasattr(patch_module, 'init_patch'):
        patch_module.init_patch(s1)
        # Give the hardware a tiny bit of time to settle after a CC flood
        time.sleep(0.2) 
    else:
        print(f"Warning: Module '{patch_module_name}' does not contain an 'init_patch(s1)' function.")
        print("Midi file will play with current physical S-1 settings.")

    # 3. Load and play the MIDI file using `mido`
    print(f"Playing MIDI file: {midi_file_path}")
    try:
        mid = mido.MidiFile(midi_file_path)
        
        # Auto-detect the best channel to play if not specified
        if target_channel is None:
            channel_counts = {}
            for track in mid.tracks:
                for msg in track:
                    if msg.type == 'note_on' and msg.velocity > 0:
                        ch = getattr(msg, 'channel', 0)
                        # Channel 9 (0-indexed) is General MIDI drums. Skip it for synth patches.
                        if ch != 9: 
                            channel_counts[ch] = channel_counts.get(ch, 0) + 1
            if channel_counts:
                target_channel = max(channel_counts, key=channel_counts.get)
                print(f"Auto-selected MIDI Channel {target_channel} (contains the most melodic notes).")
            else:
                target_channel = 0
                print("Could not auto-detect melodic channel. Defaulting to 0.")
        else:
            print(f"Playing explicitly requested MIDI Channel {target_channel}.")

        # mid.play() handles the time delays automatically based on the tempo and ticks encoded in the file
        for msg in mid.play():
            if getattr(msg, 'channel', None) != target_channel:
                continue # Ignore other tracks/instruments to preserve 4-voice polyphony
                
            if msg.type == 'note_on':
                # mido represents note_off as note_on with velocity 0 sometimes
                if msg.velocity > 0:
                    s1.on(msg.note, msg.velocity)
                else:
                    s1.off(msg.note)
            elif msg.type == 'note_off':
                s1.off(msg.note)
            elif msg.type == 'control_change':
                # Ignore control changes from the MIDI file so they don't overwrite our custom Python patch parameters
                pass

    except FileNotFoundError:
        print(f"Error: Could not find MIDI file '{midi_file_path}'")
    except Exception as e:
        print(f"Error during playback: {e}")
    finally:
        s1.panic()
        print("Playback complete. Sent all notes off.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python midi_player.py <path_to_midi_file.mid> <patch_script_name_without_py> [target_channel]")
        print("Example: python midi_player.py test.mid agent_beta_glacial_pad")
        print("Example (specific channel): python midi_player.py test.mid agent_beta_glacial_pad 2")
        sys.exit(1)
        
    midi_path = sys.argv[1]
    patch_name = sys.argv[2]
    
    tgt_channel = None
    if len(sys.argv) > 3:
        tgt_channel = int(sys.argv[3])
    
    play_midi_with_patch(midi_path, patch_name, tgt_channel)
