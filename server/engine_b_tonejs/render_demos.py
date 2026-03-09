import os
import subprocess

out_dir = r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\exports\wasm_demos"
script_dir = r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\engine_b_tonejs"
script_path = os.path.join(script_dir, "render_libpd.js")
dummy_mid = r"C:\Users\Owner\OneDrive\Documents\code\willickr\server\kernel\multitrack_experiment\test.mid"

# Create a small dummy mid file if it doesn't exist to satisfy the args
with open(dummy_mid, 'w') as f:
    f.write('dummy')

demos = [
    ("wind4", 8.0),
    ("fire_crackling3", 6.0),
    ("water4", 6.0),
    ("jetengine1", 8.0),
    ("tos_phaser", 4.0),
    ("pedestrian_beep", 5.0),
    ("droids3", 6.0),
    ("ringingtone", 5.0)
]

print("Rendering WebAssembly Physics Models...")

for patch, duration in demos:
    out_wav = os.path.join(out_dir, f"{patch}_demo.wav")
    print(f"-> Rendering {patch}.wasm ({duration}s)...")
    
    try:
         subprocess.run(
            ["node", script_path, dummy_mid, patch, str(duration), out_wav],
            cwd=script_dir,
            check=True
        )
         print(f"   [Done] Saved to {out_wav}")
    except Exception as e:
         print(f"   [Failed] Error generating {patch}.wasm: {e}")

print("Batch rendering complete.")
