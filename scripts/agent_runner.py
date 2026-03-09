import asyncio
import websockets
import json

async def run_agent():
    uri = "ws://localhost:3001"
    try:
        async with websockets.connect(uri) as websocket:
            print("Action: Agent Connected to Engine.")
            
            # 1. Analyze
            print("Action: Requesting Earthquake Analysis (12 Months proxy)...")
            await websocket.send(json.dumps({"action": "analyze", "source": "usgs_quake"}))
            
            analysis_result = None
            # Wait for result
            for _ in range(10): # Timeout loop
                try:
                    msg = await asyncio.wait_for(websocket.recv(), timeout=2.0)
                    data = json.loads(msg)
                    if data.get('type') == 'analysis_result':
                        analysis_result = data['payload']
                        print(f"Observation: Received Analysis data: {analysis_result}")
                        break
                except asyncio.TimeoutError:
                    print("Waiting for analysis...")
            
            if not analysis_result:
                print("Error: Analysis timed out.")
                return

            # 2. Reason & Configure
            intensity = float(analysis_result.get("max_magnitude", 0))
            count = int(analysis_result.get("count", 0))
            
            print(f"Reasoning: Max Magnitude is {intensity}. Threshold is 4.5.")
            
            if intensity > 4.5:
                print("Decision: INTENSE. Mode: CHAOTIC.")
                
                # Set Identity
                print("Action: Configuring Identity (140 BPM, Whole Tone, Root 36)...")
                await websocket.send(json.dumps({
                    "action": "configure_identity", 
                    "bpm": 140, 
                    "scale": "whole_tone", 
                    "root": 36
                }))
                
                # Assign Tracks
                print("Action: Assigning Track 'Lead' -> Chaos Generator...")
                await websocket.send(json.dumps({"action": "assign_track", "track": "Lead", "generator": "chaos", "channel": 0}))
                
                print("Action: Assigning Track 'Bass' -> Markov Generator...")
                await websocket.send(json.dumps({"action": "assign_track", "track": "Bass", "generator": "markov", "channel": 1}))
            else:
                print("Decision: CALM. Mode: AMBIENT.")
                await websocket.send(json.dumps({
                    "action": "configure_identity", 
                    "bpm": 70, 
                    "scale": "pentatonic_minor", 
                    "root": 48
                }))
                await websocket.send(json.dumps({"action": "assign_track", "track": "Lead", "generator": "euclidean", "channel": 2}))
                
            # 3. Play
            print("Action: Triggering Playback.")
            await websocket.send(json.dumps({"action": "transport_play"}))
            
            # Keep alive briefly to ensure commands sent
            await asyncio.sleep(2)
            print("Result: Composition Running.")
            
    except Exception as e:
        print(f"Agent Error: {e}")

if __name__ == "__main__":
    asyncio.run(run_agent())
