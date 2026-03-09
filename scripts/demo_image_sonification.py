
import asyncio
import os
import random
from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client
import json

# Configuration
SERVER_SCRIPT = "server/willickr_mcp.py"
IMAGE_URL = "https://picsum.photos/800/600" # Random Scenery (Placeholder)
TEMP_IMAGE = "temp_nebula.jpg"

async def main():
    print("--- Willickr Demo: First Light ---")
    
    # 1. Download Test Image
    print(f"[1] Downloading test image: {IMAGE_URL}")
    import urllib.request
    try:
        urllib.request.urlretrieve(IMAGE_URL, TEMP_IMAGE)
        print("    Image saved locally.")
    except Exception as e:
        print(f"    Error downloading image: {e}")
        return

    # 2. Connect to Willickr Engine (MCP)
    import sys
    # Use the same python executable running this script to run the server
    python_exe = sys.executable 
    
    print(f"[2] Connecting to Willickr Engine at {SERVER_SCRIPT}...")
    server_params = StdioServerParameters(
        command=python_exe,
        args=[SERVER_SCRIPT],
        env=os.environ.copy() # Pass current environment
    )

    async with stdio_client(server_params) as (read, write):
        async with ClientSession(read, write) as session:
            await session.initialize()
            print("    Connected to MCP Server.")

            # 3. Load Image into Kernel
            print(f"[3] Loading image into Math Kernel...")
            # Note: We need absolute path for the server tool
            abs_path = os.path.abspath(TEMP_IMAGE)
            result = await session.call_tool("kernel_load_image", arguments={"path": abs_path})
            print(f"    Result: {result.content[0].text}")

            # 4. Scan Image (Middle Horizon)
            print(f"[4] Scanning image horizon (50%)...")
            scan_data = await session.call_tool("kernel_scan_image", arguments={"y_percent": 0.5})
            # content is a JSON string in the text field
            data = json.loads(scan_data.content[0].text)
            brightness = data.get("brightness", [])
            print(f"    Extracted {len(brightness)} data points.")

            # 5. Generate Notes from Data
            # Simple mapping: Brightness (0-1) -> Scale Degree -> MIDI Note
            print(f"[5] Sonifying data stream...")
            
            scale = [0, 2, 4, 5, 7, 9, 11] # Major Scale
            root = 60 # Middle C
            
            # Subsample the data to avoid machine-gun notes (take every 10th pixel)
            pixel_step = 10
            melody = []
            
            for i in range(0, len(brightness), pixel_step):
                val = brightness[i]
                # Map 0-1 to scale index (0-14, 2 octaves)
                scale_idx = int(val * 14) 
                octave = scale_idx // 7
                note_idx = scale_idx % 7
                midi_note = root + (octave * 12) + scale[note_idx]
                melody.append(midi_note)

            print(f"    Generated {len(melody)} notes: {melody[:10]}...")

            # 6. Play Notes (Simulated Real-time)
            print(f"[6] Playing sequence to MIDI output...")
            
            # Try to force connection to S-1 if available
            print("    Configuring MIDI Port...")
            port_res = await session.call_tool("set_midi_port", arguments={"port_name": "S-1"})
            print(f"    {port_res.content[0].text}")

            ports_res = await session.call_tool("list_midi_ports")
            print(f"    Available MIDI Ports: {ports_res.content[0].text}")
            
            for note in melody[:20]: # Play first 20 notes
                # Visualization: * whose height depends on pitch
                height = (note - 60) // 2
                print(f"    Note {note} |" + "-" * height + "*")
                
                await session.call_tool("play_test_note", arguments={"note": note, "velocity": 80, "duration": 0.1})
                await asyncio.sleep(0.15) # 150ms tempo

            print("--- Demo Complete ---")
            
            # Cleanup
            try:
                os.remove(TEMP_IMAGE)
            except:
                pass

if __name__ == "__main__":
    asyncio.run(main())
