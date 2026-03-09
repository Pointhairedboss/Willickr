import os
import glob
import re

directory = '.'

# Find all gamma patches
files = glob.glob('agent_gamma_*.py') + glob.glob('gamma_*.py')

def process_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
        
    if "cartridge_base" in content and "BaseCartridge" in content:
        return # already refactored
        
    # 1. Add imports
    content = re.sub(r'(from s1_midi import Midi, CC)', r'\1\nfrom cartridge_base import BaseCartridge', content)
    
    funcs = list(re.finditer(r'^def\s+([a-zA-Z0-9_]+)\s*\(\s*([a-zA-Z0-9_]+)\s*:\s*Midi\s*\)\s*:', content, re.MULTILINE))
    if len(funcs) < 2:
        print(f"Skipping {filepath}, found {len(funcs)} functions")
        return
        
    init_func_match = funcs[0]
    exec_func_match = funcs[1]
    
    init_name = init_func_match.group(1)
    init_arg = init_func_match.group(2)
    
    exec_name = exec_func_match.group(1)
    exec_arg = exec_func_match.group(2)
    
    name_main_match = re.search(r'^if\s+__name__\s*==\s*["\']__main__["\']\s*:', content, re.MULTILINE)
    
    if not name_main_match:
        print(f"Skipping {filepath}, NO main block")
        return
        
    init_body = content[init_func_match.end():exec_func_match.start()]
    exec_body = content[exec_func_match.end():name_main_match.start()]
    
    def indent_body(body):
        lines = body.split('\n')
        if not lines: return body
        base_indents = [len(l) - len(l.lstrip()) for l in lines if l.strip()]
        if not base_indents: return body
        base_indent = min(base_indents)
        
        out = []
        for l in lines:
            if l.strip():
                out.append('        ' + l[base_indent:])
            else:
                out.append(l)
        return '\n'.join(out)
        
    init_body_indented = indent_body(init_body)
    exec_body_indented = indent_body(exec_body)
    
    exec_body_indented = re.sub(rf'^\s*{init_name}\({exec_arg}\)\s*\n', '', exec_body_indented, flags=re.MULTILINE)
    
    def repl_cutoff(m):
        val = m.group(1)
        if val.isdigit():
            c_val = int(val)
            min_v = max(0, c_val - 30)
            max_v = min(127, c_val + 30)
            return f'self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, self.get_val("afo:SpectralCentroid", {min_v}, {max_v})'
        return f'self.get_cc("afo:SpectralCentroid") or CC.FILTER_CUTOFF, {val}'
    init_body_indented = re.sub(r'CC\.FILTER_CUTOFF\s*,\s*([^\)]+)', repl_cutoff, init_body_indented)
    
    def repl_reverb(m):
        val = m.group(1)
        if val.isdigit():
            return f'self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, self.get_val("afo:RoomSize", 0, 100)'
        return f'self.get_cc("afo:RoomSize") or CC.REVERB_LEVEL, {val}'
    init_body_indented = re.sub(r'CC\.REVERB_LEVEL\s*,\s*([^\)]+)', repl_reverb, init_body_indented)
    
    def repl_vol(m):
        val = m.group(1)
        if val.isdigit():
            return f'self.get_cc("afo:Loudness") or CC.VOLUME, self.get_val("afo:Loudness", 50, 127)'
        return f'self.get_cc("afo:Loudness") or CC.VOLUME, {val}'
    init_body_indented = re.sub(r'CC\.VOLUME\s*,\s*([^\)]+)', repl_vol, init_body_indented)
    
    class_def = f"""
class GammaAcousticCartridge(BaseCartridge):
    def __init__(self):
        super().__init__()
        self.parameters = {{
            "afo:SpectralCentroid": CC.FILTER_CUTOFF,
            "afo:RoomSize": CC.REVERB_LEVEL,
            "afo:Loudness": CC.VOLUME,
            "afo:ModulationRate": CC.LFO_RATE
        }}

    def init_synth_primitive(self, {init_arg}: Midi):
{init_body_indented}

    def execute(self, duration: float, device_id: int):
        {exec_arg} = Midi(hint=str(device_id) if device_id else None)
        self.init_synth_primitive({exec_arg})
        
        print(f"\\n[Agent Gamma] Triggering sequence for {{duration}}s.")
{exec_body_indented}
"""
    
    main_block = f"""if __name__ == "__main__":
    hw_hint = None
    for a in sys.argv[1:]:
        if not a.startswith("-"): hw_hint = a
        
    cartridge = GammaAcousticCartridge()
    cartridge.apply_ontology({{"afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.4}})
    cartridge.execute(duration=5.0, device_id=hw_hint)
"""

    pre_funcs = content[:init_func_match.start()]
    new_content = pre_funcs + class_def + main_block
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(new_content)
        
    print(f"Refactored {filepath}")

for f in files:
    try:
        process_file(f)
    except Exception as e:
        print(f"Error on {f}: {e}")
