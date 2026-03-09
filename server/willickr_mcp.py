import sys
import os
import json
import logging
import asyncio
import time
from typing import Any, Optional, Dict, List, Set
import rtmidi
try:
    from midiutil import MIDIFile
except ImportError:
    MIDIFile = None  # Will warn if user tries to export
import websockets
from websockets.server import serve

from mcp.server.fastmcp import FastMCP

# Add scripts directory to path for generic analysis
SCRIPTS_DIR = os.path.join(os.path.dirname(__file__), '..', 'scripts')
sys.path.append(SCRIPTS_DIR)
try:
    import axes
except ImportError:
    logging.warning(f"Could not import axes from {SCRIPTS_DIR}")
    axes = None

# --- 1. Instrumentation (Rule #4) ---
# We configure logging to write to a file AND stderr (for Cursor debug console if needed)
# But since MCP uses stdio, we must be careful not to corrupt stdout.
# We will log to a file 'willickr_server.jsonl' in the same directory.

LOG_FILE = "willickr_server.jsonl"
CONNECTED_CLIENTS: Set[websockets.WebSocketServerProtocol] = set()

async def broadcast(message: Dict[str, Any]):
    if not CONNECTED_CLIENTS:
        return
    msg_str = json.dumps(message)
    # create copies to avoid runtime errors if set changes during iteration
    for client in list(CONNECTED_CLIENTS):
        try:
            await client.send(msg_str)
        except:
            pass

def log_event(event_type: str, payload: Dict[str, Any]):
    """
    Logs an event in structured JSON format for the 'Feedback Loop'.
    Broadcasts to WebSocket clients.
    """
    entry = {
        "timestamp": time.time(),
        "type": event_type,
        "payload": payload
    }
    
    # File Log
    with open(LOG_FILE, "a") as f:
        f.write(json.dumps(entry) + "\n")
        
    # Live Broadcast (fire and forget task)
    try:
        loop = asyncio.get_running_loop()
        loop.create_task(broadcast(entry))
    except RuntimeError:
        # No loop running yet
        pass

# --- WebSocket Server ---
async def websocket_handler(websocket):
    CONNECTED_CLIENTS.add(websocket)
    log_event("system", {"msg": "Client connected", "count": len(CONNECTED_CLIENTS)})
    try:
        async for message in websocket:
            try:
                data = json.loads(message)
                log_event("ws_command", data)
                
                action = data.get("action")
                
                if action == "log":
                    log_event("user_log", {"msg": data.get("payload")})
                elif action == "set_port":
                    port_name = data.get("port")
                    midi_bridge.connect(port_name)
                    await broadcast({"type": "midi_connected", "payload": {"port": midi_bridge.current_port_name}})
                
                elif action == "transport_play":
                    conductor.play()
                elif action == "transport_stop":
                    conductor.stop()
                elif action == "set_style":
                    style = data.get("style", "ambient")
                    conductor.set_style(style)
                    await broadcast({"type": "log", "data": {"msg": f"Style: {style}"}})
                
                elif action == "update_track":
                    track = data.get("track")
                    param = data.get("param")
                    value = data.get("value")
                    res = conductor.update_track(track, param, value)
                    await broadcast({"type": "log", "data": {"msg": res}})
                    await broadcast({"type": "engine_state", "payload": conductor.get_state()})

                elif action == "get_state":
                    await broadcast({"type": "engine_state", "payload": conductor.get_state()})
                    
                # --- AGENTIC COMPOSER BRIDGE ---
                elif action == "analyze":
                    source = data.get("source", "usgs_quake")
                    res = await analyze_data_source(source, "")
                    await broadcast({"type": "analysis_result", "payload": json.loads(res)})
                    await broadcast({"type": "log", "data": {"msg": f"Analysis: {source} complete"}})
                
                elif action == "get_capabilities":
                    caps = conductor.get_capabilities()
                    await broadcast({"type": "capabilities", "payload": caps})
                
                elif action == "configure_identity":
                    bpm = int(data.get("bpm", 120))
                    scale = data.get("scale", "minor")
                    root = int(data.get("root", 60))
                    res = await conductor_set_identity(bpm, scale, root)
                    await broadcast({"type": "log", "data": {"msg": res}})

                elif action == "assign_track":
                    name = data.get("track")
                    gen = data.get("generator")
                    ch = int(data.get("channel", 0))
                    res = await conductor_assign_track(name, gen, ch)
                    await broadcast({"type": "log", "data": {"msg": res}})

                elif action == "update_agent_instruction":
                    text = data.get("text", "")
                    conductor.set_instruction(text)
                    await broadcast({"type": "log", "data": {"msg": "Instruction Sent to Agent"}})

                elif action == "start_recording":
                    conductor.start_recording()
                    await broadcast({"type": "recording", "payload": {"recording": True}})
                    await broadcast({"type": "log", "data": {"msg": "🔴 MIDI Recording started"}})
                
                elif action == "stop_recording":
                    conductor.stop_recording()
                    await broadcast({"type": "recording", "payload": {"recording": False, "notes": len(conductor.recorded_notes)}})
                    await broadcast({"type": "log", "data": {"msg": f"⏹️ Recording stopped. {len(conductor.recorded_notes)} notes captured"}})
                
                elif action == "export_midi":
                    filename = data.get("filename", None)
                    result = conductor.export_midi(filename)
                    await broadcast({"type": "midi_exported", "payload": {"path": result}})
                    await broadcast({"type": "log", "data": {"msg": f"💾 MIDI exported: {result}"}})

                elif action == "test_note":
                    note = data.get("note", 60)
                    midi_bridge.send_note_on(0, note, 100)
                    await asyncio.sleep(0.5)
                    midi_bridge.send_note_off(0, note)
                    
                elif action == "set_playback_mode":
                    mode = data.get("mode", "linear")
                    valid_modes = ["linear", "ordered", "linear_hires", "ordered_hires", "temporal"]
                    if mode in valid_modes:
                        conductor.set_data("playback_mode", mode)
                        # Map mode to buffer key
                        if mode == "linear":
                            buf_key = "playback_buffer_linear"
                        elif mode == "ordered":
                            buf_key = "playback_buffer_ordered"
                        elif mode == "linear_hires":
                            buf_key = "playback_buffer_linear_hires"
                        elif mode == "ordered_hires":
                            buf_key = "playback_buffer_ordered_hires"
                        elif mode == "temporal":
                            buf_key = "playback_buffer_temporal"
                        selected_buf = conductor.data_context.get(buf_key, [])
                        if not selected_buf and mode.endswith("_hires"):
                            # Fallback: generate hi-res on demand
                            base_mode = mode.replace("_hires", "")
                            base_buf = conductor.data_context.get(f"playback_buffer_{base_mode}", [])
                            timeline = conductor.data_context.get("timeline", [])
                            selected_buf = upsample_buffer(base_buf, timeline, factor=10)
                            conductor.set_data(buf_key, selected_buf)
                        conductor.set_data("playback_buffer", selected_buf)
                        await broadcast({"type": "log", "data": {"msg": f"Playback mode: {mode} ({len(selected_buf)} samples)"}})
                        await broadcast({"type": "playback_mode", "payload": {"mode": mode, "buffer_size": len(selected_buf)}})
                    else:
                        await broadcast({"type": "log", "data": {"msg": f"Unknown mode: {mode}. Use: {valid_modes}"}})
                elif action == "analyze_file_upload":
                    filename = data.get("filename", "unknown")
                    content = data.get("content", "")  # Raw bytes/string
                    
                    # NEW: Configurable parameters (with defaults)
                    axis_sample_size = data.get("axis_sample_size", None)
                    buffer_size = data.get("buffer_size", None)
                    enable_hires = data.get("enable_hires", False)
                    hires_factor = data.get("hires_factor", 10)
                    use_timestamps = data.get("use_timestamps", False)  # NEW: Temporal mode
                    
                    print(f"DEBUG: Received Upload. Name={filename} Size={len(content)} UseTimestamps={use_timestamps}", flush=True)
                    
                    # TIMESTAMP PARSING (if enabled)
                    temporal_info = None
                    if use_timestamps:
                        temporal_info = parse_log_timestamps(content)
                        if temporal_info.get("event_count", 0) > 0:
                            print(f"DEBUG: Temporal Parsing: {temporal_info['event_count']} events, {temporal_info['time_range_seconds']:.1f}s span, format={temporal_info['format_detected']}", flush=True)
                            # Create temporal buffer instead of byte-sampling
                            if buffer_size is None:
                                buffer_size = 256  # Default for temporal mode
                            temporal_buffer, temporal_timeline = create_temporal_buffer(
                                temporal_info["events"], 
                                buffer_size=buffer_size
                            )
                            # Store temporal buffers
                            conductor.set_data("playback_buffer_temporal", temporal_buffer)
                            conductor.set_data("timeline_temporal", temporal_timeline)
                            conductor.set_data("temporal_info", {
                                "time_range_seconds": temporal_info["time_range_seconds"],
                                "event_count": temporal_info["event_count"],
                                "format_detected": temporal_info["format_detected"],
                                "first_timestamp": temporal_info.get("first_timestamp"),
                                "last_timestamp": temporal_info.get("last_timestamp"),
                            })
                            
                            # RHYTHMIC MODE: Create divisions from event deltas
                            enable_rhythmic = data.get("enable_rhythmic", False)
                            if enable_rhythmic:
                                rhythmic_score = create_rhythmic_score(temporal_info["events"], buffer_size=buffer_size)
                                conductor.set_data("rhythmic_divisions", rhythmic_score["divisions"])
                                conductor.set_data("playback_buffer_rhythmic", rhythmic_score["buffer"])
                                conductor.set_data("timeline_rhythmic", rhythmic_score["timeline"])
                                
                                # CRITICAL: Enable dynamic tempo modulation in clock loop
                                conductor.set_data("enable_dynamic_tempo", True)
                                log_event("conductor", {"msg": f"Rhythmic score created with {len(rhythmic_score['divisions'])} divisions"})
                                
                                # Assign RhythmicWalker to Bass
                                if "Bass" in conductor.tracks:
                                    conductor.tracks["Bass"].assign_generator(RhythmicWalkerGenerator())
                                    log_event("conductor", {"msg": "Bass track using RhythmicWalkerGenerator"})
                            
                            # HARMONY MODE: Use second axis for Lead
                            enable_harmony = data.get("enable_harmony", False)
                            if enable_harmony and "Lead" in conductor.tracks:
                                conductor.tracks["Lead"].assign_generator(HarmonyWalkerGenerator())
                                log_event("conductor", {"msg": "Lead track using HarmonyWalkerGenerator"})
                            
                            log_event("conductor", {"msg": f"Temporal buffer created: {len(temporal_buffer)} slots, {temporal_info['event_count']} events"})
                        else:
                            print(f"DEBUG: Timestamp parsing failed: {temporal_info.get('error', 'unknown')}", flush=True)
                            use_timestamps = False  # Fall back to byte mode
                    
                    # NYQUIST PRE-ANALYSIS
                    sampling_info = analyze_sampling_needs(content)
                    print(f"DEBUG: Nyquist Analysis: {sampling_info}", flush=True)
                    
                    # Use provided values or Nyquist recommendations
                    if axis_sample_size is None:
                        axis_sample_size = sampling_info["recommended_axis_sample"]
                    if buffer_size is None:
                        buffer_size = sampling_info["recommended_buffer_size"]
                    
                    # Cap buffer size to reasonable max for performance
                    buffer_size = min(10000, buffer_size)
                    
                    if axes:
                        # Run in thread to avoid blocking WebSocket loop (CPU intensive)
                        try:
                            # 2024-05: Limit output metrics to be JSON-safe too?
                            result = await asyncio.to_thread(axes.run_best_axis, content, sample_size=axis_sample_size)
                            
                            # KEEP ordered_stream for ordered playback mode
                            ordered_stream = result.get("ordered_stream", b"")
                            
                            # Clean up heavy data from broadcast (but we've already extracted it)
                            if "ordered_stream" in result:
                                del result["ordered_stream"]
                            
                            # CLEAR STALE BUFFERS
                            conductor.data_context.pop("playback_buffer_axis2", None)
                            conductor.data_context.pop("timeline_axis2", None)
                            
                            # Add suggestion/hint
                            metrics = result.get("metrics", {})
                            entropy = metrics.get("mean_entropy", 8.0)
                            
                            style_to_apply = "ambient"
                            if entropy < 4.0:
                                 result["suggestion"] = "Structured Data. Using Baroque Style."
                                 style_to_apply = "baroque"
                            elif entropy > 7.0:
                                 result["suggestion"] = "Chaotic Data. Using Chaos Style."
                                 style_to_apply = "chaos"
                            else:
                                 result["suggestion"] = "Complex Data. Switching to Ambient."
                                 style_to_apply = "ambient"
                                 
                            
                            # GENERATE DUAL PLAYBACK BUFFERS (with configurable size)
                            preview_len = buffer_size  # Now configurable!
                            
                            # LINEAR BUFFER: Samples the ENTIRE file sparsely
                            step_sz_linear = max(1, len(content) // preview_len)
                            if isinstance(content, str):
                                linear_buffer = [ord(c) for c in content[::step_sz_linear][:preview_len]]
                                content_bytes = content.encode('utf-8', errors='ignore')
                            else:
                                linear_buffer = [b for b in content[::step_sz_linear][:preview_len]]
                                content_bytes = content
                            
                            # ORDERED BUFFER: Use seriation order_indices to reorder ORIGINAL content chunks
                            order_indices = result.get("order_indices", [])
                            window_size = 4096  # Same as axes.py default
                            
                            if order_indices and len(content_bytes) > window_size:
                                sample_size = min(axis_sample_size, len(content_bytes))
                                sample = content_bytes[:sample_size]
                                
                                original_windows = []
                                for i in range(0, len(sample) - window_size + 1, window_size):
                                    original_windows.append(sample[i:i + window_size])
                                
                                valid_indices = [idx for idx in order_indices if idx < len(original_windows)]
                                if valid_indices:
                                    reordered_content = b"".join(original_windows[idx] for idx in valid_indices)
                                    step_sz_ordered = max(1, len(reordered_content) // preview_len)
                                    ordered_buffer = list(reordered_content[::step_sz_ordered][:preview_len])
                                else:
                                    ordered_buffer = linear_buffer
                            else:
                                ordered_buffer = linear_buffer
                            
                            # Get harmony option early (needed for second axis)
                            enable_harmony = data.get("enable_harmony", False)
                            
                            # SECOND AXIS BUFFER (for harmony/Lead track)
                            second_axis = result.get("second_axis")
                            if second_axis and enable_harmony:
                                second_stream = second_axis.get("ordered_stream", b"")
                                if second_stream:
                                    step_sz_axis2 = max(1, len(second_stream) // preview_len)
                                    axis2_buffer = list(second_stream[::step_sz_axis2][:preview_len])
                                    conductor.set_data("playback_buffer_axis2", axis2_buffer)
                                    conductor.set_data("timeline_axis2", second_axis.get("timeline", []))
                                    log_event("conductor", {"msg": f"Axis2 buffer created: {len(axis2_buffer)} samples from '{second_axis.get('second_view', 'unknown')}'"})
                            
                            # HI-RES UPSAMPLING (if enabled)
                            timeline = result.get("timeline", [])
                            if enable_hires:
                                hires_linear = upsample_buffer(linear_buffer, timeline, factor=hires_factor)
                                hires_ordered = upsample_buffer(ordered_buffer, timeline, factor=hires_factor)
                                conductor.set_data("playback_buffer_linear_hires", hires_linear)
                                conductor.set_data("playback_buffer_ordered_hires", hires_ordered)
                                log_event("conductor", {"msg": f"Hi-Res buffers created. Factor={hires_factor}, Size={len(hires_ordered)}"})
                            
                            # Store buffers
                            conductor.set_data("playback_buffer_linear", linear_buffer)
                            conductor.set_data("playback_buffer_ordered", ordered_buffer)
                            conductor.set_data("playback_mode", "ordered")
                            conductor.set_data("playback_buffer", ordered_buffer)
                            
                            print(f"DEBUG: Buffers created. Linear={len(linear_buffer)}, Ordered={len(ordered_buffer)}", flush=True)
                            log_event("conductor", {"msg": f"Dual buffers created. Linear: {len(linear_buffer)}, Ordered: {len(ordered_buffer)}"})
                            
                            # Inject Timeline
                            if timeline:
                                conductor.set_data("timeline", timeline)
                                log_event("conductor", {"msg": f"Timeline Injected. Size: {len(timeline)}"})
                            else:
                                log_event("conductor", {"msg": "No Timeline in Result!"})


                            # AUTO-APPLY TO CONDUCTOR
                            conductor.set_style(style_to_apply)
                            
                            # ASSIGN GENERATORS (respect rhythmic mode if already set)
                            enable_rhythmic = data.get("enable_rhythmic", False)
                            enable_harmony = data.get("enable_harmony", False)
                            
                            # Bass: Use RhythmicWalker if rhythmic mode, else DataWalker
                            if "Bass" in conductor.tracks:
                                if enable_rhythmic and use_timestamps and conductor.data_context.get("rhythmic_divisions"):
                                    conductor.tracks["Bass"].assign_generator(RhythmicWalkerGenerator())
                                    log_event("conductor", {"msg": "Bass track using RhythmicWalkerGenerator (tempo from timestamps)"})
                                else:
                                    conductor.tracks["Bass"].assign_generator(DataWalkerGenerator())
                                    log_event("conductor", {"msg": "Bass track using DataWalkerGenerator"})
                            
                            # Lead: Use Axis2Walker if harmony mode enabled
                            if enable_harmony and "Lead" in conductor.tracks:
                                conductor.tracks["Lead"].assign_generator(Axis2WalkerGenerator())
                                log_event("conductor", {"msg": "Lead track using Axis2WalkerGenerator (2nd best seriation axis)"})
                            
                            log_event("conductor", {"msg": f"Auto-configured style: {style_to_apply}"})

                            # Include sampling_info in result for UI
                            result["sampling_info"] = sampling_info
                            result["actual_axis_sample"] = axis_sample_size
                            result["actual_buffer_size"] = buffer_size
                            
                            # Remove non-JSON-serializable fields before broadcast
                            result_clean = {k: v for k, v in result.items() if k not in ["ordered_stream"]}
                            if "second_axis" in result_clean:
                                result_clean["second_axis"] = {k: v for k, v in result_clean["second_axis"].items() if k not in ["ordered_stream"]}

                            await broadcast({"type": "analysis_result", "payload": result_clean})
                            await broadcast({"type": "engine_state", "payload": conductor.get_state()})
                            await broadcast({"type": "log", "data": {"msg": f"Analysis complete. Buffer={buffer_size}, AxisSample={axis_sample_size}"}})
                        except Exception as e:
                             log_event("error", {"msg": f"Analysis failed: {str(e)}"})
                             await broadcast({"type": "log", "data": {"msg": f"Error Analyzing: {str(e)}"}} )
                    else:
                        await broadcast({"type": "log", "data": {"msg": "Error: Analysis module missing."}})
                    
                elif action == "fetch_tide":
                    res_json = await kernel_fetch_tide()
                    res = json.loads(res_json)
                    await broadcast({"type": "data_fetched", "payload": {"source": "noaa_tide", "data": res}}) 
                    
                    # Update Conductor
                    conductor.set_data("resonance", res['normalized'])
                    log_event("conductor", {"msg": f"Updated Resonance: {res['normalized']}"})
                    
                    # Sonify Tide (Bass Drone)
                    note = int(36 + (res['normalized'] * 24)) # Lower register (C2 - C4)
                    midi_bridge.send_note_on(0, note, 80)
                    async def release_tide():
                        await asyncio.sleep(2.0)
                        midi_bridge.send_note_off(0, note)
                    asyncio.create_task(release_tide())

                elif action == "fetch_quakes":
                    # Fetch Quakes
                    res_json = await kernel_fetch_earthquakes()
                    quakes = json.loads(res_json)
                    
                    if quakes:
                         # Update Conductor State
                         quakes.sort(key=lambda x: x['mag'], reverse=True)
                         max_mag = quakes[0]['mag']
                         normalized_chaos = min(1.0, max_mag / 9.0)
                         conductor.set_data("chaos", normalized_chaos)
                         
                         await broadcast({"type": "data_fetched", "payload": {
                             "source": "usgs_quake", 
                             "data": {"count": len(quakes), "max_mag": max_mag, "chaos": normalized_chaos}
                         }})
                    
                    await broadcast({"type": "log", "data": {"msg": f"Fetched {len(quakes)} Earthquakes", "source": "usgs"}})
                    
                    # Sonify Quakes (Arpeggio Burst)
                    # Sort by magnitude desc
                    quakes.sort(key=lambda x: x['mag'], reverse=True)
                    top_quakes = quakes[:5] # Play top 5
                    
                    for i, q in enumerate(top_quakes):
                        # Map Mag 1-8 to Note 40-90
                        # Bigger mag = Lower rumble, or Higher intensity? 
                        # Let's do Bigger = Louder, Higher Pitch for visibility
                        n_val = int(50 + q['mag'] * 5)
                        vel = int(min(127, 40 + q['mag'] * 15))
                        
                        midi_bridge.send_note_on(0, n_val, vel)
                        
                        # Log specific quake
                        await broadcast({"type": "data_fetched", "payload": {
                            "source": "usgs_quake", 
                            "data": {"place": q['place'], "mag": q['mag']}
                        }})
                        
                        await asyncio.sleep(0.2) # Rapid succession
                        midi_bridge.send_note_off(0, n_val)
                        
                    await broadcast({"type": "log", "data": {"msg": "Quake Sequence Complete"}})

            except Exception as e:
                log_event("ws_error", {"msg": f"Processing error: {str(e)}"})
                import traceback
                traceback.print_exc()

    except Exception as e:
        log_event("ws_disconnect", {"msg": f"Connection lost: {str(e)}"})
    finally:
        CONNECTED_CLIENTS.remove(websocket)
        log_event("system", {"msg": "Client disconnected", "count": len(CONNECTED_CLIENTS)})

async def start_websocket_server():
    print("Starting Willickr MCP Server on ws://0.0.0.0:3001 using 'websockets'...")
    # Increase or disable max_size for large file uploads (default is 1MB)
    async with serve(
        websocket_handler,
        "0.0.0.0",
        3001,
        max_size=None,
        ping_timeout=None, # Disable ping timeout for heavy processing/uploads
        ping_interval=None
    ):
        log_event("system", {"msg": "WebSocket server started on port 3001"})
        await asyncio.Future()  # run forever

# --- 2. MIDI Bridge (Rule #1) ---
class MidiBridge:
    def __init__(self):
        self.midi_outs = [] # List of (rtmidi.MidiOut, port_name) tuples
        self.connected_names = []

    def connect(self, target_port_name=None):
        # Close all existing
        for mout, _ in self.midi_outs:
            mout.close_port()
            del mout
        self.midi_outs = []
        self.connected_names = []

        try:
            # Probe ports using a temporary instance
            temp_out = rtmidi.MidiOut()
            available_ports = temp_out.get_ports()
            del temp_out
            
            if not available_ports:
                log_event("midi_error", {"msg": "No MIDI ports found"})
                return

            # If target specific port
            targets = []
            if target_port_name:
                for i, name in enumerate(available_ports):
                    if target_port_name.lower() in name.lower():
                        targets.append(i)
            else:
                # OMNI MODE: Connect to EVERYTHING safe
                # We want S-1 (hardware) AND Wavetable (Sound)
                # We skip 'Midi Through' to avoid loops if possible, but let's just grab all valid outputs
                for i, name in enumerate(available_ports):
                    targets.append(i)

            for i in targets:
                try:
                    # Create new instance for each port (safe way)
                    mout = rtmidi.MidiOut()
                    mout.open_port(i)
                    name = available_ports[i]
                    self.midi_outs.append((mout, name))
                    self.connected_names.append(name)
                    log_event("midi_connected", {"port": name})
                except Exception as e:
                    log_event("midi_warn", {"msg": f"Failed to open {available_ports[i]}: {e}"})

            if not self.midi_outs:
                log_event("midi_error", {"msg": "Could not open any requested ports"})

        except Exception as e:
            log_event("error", {"component": "midi_bridge", "msg": str(e)})

    @property
    def current_port_name(self):
        if not self.connected_names:
            return "None"
        return ", ".join(self.connected_names)

    def send_note_on(self, channel, note, velocity):
        ch = max(0, min(15, int(channel)))
        n = max(0, min(127, int(note)))
        v = max(0, min(127, int(velocity)))
        self.send_message([0x90 | ch, n, v])

    def send_note_off(self, channel, note):
        ch = max(0, min(15, int(channel)))
        n = max(0, min(127, int(note)))
        self.send_message([0x80 | ch, n, 0])

    def send_control_change(self, channel, cc, value):
        ch = max(0, min(15, int(channel)))
        c = max(0, min(127, int(cc)))
        v = max(0, min(127, int(value)))
        self.send_message([0xB0 | ch, c, v])

    def send_program_change(self, channel, program):
        ch = max(0, min(15, int(channel)))
        p = max(0, min(127, int(program)))
        self.send_message([0xC0 | ch, p])

    def send_message(self, message):
        if not self.midi_outs:
            # Try to auto-connect if disconnected
            self.connect()
        
        sent_any = False
        for mout, name in self.midi_outs:
            try:
                mout.send_message(message)
                sent_any = True
            except Exception as e:
                print(f"Error sending to {name}: {e}")
        
        if sent_any:
            # Decipher for log
            if message[0] & 0xF0 == 0x90: # Note On
                log_event("midi_sent", {"msg": "note_on", "n": message[1], "v": message[2], "ports": len(self.midi_outs)})
            elif message[0] & 0xF0 == 0x80: # Note Off
                log_event("midi_sent", {"msg": "note_off", "n": message[1], "ports": len(self.midi_outs)})
            else:
                log_event("midi_sent", {"msg": "other", "data": message, "ports": len(self.midi_outs)})

# --- 3. Generative Engine ---
import random
import math

# --- Nyquist-Informed Sampling Analysis ---

def analyze_sampling_needs(content: bytes) -> dict:
    """
    Quick scan to determine optimal sampling parameters based on data characteristics.
    Uses a Nyquist-style analysis: sample at 2x the "frequency" of value changes.
    """
    if isinstance(content, str):
        content = content.encode('utf-8', errors='ignore')
    
    file_size = len(content)
    if file_size < 100:
        return {
            "file_size": file_size,
            "characteristic_block_size": 1,
            "recommended_axis_sample": file_size,
            "recommended_buffer_size": file_size,
            "change_rate": 1.0,
        }
    
    # Sample first 50KB to analyze change frequency
    scan_size = min(50000, file_size)
    changes = 0
    threshold = 16  # Value must change by >16 to count as "significant"
    
    for i in range(1, scan_size):
        if abs(content[i] - content[i-1]) > threshold:
            changes += 1
    
    # Characteristic block size = average run length before significant change
    avg_run_length = scan_size / max(1, changes)
    
    # Change rate: 0.0 (static) to 1.0 (every byte changes)
    change_rate = changes / scan_size
    
    # Nyquist-style calculation
    # To capture all significant changes, need samples at 2x the change frequency
    nyquist_samples = int(file_size / max(1, avg_run_length / 2))
    
    # Clamp to reasonable ranges
    recommended_axis = min(2_000_000, max(256_000, nyquist_samples // 10))
    recommended_buffer = min(10_000, max(256, nyquist_samples // 100))
    
    return {
        "file_size": file_size,
        "characteristic_block_size": round(avg_run_length, 2),
        "change_rate": round(change_rate, 4),
        "recommended_axis_sample": recommended_axis,
        "recommended_buffer_size": recommended_buffer,
    }


import re
from datetime import datetime

# --- Timestamp Parsing for Log Files ---

TIMESTAMP_PATTERNS = [
    # ISO format: 2025-01-22T10:30:45 or 2025-01-22 10:30:45
    (r'(\d{4}-\d{2}-\d{2}[T ]\d{2}:\d{2}:\d{2})', '%Y-%m-%dT%H:%M:%S', 'iso'),
    # ISO with space
    (r'(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})', '%Y-%m-%d %H:%M:%S', 'iso_space'),
    # US format: 01/22/2025 10:30:45
    (r'(\d{2}/\d{2}/\d{4} \d{2}:\d{2}:\d{2})', '%m/%d/%Y %H:%M:%S', 'us'),
    # Syslog: Jan 22 10:30:45 (assumes current year)
    (r'(\w{3} +\d{1,2} \d{2}:\d{2}:\d{2})', '%b %d %H:%M:%S', 'syslog'),
    # Epoch seconds: [1705912245] or just 1705912245
    (r'\[?(\d{10})\]?', 'epoch', 'epoch'),
    # Epoch milliseconds
    (r'\[?(\d{13})\]?', 'epoch_ms', 'epoch_ms'),
]


def parse_log_timestamps(content: str, max_lines: int = 10000) -> dict:
    """
    Extract timestamps from log file content.
    
    Returns:
        {
            "events": [(offset_sec, line_entropy, line_content), ...],
            "time_range_seconds": float,
            "event_count": int,
            "format_detected": str,
            "first_timestamp": str,
            "last_timestamp": str,
        }
    """
    if isinstance(content, bytes):
        content = content.decode('utf-8', errors='ignore')
    
    lines = content.split('\n')[:max_lines]
    
    # Detect format by sampling first 10 lines with matches
    detected_format = None
    detected_pattern = None
    detected_strptime = None
    
    for pattern, strptime_fmt, fmt_name in TIMESTAMP_PATTERNS:
        matches = 0
        for line in lines[:50]:
            if re.search(pattern, line):
                matches += 1
        if matches >= 3:  # Need at least 3 matches
            detected_format = fmt_name
            detected_pattern = pattern
            detected_strptime = strptime_fmt
            break
    
    if not detected_format:
        return {
            "events": [],
            "time_range_seconds": 0,
            "event_count": 0,
            "format_detected": None,
            "error": "No timestamp format detected"
        }
    
    # Parse all lines
    events = []
    first_ts = None
    last_ts = None
    
    for i, line in enumerate(lines):
        if not line.strip():
            continue
            
        match = re.search(detected_pattern, line)
        if match:
            ts_str = match.group(1)
            
            try:
                if detected_strptime == 'epoch':
                    ts = datetime.fromtimestamp(int(ts_str))
                elif detected_strptime == 'epoch_ms':
                    ts = datetime.fromtimestamp(int(ts_str) / 1000)
                else:
                    ts = datetime.strptime(ts_str, detected_strptime.replace('T', ' '))
                    # For syslog, add current year
                    if detected_format == 'syslog':
                        ts = ts.replace(year=datetime.now().year)
                
                if first_ts is None:
                    first_ts = ts
                last_ts = ts
                
                # Calculate byte entropy of line
                line_bytes = line.encode('utf-8', errors='ignore')
                if len(line_bytes) > 0:
                    from collections import Counter
                    counts = Counter(line_bytes)
                    probs = [c / len(line_bytes) for c in counts.values()]
                    entropy = -sum(p * (p and math.log2(p)) for p in probs if p > 0)
                else:
                    entropy = 0
                
                offset = (ts - first_ts).total_seconds() if first_ts else 0
                events.append((offset, entropy, line[:100]))  # Truncate line for storage
                
            except (ValueError, OSError):
                continue
    
    if not events:
        return {
            "events": [],
            "time_range_seconds": 0,
            "event_count": 0,
            "format_detected": detected_format,
            "error": "Failed to parse any timestamps"
        }
    
    time_range = events[-1][0] if events else 0
    
    return {
        "events": events,
        "time_range_seconds": time_range,
        "event_count": len(events),
        "format_detected": detected_format,
        "first_timestamp": first_ts.isoformat() if first_ts else None,
        "last_timestamp": last_ts.isoformat() if last_ts else None,
    }


def create_temporal_buffer(events: list, buffer_size: int = 256, target_duration: float = 120.0) -> tuple:
    """
    Create playback buffer where position reflects actual time from events.
    
    Args:
        events: [(offset_sec, entropy, content), ...]
        buffer_size: Target buffer size
        target_duration: Compress all events into this many seconds of playback
    
    Returns:
        (buffer, timeline) where:
        - buffer: list of byte values (entropy * 32) for each slot
        - timeline: list of dicts with entropy and time info
    """
    if not events:
        return [], []
    
    time_range = events[-1][0] if events else 1.0
    if time_range == 0:
        time_range = 1.0  # Avoid division by zero
    
    # Bin events into buffer slots based on time
    buffer = [0] * buffer_size
    timeline = [{"entropy": 0, "event_count": 0, "time_offset": 0} for _ in range(buffer_size)]
    
    slot_counts = [0] * buffer_size
    slot_entropies = [0.0] * buffer_size
    
    for offset, entropy, content in events:
        # Map time offset to buffer slot
        slot = int((offset / time_range) * (buffer_size - 1))
        slot = max(0, min(buffer_size - 1, slot))
        
        slot_counts[slot] += 1
        slot_entropies[slot] += entropy
        
        # Use first byte of content as note value
        if content:
            buffer[slot] = ord(content[0]) if isinstance(content, str) else content[0]
    
    # Normalize and create timeline
    max_count = max(slot_counts) if slot_counts else 1
    
    for i in range(buffer_size):
        if slot_counts[i] > 0:
            avg_entropy = slot_entropies[i] / slot_counts[i]
            # Boost density-high areas (more events = hotter)
            density_factor = slot_counts[i] / max_count
            combined_entropy = (avg_entropy + density_factor * 4) / 2  # Blend entropy + density
            timeline[i] = {
                "entropy": combined_entropy,
                "event_count": slot_counts[i],
                "time_offset": (i / buffer_size) * time_range,
            }
        else:
            timeline[i] = {
                "entropy": 0,
                "event_count": 0,
                "time_offset": (i / buffer_size) * time_range,
            }
    
    return buffer, timeline


# --- Rhythmic Temporal Sonification (Phase 1-4) ---

# Division enum: tick modulo values
DIVISION_SIXTEENTH = 1   # Every tick
DIVISION_EIGHTH = 2      # Every 2nd tick
DIVISION_QUARTER = 4     # Every 4th tick
DIVISION_HALF = 8        # Every 8th tick
DIVISION_WHOLE = 16      # Every 16th tick
DIVISION_TRIPLET = 3     # For triplet feel


def event_delta_to_division(delta_seconds: float) -> int:
    """
    Map time gap between events to musical note division.
    
    Returns tick modulo value for when to play the note.
    """
    if delta_seconds < 0.1:
        return DIVISION_SIXTEENTH  # Very rapid events
    elif delta_seconds < 0.5:
        return DIVISION_EIGHTH
    elif delta_seconds < 2.0:
        return DIVISION_QUARTER
    elif delta_seconds < 8.0:
        return DIVISION_HALF
    else:
        return DIVISION_WHOLE


def compute_note_divisions(events: list) -> list:
    """
    Analyze event timing and compute note divisions for each event.
    
    Args:
        events: [(offset_sec, entropy, content), ...]
    
    Returns:
        List of dicts: [{
            "offset": float,
            "delta": float,  # Time since previous event
            "division": int,  # Tick modulo for this note
            "content": str,
            "entropy": float
        }, ...]
    """
    if not events:
        return []
    
    result = []
    prev_offset = 0.0
    
    for i, (offset, entropy, content) in enumerate(events):
        delta = offset - prev_offset
        division = event_delta_to_division(delta)
        
        result.append({
            "offset": offset,
            "delta": delta,
            "division": division,
            "content": content,
            "entropy": entropy,
        })
        
        prev_offset = offset
    
    return result


def gate_to_harmony(note: int, bass_note: int, scale: list, mode: str = "third") -> int:
    """
    Quantize a note to a harmonically appropriate interval relative to bass.
    
    Args:
        note: Raw MIDI note to harmonize
        bass_note: Current bass note
        scale: List of scale degrees [0, 2, 4, 5, 7, 9, 11] etc.
        mode: "third", "fifth", "sixth", or "random"
    
    Returns:
        Harmonized MIDI note
    """
    # Define harmonic intervals (semitones above bass)
    INTERVALS = {
        "unison": 0,
        "third": 3 if 3 in scale else 4,  # Minor or major third
        "fifth": 7,   # Perfect fifth
        "sixth": 8 if 8 in scale else 9,  # Minor or major sixth
    }
    
    if mode == "random":
        import random
        mode = random.choice(["third", "fifth", "sixth"])
    
    interval = INTERVALS.get(mode, 4)
    
    # Calculate harmony note
    harmony = bass_note + interval
    
    # Clamp to MIDI range
    return max(36, min(96, harmony))


def create_rhythmic_score(events: list, buffer_size: int = 256) -> dict:
    """
    Create a complete rhythmic score from timestamped events.
    
    Returns:
        {
            "notes": [(tick, note, velocity, duration_ticks), ...],
            "divisions": [division_for_each_slot],
            "buffer": [byte_values],
            "timeline": [entropy_info],
        }
    """
    if not events:
        return {"notes": [], "divisions": [], "buffer": [], "timeline": []}
    
    # Compute divisions
    analyzed = compute_note_divisions(events)
    
    time_range = events[-1][0] if events else 1.0
    if time_range == 0:
        time_range = 1.0
    
    # Create buffer and divisions
    buffer = [0] * buffer_size
    divisions = [DIVISION_QUARTER] * buffer_size  # Default to quarter notes
    timeline = [{"entropy": 0, "event_count": 0, "division": 4}] * buffer_size
    
    slot_counts = [0] * buffer_size
    slot_entropies = [0.0] * buffer_size
    slot_divisions = [[] for _ in range(buffer_size)]
    
    for item in analyzed:
        slot = int((item["offset"] / time_range) * (buffer_size - 1))
        slot = max(0, min(buffer_size - 1, slot))
        
        slot_counts[slot] += 1
        slot_entropies[slot] += item["entropy"]
        slot_divisions[slot].append(item["division"])
        
        if item["content"]:
            c = item["content"]
            buffer[slot] = ord(c[0]) if isinstance(c, str) else c[0]
    
    # Average divisions and create timeline
    max_count = max(slot_counts) if slot_counts else 1
    
    for i in range(buffer_size):
        if slot_counts[i] > 0:
            avg_entropy = slot_entropies[i] / slot_counts[i]
            # Use the fastest (smallest) division in dense regions
            avg_division = min(slot_divisions[i]) if slot_divisions[i] else DIVISION_QUARTER
            divisions[i] = avg_division
            
            density_factor = slot_counts[i] / max_count
            timeline[i] = {
                "entropy": (avg_entropy + density_factor * 4) / 2,
                "event_count": slot_counts[i],
                "division": avg_division,
            }
    
    return {
        "buffer": buffer,
        "divisions": divisions,
        "timeline": timeline,
    }


def upsample_buffer(buffer: list, timeline: list, factor: int = 10) -> list:
    """
    Expand buffer using entropy-guided stochastic interpolation.
    
    - Low entropy regions: smooth interpolation with minimal noise
    - High entropy regions: more chaotic transitions
    
    Args:
        buffer: Original 256-sample buffer
        timeline: List of dicts with 'entropy' keys (from axes.py)
        factor: Upsampling factor (10 = 256 -> 2560)
    
    Returns:
        Expanded buffer of length len(buffer) * factor
    """
    if not buffer:
        return []
    
    result = []
    timeline_len = len(timeline) if timeline else 1
    
    random.seed(42)  # Deterministic for reproducibility
    
    for i, val in enumerate(buffer):
        # Get local entropy (normalize 0-8 to 0-1)
        if timeline:
            t_idx = int(i / len(buffer) * timeline_len) % timeline_len
            entropy = timeline[t_idx].get("entropy", 4.0)
        else:
            entropy = 4.0  # Default mid-entropy
        
        noise_scale = min(1.0, entropy / 8.0)  # 0-1 based on entropy
        
        next_val = buffer[(i + 1) % len(buffer)]
        
        for j in range(factor):
            if j == 0:
                result.append(val)
            else:
                # Linear interpolation toward next value
                t = j / factor
                base = val + (next_val - val) * t
                
                # Add entropy-scaled noise
                noise = (random.random() - 0.5) * noise_scale * 40
                interpolated = int(base + noise)
                result.append(max(0, min(255, interpolated)))
    
    return result


class Generator:
    """Base class for algorithmic note generation."""
    def __init__(self):
        self.active = True
    
    def step(self, tick, data_context):
        """Returns list of messages [(type, note, vel), ...] or None"""
        return None

class EuclideanGenerator(Generator):
    """Generates rhythmic patterns using Bjorklund algorithm."""
    def __init__(self, steps=16, pulses=4, root=60, scale=[0, 3, 5, 7, 10]):
        super().__init__()
        self.steps = steps
        self.pulses = pulses
        self.root = root
        self.scale = scale
        self.pattern = self._compute_pattern()
        
    def _compute_pattern(self):
        pattern = [0] * self.steps
        bucket = 0
        for i in range(self.steps):
            bucket += self.pulses
            if bucket >= self.steps:
                bucket -= self.steps
                pattern[i] = 1
        return pattern
        
    def update_params(self, **kwargs):
        if 'pulses' in kwargs: self.pulses = kwargs['pulses']
        if 'steps' in kwargs: self.steps = kwargs['steps']
        if 'root' in kwargs: self.root = kwargs['root']
        self.pattern = self._compute_pattern()

    def step(self, tick, data_context):
        step_idx = tick % self.steps
        if self.pattern[step_idx]:
            # Apply data modulation if available
            mod = 0
            if 'chaos' in data_context:
                mod = int(data_context['chaos'] * 12)
            
            # Pick note from scale
            note_idx = (tick // self.steps) % len(self.scale)
            note = self.root + self.scale[note_idx] + mod
            return [("note_on", note, 100, 0.2)] # Note, Vel, Duration(s)
        return None

class DataWalkerGenerator(Generator):
    """Walks through data values to generate melody."""
    def __init__(self):
        super().__init__()
        self.position = 0 # Integer Index for buffer
    
    def step(self, tick, data_context):
        if tick % 2 != 0: return None # Eighth notes
        
        # Check for Playback Buffer
        buf = data_context.get("playback_buffer", [])
        if buf:
            # Play the data!
            val = buf[self.position % len(buf)]
            self.position += 1
            
            # Map byte (0-255) to MIDI (36-84)
            # Create more variation! 
            # 255 -> 3 octaves (36)
            root_offset = int((val / 255.0) * 36) 
            # Quantize or Chromatic? Let's go Chromatic for raw data feel, or Scale.
            # actually, let's just make it audible.
            note = 36 + root_offset
            
            return [("note_on", note, 100, 0.2)]
            
        else:
            # Legacy Random Walk
            res = data_context.get('resonance', 0.5)
            self.position += 1 # Fake index
            # ... (omitted, fallback)
            return None

class RhythmicWalkerGenerator(Generator):
    """
    Walks through data with rhythmically varying note durations.
    
    Uses divisions from temporal analysis to change note timing:
    - Dense events → faster notes (sixteenth)
    - Sparse events → slower notes (half/whole)
    """
    name = "RhythmicWalker"
    
    def __init__(self):
        super().__init__()
        self.position = 0
    
    def step(self, tick, data_context):
        buf = data_context.get("playback_buffer", [])
        if not buf:
            return None
        
        # Get divisions array (or default to quarter notes)
        divisions = data_context.get("rhythmic_divisions", [])
        
        # Get current division for this position
        pos = self.position % len(buf)
        if divisions and pos < len(divisions):
            current_division = divisions[pos]
        else:
            current_division = DIVISION_QUARTER  # Default
        
        # Only play on tick modulo division
        if tick % current_division != 0:
            return None
        
        # Get the data byte
        val = buf[pos]
        self.position += 1
        
        # Map byte to MIDI note (36-84)
        root_offset = int((val / 255.0) * 36)
        note = 36 + root_offset
        
        # Duration based on division (longer divisions = longer notes)
        duration = 0.1 + (current_division / 16.0) * 0.4  # 0.1-0.5s
        
        return [("note_on", note, 100, duration)]


class Axis2WalkerGenerator(Generator):
    """
    Walks through the SECOND BEST seriation axis data.
    
    This axis is naturally correlated with the primary axis (Bass) because
    it's derived from the same data structure. It produces a second voice
    that harmonizes based on data relationships, not artificial intervals.
    """
    name = "Axis2Walker"
    
    def __init__(self):
        super().__init__()
        self.position = 0
    
    def step(self, tick, data_context):
        # Quarter notes (different rhythm than bass for polyphony)
        if tick % 4 != 0:
            return None
        
        buf = data_context.get("playback_buffer_axis2", [])
        if not buf:
            return None
        
        val = buf[self.position % len(buf)]
        self.position += 1
        
        # Map byte to MIDI note (higher range for Lead: 48-84)
        root_offset = int((val / 255.0) * 36)
        note = 48 + root_offset  # One octave higher than Bass
        
        return [("note_on", note, 85, 0.25)]  # Slightly softer, quarter note duration


class HarmonyWalkerGenerator(Generator):
    """
    Walks through second axis data, gated to harmony intervals.
    
    Follows the bass track and produces consonant intervals.
    """
    name = "HarmonyWalker"
    
    def __init__(self):
        super().__init__()
        self.position = 0
    
    def step(self, tick, data_context):
        # Only play on even ticks (eighth notes)
        if tick % 4 != 0:  # Quarter notes for harmony
            return None
        
        buf = data_context.get("playback_buffer_axis2", [])
        if not buf:
            # Fall back to main buffer
            buf = data_context.get("playback_buffer", [])
        if not buf:
            return None
        
        # Get current bass note (set by DataWalker/RhythmicWalker)
        bass_note = data_context.get("current_bass_note", 48)
        scale = data_context.get("scale", [0, 2, 4, 5, 7, 9, 11])
        
        # Get the byte value
        val = buf[self.position % len(buf)]
        self.position += 1
        
        # Gate to harmony
        # Use the byte value to select harmony mode
        if val < 85:
            mode = "third"
        elif val < 170:
            mode = "fifth"
        else:
            mode = "sixth"
        
        harmony_note = gate_to_harmony(val, bass_note, scale, mode)
        
        return [("note_on", harmony_note, 80, 0.3)]  # Softer velocity for harmony


class ChaoticAttractor(Generator):
    """Lorenz Attractor for organic, evolving modulation."""
    def __init__(self):
        super().__init__()
        self.x, self.y, self.z = 0.1, 0, 0
        self.sigma = 10.0
        self.rho = 28.0
        self.beta = 8.0 / 3.0
        self.dt = 0.01

    def step(self, tick, data_context):
        if tick % 6 != 0: return None # Slower pace
        
        # Integrate Lorenz Equations
        dx = self.sigma * (self.y - self.x)
        dy = self.x * (self.rho - self.z) - self.y
        dz = self.x * self.y - self.beta * self.z
        
        self.x += dx * self.dt
        self.y += dy * self.dt
        self.z += dz * self.dt
        
        # Map to MIDI
        # x (-20 to 20) -> Pitch
        note = int(60 + self.x)
        # z (0 to 50) -> Velocity
        vel = int(min(127, 40 + self.z * 2))
        
        return [("note_on", note, vel, 0.3)]

class MarkovGenerator(Generator):
    """1st Order Markov Chain for style emulation."""
    def __init__(self, style="baroque"):
        super().__init__()
        self.last_note = 60
        self.style = style
        # Transition Matrix: {note_offset: {next_offset: probability}}
        # Simplified: Just relative intervals
        if style == "baroque":
            # Stepwise motion dominant
            self.transitions = {
                -2: [-2, -1, 0, 1], # If went down, likely continue or turn
                -1: [-1, -1, 0, 1],
                0:  [-2, 2, 5, 7],  # Arpeggiate
                1:  [1, 1, 2, 0],
                2:  [2, -1, -2, 0],
            }
        else: # Chaos/Random
             self.transitions = {}

    def step(self, tick, data_context):
        if tick % 4 != 0: return None
        
        # Determine interval
        # Basic implementations just picks a next note based on scale
        scale = [0, 2, 3, 5, 7, 8, 10] # Minor
        
        # Pick interval
        prev_interval = 0
        options = self.transitions.get(prev_interval, [-2, -1, 1, 2])
        interval = random.choice(options)
        
        # Constraints
        next_note = self.last_note + interval
        if next_note < 48: next_note += 12
        if next_note > 84: next_note -= 12
        
        self.last_note = next_note
        return [("note_on", next_note, 90, 0.3)]

class Track:
    def __init__(self, name, channel=0):
        self.name = name
        self.channel = channel
        self.program = 0
        self.generator = None
        self.mute = False
        self.solo = False

    def assign_generator(self, generator):
        self.generator = generator

    def process(self, tick, data_context):
        if self.mute or not self.generator:
            return []
        return self.generator.step(tick, data_context)

class Conductor:
    def __init__(self, midi_bridge):
        self.midi_bridge = midi_bridge
        self.bpm = 120
        self.playing = False
        self.tracks = {}
        self.data_context = {"chaos": 0.0, "resonance": 0.5}
        self.tick = 0
        self._loop_task = None
        
        # Agent Communication
        self.user_instruction = "Compose something based on the data."
        
        # MIDI Recording
        self.recording = False
        self.recorded_notes = []  # [(tick, track_name, note, velocity, duration_ticks)]
        self.record_start_tick = 0
        
        # Initialize Default Tracks
        # Channel 0 = MIDI Ch 1
        # Channel 1 = MIDI Ch 2
        # Channel 2 = MIDI Ch 3
        # Use update_track tool to change these!
        self.tracks["Kick"] = Track("Kick", 0) 
        self.tracks["Bass"] = Track("Bass", 1)
        self.tracks["Lead"] = Track("Lead", 2)
        
        # Global Harmony
        self.scale = [0, 2, 4, 5, 7, 9, 11]
        self.scale_name = "Major"
        self.root_note = 60
        
        self.set_style("ambient")
        self.root_note = 60
        self.scale = [0, 2, 4, 5, 7, 9, 11]
        self.scale_name = "Major"
    
    def start_recording(self):
        """Start recording MIDI notes."""
        self.recording = True
        self.recorded_notes = []
        self.record_start_tick = self.tick
        log_event("conductor", {"msg": "MIDI recording started"})
    
    def stop_recording(self):
        """Stop recording MIDI notes."""
        self.recording = False
        log_event("conductor", {"msg": f"MIDI recording stopped. {len(self.recorded_notes)} notes captured"})
    
    def export_midi(self, filename: str = None) -> str:
        """Export recorded notes to a MIDI file."""
        if MIDIFile is None:
            return "Error: midiutil not installed. Run: pip install midiutil"
        
        if not self.recorded_notes:
            return "Error: No notes recorded"
        
        # Create MIDI file with 3 tracks
        midi = MIDIFile(3)
        track_map = {"Kick": 0, "Bass": 1, "Lead": 2}
        
        # Set tempo
        midi.addTempo(0, 0, self.bpm)
        midi.addTempo(1, 0, self.bpm)
        midi.addTempo(2, 0, self.bpm)
        
        # Add track names
        midi.addTrackName(0, 0, "Kick")
        midi.addTrackName(1, 0, "Bass")
        midi.addTrackName(2, 0, "Lead")
        
        # Ticks to beats (16 ticks = 1 bar = 4 beats)
        ticks_per_beat = 4.0  # 16th notes
        
        for tick, track_name, note, velocity, dur_ticks in self.recorded_notes:
            track_idx = track_map.get(track_name, 1)
            beat_time = (tick - self.record_start_tick) / ticks_per_beat
            beat_duration = dur_ticks / ticks_per_beat
            midi.addNote(track_idx, 0, note, beat_time, beat_duration, velocity)
        
        # Generate filename
        if not filename:
            timestamp = time.strftime("%Y%m%d_%H%M%S")
            filename = f"willickr_export_{timestamp}.mid"
        
        # Ensure output directory exists
        output_dir = os.path.join(os.path.dirname(__file__), "exports")
        os.makedirs(output_dir, exist_ok=True)
        filepath = os.path.join(output_dir, filename)
        
        # Write MIDI file
        with open(filepath, "wb") as f:
            midi.writeFile(f)
        
        log_event("conductor", {"msg": f"MIDI exported: {filepath}", "notes": len(self.recorded_notes)})
        return filepath

    def set_instruction(self, text):
        self.user_instruction = text
        log_event("conductor", {"msg": f"Instruction Updated: {text[:50]}..."})

    # Define Scales as Class Constant
    SCALES = {
        "major": [0, 2, 4, 5, 7, 9, 11],
        "minor": [0, 2, 3, 5, 7, 8, 10],
        "pentatonic_major": [0, 2, 4, 7, 9],
        "pentatonic_minor": [0, 3, 5, 7, 10],
        "whole_tone": [0, 2, 4, 6, 8, 10],
        "chromatic": [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11],
        "harmonic_minor": [0, 2, 3, 5, 7, 8, 11],
        "dorian": [0, 2, 3, 5, 7, 9, 10], # Added Dorian
        "lydian": [0, 2, 4, 6, 7, 9, 11], # Added Lydian
    }
    
    # Define Generator Types
    GENERATOR_TYPES = ["euclidean", "markov", "chaos", "lorenz", "walk", "random"]

    def get_capabilities(self):
        """Returns the capabilities of the engine."""
        return {
            "scales": list(self.SCALES.keys()),
            "generators": self.GENERATOR_TYPES,
            "max_tracks": 8,
            "can_fetch_data": ["quakes", "tides", "weather", "market"] # Future proofing
        }

    def get_state(self):
        """Returns the current engine state for UI."""
        track_states = {}
        for name, track in self.tracks.items():
            track_states[name] = {
                "name": name,
                "mute": track.mute,
                "solo": track.solo,
                "channel": track.channel,
                "generator": track.generator.name if track.generator else "None"
            }
            
        return {
            "playing": self.playing,
            "bpm": self.bpm,
            "scale": self.scale_name,
            "root": self.root_note,
            "tracks": track_states,
            "connection": "online"
        }

    def create_generator(self, gen_type, **kwargs):
        """Factory for creating generators by name."""
        gt = gen_type.lower()
        if "euclid" in gt: return EuclideanGenerator(**kwargs)
        if "markov" in gt: return MarkovGenerator(**kwargs)
        if "chaos" in gt or "lorenz" in gt: return ChaoticAttractor()
        if "walk" in gt: return DataWalkerGenerator()
        return None

    def quantize(self, note_val):
        """Snaps a note to the nearest valid scale degree."""
        # Adjust to global root note
        relative_note = note_val - self.root_note
        
        octave = relative_note // 12
        pitch_class = relative_note % 12
        
        # Find closest scale note
        closest_scale_degree = min(self.scale, key=lambda x: abs(x - pitch_class))
        
        # Reconstruct note with global root and clamp to MIDI range
        return max(0, min(127, self.root_note + octave * 12 + closest_scale_degree))

    def set_global_scale(self, root_note, scale_name):
        scale_key = scale_name.lower()
        if scale_key in self.SCALES:
            self.root_note = root_note
            self.scale = self.SCALES[scale_key]
            self.scale_name = scale_name
            log_event("conductor_scale_set", {"root": root_note, "scale": scale_name})
            return f"Global scale set to {scale_name} with root {root_note}."
        return f"Scale '{scale_name}' not recognized. Available: {', '.join(self.SCALES.keys())}"
        
    def set_style(self, style_name):
        if style_name == "chaos":
            self.tracks['Kick'].assign_generator(EuclideanGenerator(16, 7, 36)) # Dense pulse
            self.tracks['Lead'].assign_generator(ChaoticAttractor())
            self.tracks['Bass'].assign_generator(DataWalkerGenerator())
            self.scale = [0, 2, 4, 6, 8, 10] # Whole Tone (Dreamy/Unsettled)
            self.scale_name = "Whole Tone"
        elif style_name == "baroque":
            self.tracks['Kick'].assign_generator(EuclideanGenerator(16, 4, 36)) # Steady pulse
            self.tracks['Lead'].assign_generator(MarkovGenerator("baroque"))
            self.tracks['Bass'].assign_generator(EuclideanGenerator(16, 8, 48))
            self.scale = [0, 2, 3, 5, 7, 8, 11] # Harmonic Minor
            self.scale_name = "Harmonic Minor"
        else: # Ambient
            self.tracks['Kick'].assign_generator(EuclideanGenerator(16, 2, 36)) # Sparse pulse
            self.tracks['Lead'].assign_generator(EuclideanGenerator(16, 5, 72))
            self.tracks['Bass'].assign_generator(DataWalkerGenerator())
            self.scale = [0, 2, 3, 5, 7, 8, 10] # Natural Minor
            self.scale_name = "Natural Minor"
            
        log_event("conductor", {"msg": f"Style: {style_name}, Scale: {self.scale_name}"})

    def set_data(self, key, value):
        self.data_context[key] = value

    def play(self):
        if self.playing: return
        self.playing = True
        self.tick = 0
        self._loop_task = asyncio.create_task(self._clock_loop())
        log_event("transport", {"state": "playing", "bpm": self.bpm})

    def stop(self):
        self.playing = False
        if self._loop_task:
            self._loop_task.cancel()
        # All Notes Off
        for i in range(16):
            self.midi_bridge.send_message([0xB0 | i, 123, 0]) # All Notes Off
        log_event("transport", {"state": "stopped"})

    async def _clock_loop(self):
        try:
            while self.playing:
                start_time = time.time()
                
                # sixteenth note duration
                step_dur = 60.0 / self.bpm / 4.0
                
                # --- DYNAMIC CONDUCTOR ---
                # Calculate Playback Position and Read Timeline
                timeline = self.data_context.get("timeline", [])
                pb_buf = self.data_context.get("playback_buffer", [])
                buf_len = len(pb_buf) if pb_buf else 256
                
                # Loop position (0.0 to 1.0)
                loop_idx = self.tick % buf_len
                pct = loop_idx / float(buf_len)
                
                if timeline:
                    # Map position to timeline window
                    t_idx = int(pct * len(timeline))
                    t_idx = min(t_idx, len(timeline) - 1)
                    window = timeline[t_idx]
                    
                    # Update Context with current metrics
                    self.data_context['current_entropy'] = window.get('entropy', 0)
                    self.data_context['current_view_index'] = window.get('view_index', 0)
                    
                    # --- DYNAMIC TEMPO MODULATION ---
                    # Change BPM on bar boundaries (every 16 ticks = 1 bar in 4/4)
                    if self.tick % 16 == 0 and self.data_context.get("enable_dynamic_tempo", False):
                        # Get current division or event density
                        divisions = self.data_context.get("rhythmic_divisions", [])
                        event_count = window.get("event_count", 1)
                        current_div = window.get("division", 4)  # Default quarter note
                        
                        if divisions and loop_idx < len(divisions):
                            current_div = divisions[loop_idx]
                        
                        # Map division to BPM: smaller division = faster tempo
                        # QUANTIZED to musical ratios relative to base 120 BPM
                        # div 1 (sixteenth) → 180 BPM (1.5x)
                        # div 2 (eighth) → 150 BPM (1.25x)
                        # div 4 (quarter) → 120 BPM (1.0x)
                        # div 8 (half) → 90 BPM (0.75x)
                        # div 16 (whole) → 60 BPM (0.5x)
                        BPM_MAP = {
                            1: 180,   # Sixteenth → fast
                            2: 150,   # Eighth
                            3: 140,   # Triplet
                            4: 120,   # Quarter → normal
                            8: 90,    # Half → slow
                            16: 60    # Whole → very slow
                        }
                        
                        target_bpm = BPM_MAP.get(current_div, 120)
                        
                        # Smooth transition: don't jump more than 30 BPM per bar
                        if abs(target_bpm - self.bpm) > 30:
                            if target_bpm > self.bpm:
                                self.bpm = min(target_bpm, self.bpm + 30)
                            else:
                                self.bpm = max(target_bpm, self.bpm - 30)
                        else:
                            self.bpm = target_bpm
                        
                        print(f"DEBUG: BPM→{self.bpm} (div={current_div}, events={event_count})", flush=True)
                    
                    # Debug Log (Every 16 ticks)
                    if self.tick % 64 == 0:
                        print(f"DEBUG: Tick={self.tick} Idx={t_idx} Ent={window.get('entropy', 'UNK')} BPM={self.bpm}", flush=True)

                    
                    # OPTIONAL: Dynamic Style Modulation
                    # If entropy is extremely high, temporarily boost Chaos Generator probability?
                    # For now, we trust the Global Style set by 'analyze_file_upload'
                    pass
                
                # Process Tracks
                for t_name, track in self.tracks.items():
                    events = track.process(self.tick, self.data_context)
                    if events:
                        for evt in events:
                            # evt: (type, note, vel, dur)
                            if evt[0] == "note_on":
                                # QUANTIZE HERE
                                raw_note = evt[1]
                                q_note = self.quantize(raw_note)
                                
                                self.midi_bridge.send_note_on(track.channel, q_note, evt[2])
                                
                                # MIDI RECORDING
                                if self.recording:
                                    dur_ticks = int(evt[3] / (60.0 / self.bpm / 4.0))  # Convert seconds to ticks
                                    self.recorded_notes.append((self.tick, t_name, q_note, evt[2], dur_ticks))
                                
                                # Schedule Note Off
                                asyncio.create_task(self._schedule_note_off(track.channel, q_note, evt[3]))
                
                # Broadcast Clock UI
                if self.tick % 4 == 0: # Beat
                    # Send additional dynamic info
                    payload = {"tick": self.tick, "bpm": self.bpm}
                    if "current_entropy" in self.data_context:
                         payload["entropy"] = self.data_context["current_entropy"]
                         payload["progress"] = self.data_context.get("playback_position", (self.tick % 256)/256.0) # Approx
                         # Actually calculate pct again here to be safe
                         buf_len = len(self.data_context.get("playback_buffer", [])) or 256
                         payload["progress"] = (self.tick % buf_len) / float(buf_len)
                         
                    await broadcast({"type": "clock", "payload": payload})

                self.tick += 1
                
                # Drift Correction Sleep
                elapsed = time.time() - start_time
                await asyncio.sleep(max(0, step_dur - elapsed))
                
        except asyncio.CancelledError:
            pass
        except Exception as e:
            log_event("error", {"src": "conductor", "msg": str(e)})

    async def _schedule_note_off(self, ch, n, dur):
        await asyncio.sleep(dur)
        self.midi_bridge.send_note_off(ch, n)
        
    def get_state(self):
        return {
            "bpm": self.bpm,
            "playing": self.playing,
            "style": self.scale_name, # Using scale_name as a proxy for style
            "root_note": self.root_note,
            "scale": self.scale,
            "tracks": {name: {"mute": t.mute, "solo": t.solo, "channel": t.channel, "program": t.program, "generator": t.generator.__class__.__name__ if t.generator else "None"} for name, t in self.tracks.items()}
        }
    
    def update_track(self, name, param, value):
        if name in self.tracks:
            t = self.tracks[name]
            if param == "mute": t.mute = bool(value)
            elif param == "solo": t.solo = bool(value)
            elif param == "channel": t.channel = int(value)
            elif param == "program": 
                t.program = int(value)
                self.midi_bridge.send_program_change(t.channel, t.program)
            log_event("conductor_track_update", {"track": name, "param": param, "value": value})
            return f"Track {name} {param} set to {value}"
        return f"Track {name} not found."


midi_bridge = MidiBridge()
conductor = Conductor(midi_bridge)

# --- 4. WebSocket Server & MCP ---
app = FastMCP("Willickr Engine")

@app.tool()
async def list_midi_ports() -> List[str]:
    """Returns a list of available MIDI output ports."""
    midi_bridge.available_ports = midi_bridge.midi_out.get_ports()
    return midi_bridge.available_ports

@app.tool()
async def set_midi_port(port_name: str) -> str:
    """Switches the active MIDI output port. Returns the name of the connected port."""
    if not port_name:
        return "No port name provided"
    
    midi_bridge.connect(target_port_name=port_name)
    return f"Connected to {midi_bridge.current_port_name}"

@app.tool()
async def play_test_note(note: int = 60, velocity: int = 100, duration: float = 0.5, channel: int = 1):
    """Fires a single note to verify the connection.
    Args:
        note: MIDI note number (0-127, 60 is C4)
        velocity: Strike velocity (0-127)
        duration: Length in seconds
        channel: MIDI Channel (1-16)
    """
    log_event("tool_call", {"tool": "play_test_note", "note": note, "channel": channel})
    
    # Convert 1-16 to 0-15
    ch_idx = max(0, min(15, channel - 1))
    
    midi_bridge.send_note_on(ch_idx, note, velocity)
    await asyncio.sleep(duration)
    midi_bridge.send_note_off(ch_idx, note)
    
    return f"Played note {note} on Channel {channel} ({midi_bridge.current_port_name})"

@app.tool()
async def panic():
    """Stops all notes and resets checking."""
    log_event("tool_call", {"tool": "panic"})
    # MIDI Panic (All Notes Off on all channels)
    if midi_bridge.connected:
        for ch in range(16):
            midi_bridge.midi_out.send_message([0xB0 | ch, 123, 0]) # All Notes Off
    return "Panic signal sent."

from kernel.image_processor import ImageProcessor
from kernel.generators import Generator

# --- 4. Math Kernel State ---
img_proc = ImageProcessor()

@app.tool()
async def kernel_load_image(path: str) -> str:
    """
    Loads an image into the Math Kernel for analysis.
    Args:
        path: Absolute path to the image file.
    """
    res = img_proc.load_image(path)
    log_event("kernel_img_load", {"path": path, "res": res})
    return str(res)

@app.tool()
async def kernel_scan_image(y_percent: float) -> str:
    """
    Scans a horizontal line of the loaded image.
    Returns JSON string with brightness/saturation arrays.
    Args:
        y_percent: 0.0 to 1.0
    """
    try:
        data = img_proc.scanline(y_percent)
        # return summary to avoid blowing up token context if huge
        # Agent can request sampling if needed. For now return full list but truncate in log?
        log_event("kernel_scan", {"y": y_percent, "len": data["len"]})
        return json.dumps(data)
    except Exception as e:
        return f"Error: {e}"

@app.tool()
async def kernel_generate_rhythm(steps: int, pulses: int) -> List[int]:
    """Generates a Euclidean rhythm pattern (Bjorklund)."""
    pat = Generator.euclidean_rhythm(steps, pulses)
    log_event("kernel_gen", {"algo": "euclidean", "pat": pat})
    return pat

@app.tool()
async def kernel_grid_to_notes(grid_x: int, grid_y: int, scale_root: int = 60, scale: str = "minor") -> List[Dict[str, Any]]:
    """
    Samples the loaded image in a grid and converts cell brightness to MIDI notes.
    Returns list of {x, y, note, velocity}.
    """
    try:
        cells = img_proc.grid_stats(grid_x, grid_y)
        
        # Extract brightnesses
        brights = [c["brightness"] / 255.0 for c in cells]
        
        # Quantize
        notes = Generator.quantize_to_scale(brights, scale_root, scale)
        
        result = []
        for i, note in enumerate(notes):
            cell = cells[i]
            # Use Red channel for velocity?
            vel = int(cell["r"])
            vel = max(30, min(120, vel))
            
            result.append({
                "step_index": i, 
                "x": cell["x"], "y": cell["y"],
                "note": note, 
                "velocity": vel
            })
            
        log_event("kernel_grid_notes", {"count": len(result)})
        return result
    except Exception as e:
        log_event("error", {"msg": str(e)})
        return []

@app.tool()
async def search_references(query: str = "") -> List[Dict[str, str]]:
    """
    Searches the internal knowledge base of sonification techniques/references.
    Args:
        query: Keyword to filter by (e.g., 'sonification', 'twotone'). Empty returns all.
    """
    try:
        ref_path = "data/references.json"
        # Handle path relative to script execution or absolute
        import os
        if not os.path.exists(ref_path):
             # Try absolute path based on __file__
             ref_path = os.path.join(os.path.dirname(__file__), "data", "references.json")
             
        with open(ref_path, "r") as f:
            refs = json.load(f)
            
        if not query:
            return refs
            
        return [r for r in refs if query.lower() in r.get("title", "").lower() or query.lower() in r.get("description", "").lower()]
    except Exception as e:
        log_event("error", {"tool": "search_references", "msg": str(e)})
        return []

@app.tool()
async def kernel_fetch_tide(station_id: str = "8518750") -> str:
    """
    Fetches real-time water level from NOAA Tides & Currents.
    Returns JSON with water level and normalized value (0-1).
    Args:
        station_id: NOAA Station ID (default: The Battery, NY)
    """
    import urllib.request
    
    url = f"https://api.tidesandcurrents.noaa.gov/api/prod/datagetter?product=water_level&station={station_id}&date=latest&datum=MLLW&units=english&time_zone=lst_ldt&format=json"
    
    try:
        # Run blocking IO in executor to avoid freezing the async loop
        def fetch():
            with urllib.request.urlopen(url) as response:
                return json.loads(response.read().decode())
        
        loop = asyncio.get_running_loop()
        data = await loop.run_in_executor(None, fetch)
            
        if 'error' in data:
            return json.dumps({"error": data['error']})
            
        observation = data['data'][0]
        water_level = float(observation['v'])
        
        # Normalize (assuming -2 to 8 range)
        norm = (water_level + 2.0) / 10.0
        norm = max(0.0, min(1.0, norm))
        
        result = {
            "station": station_id,
            "time": observation['t'],
            "level": water_level,
            "normalized": norm
        }
        
        log_event("data_fetched", {"source": "noaa_tide", "data": result})
        return json.dumps(result)

    except Exception as e:
        err = {"error": str(e)}
        log_event("error", {"src": "noaa", "msg": str(e)})
        return json.dumps(err)

@app.tool()
async def kernel_fetch_earthquakes() -> str:
    """Fetches significant earthquake data from USGS (last 30 days)."""
    url = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/significant_month.geojson"
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(url) as response:
                if response.status == 200:
                    data = await response.json()
                    feats = data.get("features", [])
                    # Extract Mag and Place
                    simplified = [{"mag": f["properties"]["mag"], "place": f["properties"]["place"]} for f in feats]
                    return json.dumps(simplified[:50]) # Limit to 50
    except Exception as e:
        log_event("error", {"tool": "fetch_earthquakes", "msg": str(e)})
        return "[]"

@app.tool()
async def transport_play() -> str:
    """Starts the music engine."""
    conductor.play()
    return "Transport: Playing"

@app.tool()
async def transport_stop() -> str:
    """Stops the music engine."""
    conductor.stop()
    return "Transport: Stopped"

@app.tool()
async def conductor_set_identity(bpm: int, scale: str, root: int) -> str:
    """
    Sets the global musical identity of the engine.
    scale options: major, minor, pentatonic_major, pentatonic_minor, whole_tone, harmonic_minor.
    root: MIDI note number (e.g., 60 is Middle C).
    """
    conductor.bpm = bpm
    res = conductor.set_global_scale(root, scale)
    await broadcast({"type": "engine_state", "payload": conductor.get_state()})
    return f"Conductor Identity Set: {bpm} BPM, {res}"

@app.tool()
async def conductor_assign_track(track_name: str, generator_type: str, midi_channel: int) -> str:
    """
    Assigns a generator (algorithm) and MIDI channel to a track.
    generator_type: 'euclidean', 'markov', 'chaos', 'walker'.
    existing tracks: 'Kick', 'Bass', 'Lead'.
    """
    if track_name not in conductor.tracks:
        return f"Error: Track '{track_name}' does not exist."
    
    gen = conductor.create_generator(generator_type)
    if not gen:
        return f"Error: Generator type '{generator_type}' unknown."
        
    conductor.tracks[track_name].assign_generator(gen)
    conductor.tracks[track_name].channel = midi_channel
    
    # Unmute if it was muted
    conductor.tracks[track_name].mute = False
    
    await broadcast({"type": "engine_state", "payload": conductor.get_state()})
    return f"Track '{track_name}' assigned '{generator_type}' on Channel {midi_channel}."

@app.tool()
async def analyze_data_source(source_type: str, uri: str) -> str:
    """
    Analyzes a data source to return musical metadata using Generic Series Analysis.
    source_type: 'noaa_tide', 'usgs_quake', 'file'.
    Returns: JSON with entropy, segments, best_view, and structural metrics.
    """
    raw_data = None
    
    # 1. Ingestion Layer
    if source_type == "noaa_tide":
        raw_data = await kernel_fetch_tide() # Returns JSON string
    elif source_type == "usgs_quake":
        raw_data = await kernel_fetch_earthquakes() # Returns JSON string
    elif source_type == "file":
        # Placeholder for file reading if implemented
        return "File access not yet enabled via MCP."
    else:
        return "Unknown source type."

    # 2. Generic Analysis Layer
    if axes:
        # Pass raw string (or bytes) to axes discovery
        # It handles conversion to bytes internally if string
        result = axes.run_best_axis(raw_data, sample_size=100000)
        
        # We can drop the 'ordered_stream' (bytes) from output to keep JSON small
        # The agent mainly needs the metrics and segments.
        if "ordered_stream" in result:
            del result["ordered_stream"] # Too large to pass as text
            
        # Add legacy hint/suggestion to help transition
        metrics = result.get("metrics", {})
        entropy = metrics.get("mean_entropy", 8.0)
        if entropy < 4.0:
            result["suggestion"] = "Highly structured/repetitive. Use Markov or Euclidean."
        elif entropy > 7.0:
            result["suggestion"] = "High entropy/chaos. Use Lorenz or Random Walk."
        else:
            result["suggestion"] = "Balanced structure. Good for Melodic/Walking."
            
        return json.dumps(result, cls=json.JSONEncoder)
    
    else:
        # Fallback to legacy hardcoded logic if axes script missing
        if source_type == "noaa_tide":
             data = json.loads(raw_data)
             return json.dumps({
                 "value": data.get("v"),
                 "normalized": data.get("normalized"), 
                 "suggestion": "Low frequency drone (Legacy Fallback)."
             })
        elif source_type == "usgs_quake":
             data = json.loads(raw_data)
             return json.dumps({
                 "count": len(data),
                 "suggestion": "Chaotic bursts (Legacy Fallback)."
             })
        return "Analysis module missing."

@app.tool()
async def conductor_get_capabilities() -> str:
    """
    Returns the capabilities of the Willickr Generative Engine.
    Use this to discover available Scales, Generator Types, and other constants.
    """
    caps = conductor.get_capabilities()
    return json.dumps(caps, indent=2)

@app.tool()
async def conductor_get_agent_protocol() -> str:
    """
    Returns the 'Agentic Conductor Protocol' (System Prompt).
    Use this to understand your role, capabilities, and the required sequence of operations.
    """
    try:
        # Assuming run from 'server' dir
        path = os.path.join("data", "agent_protocol.md")
        if not os.path.exists(path):
            return "Protocol file not found."
        with open(path, "r") as f:
            return f.read()
    except Exception as e:
        return f"Error reading protocol: {e}"

@app.tool()
async def conductor_get_technical_manual() -> str:
    """
    Returns the 'Technical Manual' describing the engine's architecture and signal flow.
    Use this to understand polyphony, timing, and how data affects generation.
    """
    try:
        path = os.path.join("data", "technical_manual.md")
        if not os.path.exists(path):
            return "Manual file not found."
        with open(path, "r") as f:
            return f.read()
    except Exception as e:
        return f"Error reading manual: {e}"

@app.tool()
async def conductor_post_instruction(text: str) -> str:
    """Post a high-level instruction for the Conductor/Agent to follow."""
    if not conductor:
        return "Error: Conductor not initialized."
    conductor.set_instruction(text)
    return f"Instruction updated: {text}"

@app.tool()
async def conductor_get_user_instruction() -> str:
    """Get the current high-level instruction from the user."""
    if not conductor:
        return "Error: Conductor not initialized."
    return conductor.user_instruction

if __name__ == "__main__":
    import threading
    
    # 1. Initialize MIDI
    midi_bridge.connect()
    
    # 2. Start WebSocket Server in a separate thread
    def run_websocket_thread():
        # Create a new loop for this thread to avoid FastMCP conflict
        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        try:
            loop.run_until_complete(start_websocket_server())
        except Exception as e:
            # If server fails, just log it to file (logging might not be safe across threads if not carefully done, but open() is)
            with open(LOG_FILE, "a") as f:
                f.write(json.dumps({"type": "error", "payload": str(e)}) + "\n")

    ws_thread = threading.Thread(target=run_websocket_thread, daemon=True)
    ws_thread.start()
    
    # 3. Run MCP Server (blocks main thread stdio)
    app.run()
