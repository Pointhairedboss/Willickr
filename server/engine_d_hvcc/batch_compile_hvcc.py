import os
import glob
import subprocess
import shutil
from pathlib import Path

def run_compiler():
    print("--- Willickr HVCC Batch WASM Compiler ---")
    
    base_dir = r"C:\Users\Owner\OneDrive\Documents\code\willickr\SyntheoryGordonReid\BOOK-PUREDATA"
    out_dir = r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\engine_b_tonejs\wasm_library"
    hvcc_exe = r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\engine_d_hvcc\venv\Scripts\hvcc.exe"
    emsdk_env = r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\engine_d_hvcc\emsdk\emsdk_env.bat"
    
    if os.path.exists(out_dir):
        shutil.rmtree(out_dir)
    os.makedirs(out_dir, exist_ok=True)
    
    pd_files = glob.glob(os.path.join(base_dir, "**", "*.pd"), recursive=True)
    
    skip_dirs = ['ABSTRACTIONS', 'PD-COMMON', 'ABOUTPD', 'images']
    search_paths = [
        os.path.join(base_dir, 'ABSTRACTIONS'),
        os.path.join(base_dir, 'PD-COMMON')
    ]
    
    valid_pds = []
    for f in pd_files:
        path_obj = Path(f)
        skip = False
        for part in path_obj.parts:
            if part in skip_dirs:
                skip = True
                break
        
        if not skip:
            valid_pds.append(f)

    valid_pds = list(set(valid_pds)) # remove duplicates
    
    print(f"Isolated {len(valid_pds)} '.pd' files to compile.")
    
    success_count = 0
    fail_count = 0
    
    for pd_file in valid_pds:
        model_name = Path(pd_file).stem.replace("-", "_").replace(" ", "_").lower()
        parent_dir = str(Path(pd_file).parent)
        
        print(f"\n[Compiling] {model_name}...")
        
        tmp_build_dir = os.path.join(out_dir, f".tmp_{model_name}")
        
        # Build hvcc command
        cmd = f'call "{emsdk_env}" && "{hvcc_exe}" "{pd_file}" -o "{tmp_build_dir}" -n {model_name} -g js -p "{search_paths[0]}" -p "{search_paths[1]}" -p "{parent_dir}"'
        
        try:
            result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
            
            if result.returncode == 0:
                print(f"  -> C++ Transpilation & WASM Assembly: SUCCESS")
                
                # Move the compiled JS and WASM out of the temporary folder to the clean library path
                js_dir = os.path.join(tmp_build_dir, "js")
                
                if os.path.exists(js_dir):
                    final_js = os.path.join(out_dir, f"{model_name}.js")
                    final_worklet = os.path.join(out_dir, f"{model_name}_AudioLibWorklet.js")
                    
                    shutil.copy(os.path.join(js_dir, f"{model_name}.js"), final_js)
                    shutil.copy(os.path.join(js_dir, f"{model_name}_AudioLibWorklet.js"), final_worklet)
                    
                    # Also write a standard index test html for it
                    html = f'''<!DOCTYPE html><html><head><script src="{model_name}.js"></script>
<script>
window.renderOffline = async function(durationSeconds) {{
    return new Promise(async (resolve, reject) => {{
        try {{
            const sampleRate = 44100;
            const length = sampleRate * durationSeconds;
            const offlineCtx = new OfflineAudioContext(2, length, sampleRate);
            const heavyModule = await {model_name}_Module();
            const loader = new heavyModule.AudioLibLoader();
            await loader.init({{ blockSize: 2048, webAudioContext: offlineCtx }});
            loader.start();
            const renderedBuffer = await offlineCtx.startRendering();
            
            // Encode WAV
            function encodeWAV(audioBuffer) {{
                const numChannels = audioBuffer.numberOfChannels;
                const sampleRate = audioBuffer.sampleRate;
                const channelData = [];
                for (let i = 0; i < numChannels; i++) channelData.push(audioBuffer.getChannelData(i));
                let interleaved = new Float32Array(channelData[0].length * 2);
                let ix = 0;
                for(let i=0; i<channelData[0].length; i++) {{ interleaved[ix++] = channelData[0][i]; interleaved[ix++] = channelData[1][i]; }}
                const buffer = new ArrayBuffer(44 + interleaved.length * 2);
                const view = new DataView(buffer);
                const writeString = (view, offset, string) => {{ for(let i=0; i<string.length; i++) view.setUint8(offset + i, string.charCodeAt(i)); }};
                writeString(view, 0, 'RIFF');
                view.setUint32(4, 36 + interleaved.length * 2, true);
                writeString(view, 8, 'WAVE'); writeString(view, 12, 'fmt '); view.setUint32(16, 16, true);
                view.setUint16(20, 1, true); view.setUint16(22, 2, true); view.setUint32(24, sampleRate, true);
                view.setUint32(28, sampleRate * 4, true); view.setUint16(32, 4, true); view.setUint16(34, 16, true);
                writeString(view, 36, 'data'); view.setUint32(40, interleaved.length * 2, true);
                let offset = 44;
                for (let i = 0; i < interleaved.length; i++) {{
                    let s = Math.max(-1, Math.min(1, interleaved[i]));
                    view.setInt16(offset, s < 0 ? s * 0x8000 : s * 0x7FFF, true); offset += 2;
                }}
                return buffer;
            }}
            const wavBuffer = encodeWAV(renderedBuffer);
            const bytesWav = new Uint8Array(wavBuffer);
            let binaryWav = '';
            for (let i = 0; i < bytesWav.byteLength; i++) binaryWav += String.fromCharCode(bytesWav[i]);
            resolve(window.btoa(binaryWav));
        }} catch (err) {{ reject(err.toString()); }}
    }});
}};
</script></head><body></body></html>'''
                    with open(os.path.join(out_dir, f"{model_name}.html"), "w") as f:
                        f.write(html)
                        
                    success_count += 1
                
                # Cleanup tmp
                shutil.rmtree(tmp_build_dir)
            else:
                print(f"  -> C++ Transpilation: FAILED (Check missing abstractions)")
                fail_count += 1
        except Exception as e:
            print(f"  -> System Error: {e}")
            fail_count += 1

    print("\n--- Batch Compilation Complete ---")
    print(f"Successfully minted {success_count} isolated WASM Software Cartridges.")
    print(f"Failed to transpile {fail_count} models (Likely missing complex nested abstraction links).")
    print(f"Outputs saved to: {out_dir}")

if __name__ == "__main__":
    run_compiler()
