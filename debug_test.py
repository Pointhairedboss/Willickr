import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
server_dir = os.path.join(script_dir, "server")
sys.path.insert(0, server_dir)

from willickr_api import RenderRequest, execute_render

payload = {
    "duration": 5.0, 
    "parameters": {}, 
    "engine": "S1", 
    "tracks": [
        {"engine": "ToneJS", "patch_name": "agent_alpha_bell_1", "midi_file": "dummy.mid"}
    ]
}

req = RenderRequest(**payload)
print("Executing render ...")
try:
    execute_render("TEST_ID", req)
    print("Done")
except Exception as e:
    import traceback
    traceback.print_exc()
