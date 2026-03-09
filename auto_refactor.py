import os
import re

folder = 'C:/Users/Owner/OneDrive/Documents/code/willickr/server/kernel/Stories/'
files = ['agent_beta_abyssal_chimes.py', 'agent_beta_ambient_2.py', 'agent_beta_ambient_3.py', 
         'agent_delta_euclidean_rhythm.py', 'agent_delta_markov_drone.py', 'agent_delta_markov_sequence.py', 
         'agent_delta_stochastic_fm_v2.py', 'agent_epsilon_glitch_1.py', 'agent_epsilon_stress_test_1.py', 
         'agent_epsilon_voice_steal_1.py', 'agent_gamma_k_organ_combo.py', 'agent_gamma_k_organ_tonewheel.py', 
         'agent_gamma_k_piano_acoustic.py', 'agent_gamma_k_piano_electric.py', 'agent_gamma_p_bell.py', 
         'agent_gamma_p_claves.py', 'agent_gamma_p_hihat_808.py', 'agent_gamma_w_bowed_articulation.py', 
         'agent_gamma_w_bowed_strings_1.py', 'agent_gamma_w_bowed_strings_2.py', 'agent_gamma_w_clarinet.py', 
         'agent_gamma_w_flute.py', 'agent_gamma_w_pan_pipes.py', 'agent_gamma_w_pwm_strings.py', 
         'agent_gamma_w_recorder.py', 'agent_gamma_w_string_machine.py', 'agent_gamma_w_violin.py', 
         'harbour_bells_fix.py', 'harbour_bells_v3.py', 'Sailor.py']

TEMPLATE = """{docstring}
import time
import random
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
try:
    from s1_midi import Midi, CC
except ImportError:
    from server.kernel.s1_midi import Midi, CC
from cartridge_base import BaseCartridge

class AutoConvertedCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {
             "afo:Loudness": CC.VOLUME,          
             "afo:SpectralCentroid": CC.FILTER_CUTOFF, 
             "afo:ModulationRate": CC.LFO_RATE,  
             "afo:RoomSize": CC.REVERB_LEVEL    
        }

{init_func}

    def execute(self, duration: float, device_id: int):
        midi = Midi(hint=str(device_id) if device_id else None)
        try:
            s1 = midi
        except: pass
        try:
            m = midi
        except: pass

        # Provide common aliases
{main_body}

if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
    cartridge = AutoConvertedCartridge()
    cartridge.execute(duration=5.0, device_id=hw_hint)
"""

for fname in files:
    path = os.path.join(folder, fname)
    if not os.path.exists(path):
        continue
    with open(path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Extract Docstring
    docstring = ""
    doc_match = re.match(r'^\"\"\"(.*?)\"\"\"', content, re.DOTALL)
    if doc_match:
        docstring = '"""' + doc_match.group(1) + '"""'
    else:
        docstring = '""" Auto-converted patch """'
        
    # Find init_patch or init_synth_primitive or similar function
    init_match = re.search(r'def\s+(init_[a-zA-Z0-9_]+|build_[a-zA-Z0-9_]+)\s*\([^)]*\):\s*(.*?)(?=\n\s*def\s|\nif\s+__name__|\Z)', content, re.DOTALL)
    init_func = ""
    if init_match:
        init_func = "    def init_synth_primitive(self, s1: Midi):\n" + init_match.group(2)
        # Fix indentation
        lines = init_func.split('\n')
        init_func = '\n'.join([("    " + line if not line.startswith("    def ") else line) for line in lines])
        # Replace instances of `s1.cc` assuming parameter `s1`
    
    # Main function
    main_match = re.search(r'def\s+(generate_[a-zA-Z0-9_]+|run_[a-zA-Z0-9_]+|demonstration)\s*\([^)]*\):\s*(.*?)(?=\n\s*def\s|\nif\s+__name__|\Z)', content, re.DOTALL)
    main_body = ""
    if main_match:
        # We need to extract the inner block of the main function, omitting the "Midi()" instantiation
        body = main_match.group(2)
        
        # Strip out Midi() instantiations
        body = re.sub(r'[a-zA-Z0-9_]+\s*=\s*Midi\([^)]*\)', '', body)
        # Strip out call to init function
        body = re.sub(r'(init_[a-zA-Z0-9_]+|build_[a-zA-Z0-9_]+)\([^)]*\)', 'self.init_synth_primitive(midi)', body)
        
        # Replace while True: with while time.time() - start_time < duration:
        body = re.sub(r'while\s+True\s*:', 'start_time = time.time()\n        while time.time() - start_time < duration:', body)
        
        # Modify the body to ensure time-bounding
        lines = body.split('\n')
        indented_lines = ["        " + line for line in lines]
        main_body = '\n'.join(indented_lines)
        
        # Add panic at end
        if 'panic()' not in main_body:
            main_body += '\n        midi.panic()'
    
    if not init_match and not main_match:
        print(f"COULD NOT PARSE: {fname}")
        continue
        
    new_content = TEMPLATE.format(
        docstring=docstring,
        init_func=init_func,
        main_body=main_body
    )
    
    # Fix aliases
    new_content = new_content.replace('s1.', 'midi.').replace('m.', 'midi.')
    
    # Save back
    with open(path, 'w', encoding='utf-8') as f:
        f.write(new_content)
    print(f"Converted {fname}")
