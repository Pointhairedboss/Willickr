from fastapi import FastAPI, BackgroundTasks, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel
import subprocess
import os
import uuid
import sys
from typing import Optional, List

# Add multitrack kernel path so we can import its modules
multitrack_path = os.path.join(os.path.dirname(__file__), "kernel", "multitrack_experiment")
if multitrack_path not in sys.path:
    sys.path.append(multitrack_path)

from multitrack_studio import render_mixdown, load_patches

app = FastAPI(title="Willickr Agentic Studio API", version="1.0.0")

# Allow Web UI to communicate with the API
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

exports_dir = os.path.join(os.path.dirname(__file__), "exports")
os.makedirs(exports_dir, exist_ok=True)
app.mount("/exports", StaticFiles(directory=exports_dir), name="exports")

class RenderTrack(BaseModel):
    engine: str
    patch_name: str
    midi_file: str

class RenderRequest(BaseModel):
    tracks: Optional[List[RenderTrack]] = None
    engine: Optional[str] = None # "S1", "ToneJS", "libpd"
    patch_name: Optional[str] = None
    midi_file: Optional[str] = None # path to blueprint
    duration: float
    parameters: dict # The Universal Ontology Dictionary

# Store job status
jobs = {}

# Pre-load available S-1 patches into memory
AVAILABLE_PATCHES = load_patches()

from kernel.engine_router import EngineRouter
router = EngineRouter()

def execute_render(job_id: str, request: RenderRequest):
    """Background task to run the engine renderer without blocking the API."""
    try:
        jobs[job_id] = {"status": "processing"}
        print(f"[{job_id}] Starting render for job ID {job_id}")
        
        target_dir = os.path.join(os.path.dirname(__file__), "exports")
        os.makedirs(target_dir, exist_ok=True)
        target_wav = os.path.join(target_dir, f"api_{job_id}.wav")
        
        # Build the session list
        session = []
        tracks_to_process = request.tracks if request.tracks else []
        
        # Fallback to legacy single-track request if 'tracks' list is not provided
        if not tracks_to_process and request.engine and request.patch_name:
            tracks_to_process.append(RenderTrack(
                engine=request.engine, 
                patch_name=request.patch_name, 
                midi_file=request.midi_file if request.midi_file else "dummy.mid"
            ))
            
        for i, t in enumerate(tracks_to_process):
            # Give each track its own temp file so it doesn't overwrite
            temp_wav = os.path.join(target_dir, f"temp_{job_id}_{i}.wav")
            
            # Check if user passed a specific string file
            is_file_playback = t.midi_file and t.midi_file != "dummy.mid" and t.midi_file != "null"
            
            if is_file_playback and t.midi_file.lower().endswith(".wav"):
                # WAV FILE BYPASS: The user dragged an AudioAsset into the Graph.
                import shutil
                abs_wav = t.midi_file if os.path.isabs(t.midi_file) else os.path.join(os.path.dirname(__file__), "..", t.midi_file)
                if not os.path.exists(abs_wav):
                    # Check relative path
                    fallback = os.path.join(os.getcwd(), "..", t.midi_file)
                    if os.path.exists(fallback): abs_wav = fallback
                    else: raise FileNotFoundError(f"Requested WAV sample not found at {abs_wav}")
                    
                print(f"[{job_id}] WAV Sample Injection Bypass: Copying {abs_wav} to {temp_wav}")
                shutil.copyfile(abs_wav, temp_wav)
                wav = temp_wav
            else:
                # All engines now utilize the Object Oriented Cartridge system to generate control data!
                import importlib.util
                patch_file = os.path.join(os.path.dirname(__file__), "kernel", "Stories", f"{t.patch_name}.py")
                if not os.path.exists(patch_file):
                    raise ValueError(f"Cartridge {t.patch_name} not found.")
                    
                spec = importlib.util.spec_from_file_location(t.patch_name, patch_file)
                mod = importlib.util.module_from_spec(spec)
                spec.loader.exec_module(mod)
                
                import inspect
                from kernel.cartridge_base import BaseCartridge
                
                CartridgeClass = None
                for name, obj in inspect.getmembers(mod):
                    if inspect.isclass(obj) and hasattr(obj, 'execute') and hasattr(obj, 'apply_ontology') and name != "BaseCartridge":
                        CartridgeClass = obj
                        break
                        
                if not CartridgeClass:
                    raise ValueError(f"No valid Cartridge class found in {t.patch_name}.py")
                    
                instance = CartridgeClass()
                
                # Translate parameters via internal routing logic
                translated_params = router.translate_parameters(t.engine, request.parameters)
                instance.apply_ontology(translated_params)
                
                if t.engine in ("S1", "S-1"):
                    if is_file_playback:
                        wav = router.render_s1_midi_file(instance, t.midi_file, request.duration, temp_wav)
                    else:
                        wav = router.render_s1_cartridge(instance, request.duration, temp_wav)
                else:
                    fallback_patch = "additive_bell" if t.engine == "ToneJS" else "droids3"
                    if is_file_playback:
                        wav = router.render_offline_midi_file(instance, t.midi_file, t.engine, fallback_patch, request.duration, temp_wav)
                    else:
                        wav = router.render_offline_cartridge(instance, t.engine, fallback_patch, request.duration, temp_wav)
                    
            session.append({
                "engine": "pre_rendered",
                "url": wav
            })

        if not session:
            jobs[job_id] = {"status": "error", "message": "No valid tracks provided."}
            return

        # Perform actual Mixdown
        import numpy as np
        import soundfile as sf
        import shutil
        
        if len(session) > 1:
            print(f"[{job_id}] Mixing down {len(session)} tracks...")
            arrays = []
            max_len = 0
            sample_rate = 44100
            for s in session:
                data, fs = sf.read(s["url"])
                arrays.append(data)
                sample_rate = fs
                if len(data) > max_len: max_len = len(data)
                
            mix = np.zeros((max_len, 2))
            for arr in arrays:
                if arr.ndim == 1: # Convert mono to stereo
                    arr = np.column_stack((arr, arr))
                mix[:len(arr)] += arr
                
            peak = np.max(np.abs(mix))
            if peak > 0:
                mix = (mix / peak) * 0.95
                
            sf.write(target_wav, mix, sample_rate, subtype='PCM_16')
            
            # Clean up temp files
            for s in session:
                try: os.remove(s["url"])
                except: pass
        else:
            # Single track, just rename it
            shutil.copyfile(session[0]["url"], target_wav)
            try: os.remove(session[0]["url"])
            except: pass
             
        web_url = f"http://127.0.0.1:8000/exports/api_{job_id}.wav"
        jobs[job_id] = {"status": "complete", "url": web_url, "local_path": target_wav}
        print(f"[{job_id}] Finished processing. Mixdown saved to {target_wav}")

    except Exception as e:
        import traceback
        traceback.print_exc()
        jobs[job_id] = {"status": "error", "message": str(e)}

@app.get("/")
def read_root():
    return {"message": "Willickr Agentic Studio Core API Online."}

@app.post("/api/v1/render")
async def render_stem(request: RenderRequest, background_tasks: BackgroundTasks):
    """Initiates an audio generation task given an engine, a blueprint, and ontological parameters."""
    job_id = str(uuid.uuid4())
    background_tasks.add_task(execute_render, job_id, request)
    return {"job_id": job_id, "status": "processing"}

class ChatRequest(BaseModel):
    message: str

@app.post("/api/v1/chat")
async def process_chat(request: ChatRequest):
    import urllib.request
    import json
    import os
    
    # Dynamically inject available patches
    patch_dir = os.path.join(os.path.dirname(__file__), "kernel", "Stories")
    available_patches = []
    if os.path.exists(patch_dir):
        for file in os.listdir(patch_dir):
            if file.endswith(".py") and file != "__init__.py" and not file.startswith("agent_epsilon"):
                available_patches.append(f"- {file.replace('.py', '')}")
                
    patch_list_str = "\n".join(available_patches)

    system_prompt = f'''You are Agent Zeta, translating user intent for the Willickr Synthesizer.
Respond ONLY with a raw JSON object containing the musical configuration. No markdown formatting, no other text.
Format Example:
{{"engine": "S1", "patch_name": "agent_delta_fm_1", "duration": 10.0, "midi_file": null, "parameters": {{"afo:SpectralCentroid": 0.8, "afo:Loudness": 0.5, "afo:RoomSize": 0.9}}}}

Available engines: S1, ToneJS, libpd
Available Synth Patches:
{patch_list_str}

If the user wants to play a specific MIDI file instead of a generative algorithm, specify the filename in "midi_file" (e.g., "MidiArchive/MIDI Collection/10.mid"). Otherwise, set it to null.
Use the patch names exactly as listed above. Select a patch whose name best suggests the sonic qualities the user requested (e.g., "ambient_1" for soft drones, "gamma_k_piano" for keys).
'''
    data = {
        "model": "qwen/qwen3.5-9b",
        "system_prompt": system_prompt,
        "input": request.message
    }
    
    req = urllib.request.Request("http://localhost:1234/api/v1/chat", 
                                 data=json.dumps(data).encode('utf-8'), 
                                 headers={'Content-Type': 'application/json'})
    
    try:
        with urllib.request.urlopen(req) as response:
            raw_res = response.read().decode('utf-8')
            res_data = json.loads(raw_res)
            
            content = ""
            
            if 'output' in res_data:
                for item in reversed(res_data['output']):
                    if item.get('type') == 'message':
                        content = item.get('content', '')
                        break
            elif 'messages' in res_data:
                content = res_data['messages'][-1].get('content', '')
            elif 'choices' in res_data:
                content = res_data['choices'][0].get('message', {}).get('content', '')
            
            # Simple cleanup in case it outputs markdown blocks despite instructions
            content = content.replace('```json', '').replace('```', '').strip()
            
            try:
                payload = json.loads(content)
                return {"success": True, "payload": payload, "reply": f"LLM parsed intent successfully. Routing to {payload.get('patch_name')}."}
            except json.JSONDecodeError:
                return {"success": False, "reply": f"Failed to parse LLM output. Raw: {raw_res}"}
                
    except Exception as e:
         return {"success": False, "reply": f"LLM Connection Error: {str(e)}"}

@app.get("/api/v1/status/{job_id}")
def check_status(job_id: str):
    """Poll job status from the Web UI."""
    if job_id not in jobs:
         raise HTTPException(status_code=404, detail="Job not found")
    return jobs[job_id]

@app.get("/api/v1/assets")
def get_assets():
    import ast
    import glob
    
    # Audio Assets (WAV)
    audio_dir = os.path.join(os.path.dirname(__file__), "..", "AudioArchive")
    audio_assets = []
    if os.path.exists(audio_dir):
        for f in glob.glob(os.path.join(audio_dir, "*.wav")):
            bn = os.path.basename(f)
            audio_assets.append({
                "type": "input",
                "label": f"🌊 {bn}",
                "desc": "Direct audio bypass sample",
                "path": f"AudioArchive/{bn}"
            })
            
    # MIDI Assets 
    midi_dir = os.path.join(os.path.dirname(__file__), "..", "MidiArchive")
    midi_assets = []
    if os.path.exists(midi_dir):
        for root, dirs, files in os.walk(midi_dir):
            for file in files:
                if file.lower().endswith(".mid"):
                    rel_path = os.path.relpath(os.path.join(root, file), os.path.join(os.path.dirname(__file__), ".."))
                    midi_assets.append({
                        "type": "input",
                        "label": f"🎵 {file}",
                        "desc": "Vintage pattern data",
                        "path": rel_path.replace('\\', '/')
                    })
                    
    # Cartridge Algorithms
    cartridge_dir = os.path.join(os.path.dirname(__file__), "kernel", "Stories")
    cartridges = []
    if os.path.exists(cartridge_dir):
        for file in os.listdir(cartridge_dir):
            if file.endswith(".py") and file != "__init__.py" and not file.startswith("agent_epsilon") and file != "refactor_gamma.py":
                cname = file.replace('.py', '')
                try:
                    with open(os.path.join(cartridge_dir, file), 'r', encoding='utf-8') as f:
                        tree = ast.parse(f.read())
                        doc = ast.get_docstring(tree) or "Algorithm patch"
                        desc = doc.split('\n')[0][:50]
                except Exception:
                    desc = "Generative Algorithm"
                
                cartridges.append({
                    "type": "cartridgeNode",
                    "label": f"🔌 {cname}",
                    "desc": desc,
                    "path": cname
                })
                
    # Mixdown
    mixdowns = [{
        "type": "mixdownNode",
        "label": "🎛️ Multitrack Timeline",
        "desc": "DAW alignment & mixdown",
        "path": "10.0s Timeline"
    }]
    
    # Outputs
    outputs = [
        {"type": "output", "label": "📡 Roland S-1", "desc": "Hardware Synth", "path": "S1"},
        {"type": "output", "label": "🌐 Tone.js", "desc": "Web Audio synthesis", "path": "ToneJS"},
        {"type": "output", "label": "📦 libpd", "desc": "Pure Data offline patch", "path": "libpd"}
    ]
    
    return {
        "inputs": audio_assets + midi_assets,
        "algorithms": cartridges,
        "mixdown": mixdowns,
        "engines": outputs
    }

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="127.0.0.1", port=8000)
