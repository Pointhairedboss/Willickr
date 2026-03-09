import os
import json
import subprocess
import threading
import queue
import time
import sounddevice as sd
import soundfile as sf
import sys

# Ensure s1_midi is accessible
parent_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if parent_dir not in sys.path:
    sys.path.append(parent_dir)

SAMPLE_RATE = 44100

class EngineRouter:
    def __init__(self):
        self.device_profiles = {}
        self.load_profiles()
    
    def load_profiles(self):
        data_dir = os.path.join(parent_dir, 'data')
        s1_profile_path = os.path.join(data_dir, 's1_profile.json')
        if os.path.exists(s1_profile_path):
            with open(s1_profile_path, 'r') as f:
                self.device_profiles["S1"] = json.load(f)
                
    def _find_s1_audio_input(self):
        for i, dev in enumerate(sd.query_devices()):
            if dev['max_input_channels'] > 0 and any(n in dev['name'].upper() for n in ('S-1', 'ROLAND')):
                return i, dev['name']
        return None, None

    def translate_parameters(self, engine: str, parameters: dict) -> dict:
        """
        Translates Universal Ontology macros into specific engine dials (like CC values)
        By default, translates normalized 0.0-1.0 to the target range.
        """
        if engine not in self.device_profiles:
            return parameters # pass-through if no profile
            
        profile = self.device_profiles[engine]
        translated = {}
        
        for macro, value in parameters.items():
            if macro in profile.get("macro_mappings", {}):
                mapping = profile["macro_mappings"][macro]
                target = mapping.get("target", mapping.get("midi_cc")) # backwards compat
                min_val = mapping.get("range_min", 0)
                max_val = mapping.get("range_max", 127)
                
                # Assume value is normalized 0.0 - 1.0
                scaled_val = min_val + (max_val - min_val) * value
                translated[target] = int(scaled_val) if target != "pd_receive" else float(scaled_val)
            else:
                translated[macro] = value # pass-through 
                
        return translated

    def render_s1_cartridge(self, cartridge_instance, duration_seconds: float, output_wav: str):
        """
        Executes a BaseCartridge object while recording the S-1 hardware via USB.
        """
        dev_id, dev_name = self._find_s1_audio_input()
        if dev_id is None:
            raise RuntimeError("Hardware Error: Roland S-1 USB Audio not found.")
            
        print(f"Routing to Hardware {dev_name} for {duration_seconds}s...")
        q = queue.Queue()
        
        def audio_callback(indata, frames, time_info, status):
            q.put(indata.copy())

        # Brief pause to ensure audio engine readiness
        time.sleep(0.5)

        stream = sd.InputStream(
            samplerate=SAMPLE_RATE, 
            device=dev_id, 
            channels=2, 
            callback=audio_callback
        )
        
        with stream:
            midi_thread = threading.Thread(target=cartridge_instance.execute, args=(duration_seconds, dev_id))
            midi_thread.start()
            
            with sf.SoundFile(output_wav, mode='w', samplerate=SAMPLE_RATE, channels=2, subtype='PCM_16') as file: 
                start_time = time.time()
                while time.time() - start_time < duration_seconds:
                    try:
                        file.write(q.get(timeout=0.2))
                    except queue.Empty:
                        pass
                    
            midi_thread.join(timeout=1.0)
            
        print(f"Saved {output_wav}")
        return output_wav

    def render_offline_cartridge(self, cartridge_instance, engine: str, patch_name: str, duration_seconds: float, output_wav: str):
        """
        Executes a Cartridge in offline memory to generate a MIDI file, 
        then passes that MIDI file to the headless WASM or Tone.js renderer.
        """
        print(f"Generating Virtual MIDI Buffer for {patch_name}...")
        
        # This will run the cartridge time sleeps and dump to virtual_sequence.mid
        generated_mid = os.path.abspath(f"virtual_sequence_{patch_name}.mid")
        cartridge_instance.execute(duration_seconds, "offline") # Ensure offline writes here
        
        # Need to fix s1_midi.py to write to this specific generated_mid, or we can just capture the default one here
        default_mid = os.path.abspath("virtual_sequence.mid")
        if not os.path.exists(default_mid):
            raise FileNotFoundError(f"Virtual sequence generation failed for {patch_name}.")
            
        if engine == "ToneJS":
            return self.render_tonejs(patch_name, default_mid, duration_seconds, output_wav)
        elif engine == "libpd":
            return self.render_libpd(patch_name, default_mid, duration_seconds, output_wav)
        else:
            raise ValueError(f"Unknown offline engine requested: {engine}")

    def render_s1_midi_file(self, cartridge_instance, midi_file_path: str, duration_seconds: float, output_wav: str):
        """
        Initializes the synth using the Cartridge's aesthetic flavor, then plays a raw MIDI file instead of
        the Cartridge's generative script.
        """
        import mido
        dev_id, dev_name = self._find_s1_audio_input()
        if dev_id is None:
            raise RuntimeError("Hardware Error: Roland S-1 USB Audio not found.")
            
        # Resolve correct path
        abs_midi = midi_file_path if os.path.isabs(midi_file_path) else os.path.join(parent_dir, midi_file_path)
        if not os.path.exists(abs_midi):
            # Fallback if someone passed it from the server dir context
            fallback_root = os.path.join(parent_dir, "..", midi_file_path)
            fallback_current = os.path.join(os.getcwd(), midi_file_path)
            
            if os.path.exists(fallback_root):
                abs_midi = os.path.abspath(fallback_root)
            elif os.path.exists(fallback_current):
                abs_midi = os.path.abspath(fallback_current)
            else:
                raise FileNotFoundError(f"Requested MIDI File not found: {midi_file_path}")

        print(f"Routing MIDI File `{abs_midi}` to Hardware {dev_name} for {duration_seconds}s...")
        q = queue.Queue()
        
        def audio_callback(indata, frames, time_info, status):
            q.put(indata.copy())

        time.sleep(0.5)
        stream = sd.InputStream(
            samplerate=SAMPLE_RATE, 
            device=dev_id, 
            channels=2, 
            callback=audio_callback
        )
        
        thread_error = None

        def play_midi_thread():
            nonlocal thread_error
            try:
                # Initialize with aesthetic flavor parameter sets
                from s1_midi import Midi
                hw_midi = Midi(hint=str(dev_id))
                cartridge_instance.init_synth_primitive(hw_midi)
                time.sleep(0.5)
                
                mid = mido.MidiFile(abs_midi)
                start_time = time.time()
                for msg in mid.play():
                    if time.time() - start_time > duration_seconds:
                        break
                    
                    msg_type = getattr(msg, 'type', None)
                    if msg_type == 'note_on':
                        if msg.velocity == 0:
                            hw_midi.off(msg.note)
                        else:
                            hw_midi.on(msg.note, msg.velocity)
                    elif msg_type == 'note_off':
                        hw_midi.off(msg.note)
                hw_midi.panic()
            except Exception as e:
                import traceback
                traceback.print_exc()
                thread_error = e

        with stream:
            midi_thread = threading.Thread(target=play_midi_thread)
            midi_thread.start()
            
            with sf.SoundFile(output_wav, mode='w', samplerate=SAMPLE_RATE, channels=2, subtype='PCM_16') as file: 
                start_time = time.time()
                while time.time() - start_time < duration_seconds:
                    if thread_error:
                        raise RuntimeError(f"MIDI playback thread failed: {thread_error}")
                    try:
                        file.write(q.get(timeout=0.2))
                    except queue.Empty:
                        pass
                    
            midi_thread.join(timeout=1.0)
            
        if thread_error:
            raise RuntimeError(f"MIDI playback thread failed: {thread_error}")
            
        print(f"Saved {output_wav}")
        return output_wav

    def render_offline_midi_file(self, cartridge_instance, midi_file_path: str, engine: str, patch_name: str, duration_seconds: float, output_wav: str):
        """
        Bypasses generating a virtual_sequence.mid and directly routes the requested MIDI file to ToneJS/libpd.
        """
        print(f"Bypassing generation. Routing MIDI file `{midi_file_path}` directly to offline engine...")
        
        # ToneJS WASM currently accepts direct midi_file parameter injections.
        abs_midi = midi_file_path if os.path.isabs(midi_file_path) else os.path.join(parent_dir, midi_file_path)
        if not os.path.exists(abs_midi):
            fallback_root = os.path.join(parent_dir, "..", midi_file_path)
            fallback_current = os.path.join(os.getcwd(), midi_file_path)
            
            if os.path.exists(fallback_root):
                abs_midi = os.path.abspath(fallback_root)
            elif os.path.exists(fallback_current):
                abs_midi = os.path.abspath(fallback_current)
            else:
                raise FileNotFoundError(f"Requested MIDI File not found: {midi_file_path}")
            
        if engine == "ToneJS":
            return self.render_tonejs(patch_name, abs_midi, duration_seconds, output_wav)
        elif engine == "libpd":
            return self.render_libpd(patch_name, abs_midi, duration_seconds, output_wav)
        else:
            raise ValueError(f"Unknown offline engine requested: {engine}")
            
    def render_libpd(self, patch_name: str, midi_file: str, duration_seconds: float, output_wav: str):
        """
        Fires the WASM C-Physics headless render.
        Note: Currently script bridges via CLI args, but will soon pass true parameter JSON.
        """
        print(f"Routing to WASM libpd engine [{patch_name}] for {duration_seconds}s...")
        script_path = os.path.join(parent_dir, "engine_b_tonejs", "render_libpd.js")
        if not os.path.exists(midi_file):
            # Pass a dummy string if no midi
            midi_file = "dummy.mid"
            
        subprocess.run(
            ["node", script_path, midi_file, patch_name, str(duration_seconds), output_wav],
            cwd=os.path.join(parent_dir, "engine_b_tonejs"),
            check=True
        )
        print(f"Saved {output_wav}")
        return output_wav
        
    def render_tonejs(self, patch_name: str, midi_file: str, duration_seconds: float, output_wav: str):
        """
        Fires the Tone.JS headless render.
        """
        print(f"Routing to ToneJS engine [{patch_name}] for {duration_seconds}s...")
        script_path = os.path.join(parent_dir, "engine_b_tonejs", "render_tonejs.js")
        
        subprocess.run(
            ["node", script_path, midi_file, patch_name, str(duration_seconds), output_wav],
            cwd=os.path.join(parent_dir, "engine_b_tonejs"),
            check=True
        )
        print(f"Saved {output_wav}")
        return output_wav
