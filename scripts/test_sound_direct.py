
import rtmidi
import time

def main():
    print("--- Willickr: Direct Hardware Sound Test ---")
    midi_out = rtmidi.MidiOut()
    available_ports = midi_out.get_ports()

    print(f"Available Ports: {available_ports}")

    # Find Internal Synth (Microsoft GS Wavetable Synth)
    target_port = -1
    for i, name in enumerate(available_ports):
        if "wavetable" in name.lower() or "microsoft" in name.lower():
            target_port = i
            break
            
    if target_port == -1:
        print("Internal Wavetable Synth not found. Trying index 0.")
        if available_ports:
            target_port = 0
        else:
            print("No MIDI ports found!")
            return

    port_name = available_ports[target_port]
    print(f"Connecting to INTERNAL SYNTH: {port_name}")
    midi_out.open_port(target_port)

    print("Playing scale (C Major)...")
    scale = [60, 62, 64, 65, 67, 69, 71, 72] # C4 to C5
    
    for note in scale:
        print(f"-> Note On: {note}")
        midi_out.send_message([0x90, note, 100]) # Note On, Vel 100
        time.sleep(0.3)
        midi_out.send_message([0x80, note, 0])   # Note Off
        time.sleep(0.1)
        
    print("Test Complete. If you heard nothing, check S-1 volume/drivers.")
    del midi_out

if __name__ == "__main__":
    main()
