# Prespec-Willickr: The AI-Augmented Generative Studio

## 1. Vision
**Willickr** is not an AI that writes music. It is a **computational instrument** that allows the user to perform "Data Alchemy." It leverages the **Antigravity Agent** as a conductor to translate disparate data sources—satellite imagery, text streams, topological maps, mathematical functions—into musical information (MIDI, Automation, Audio) in real-time.

The goal is to move from "programming notes" to "sculpting data," using Tracktion Waveform and hardware synths (Roland S-1) as the acoustic output engine.

## 1.1 Philosophy: Visibility is Intelligence
This project is a demonstration of AI-Human augmentation. Cruical to this success is the **Feedback Loop**.
*   **Instrument Everything**: The Agent must be able to "see" what it is doing. We do not fire into the void.
*   **Real-Time Review**: Logs, visualizers, and status updates must be available to both the User and the Agent in near-real-time.
*   **Self-Correction**: The system architecture must allow the Agent to read the state of the "Loom" or the MCP server logs to correct course if the music generation drifts.

## 1.2 Reference Library (Knowledge Base)
To prevent "reinventing the wheel," Willickr maintains a dynamic database of sonification techniques and external references (stored in `docs/REFERENCES.md` and `server/data/references.json`).
The MCP server exposes tools to query this knowledge base (`search_references`), allowing the Agent to "study" prior art (like TwoTone) before implementing new translation modes.

The system consists of three distinct interacting layers:

### Layer 1: The Orchestrator (Antigravity)
*   **Role**: The creative director and coder.
*   **Input**: Natural language instructions ("Take this weather map and play the storm front as a bassline").
*   **Action**: Writes code (Python/JS) to process data, invokes MCP tools to execute playback, and configures the environment.

### Layer 2: The Engine (Willickr MCP Server)
The heavy lifter. A Python-based server exposing tools for:
*   **DAW Control**: Transport, Track Arming, Recording (via key injection).
*   **Midi Bridge**: Direct generation and streaming of MIDI data to virtual ports.
*   **Math Kernel**: A suite of algorithms (FFT, Perlin Noise, Markov Chains, Image Analysis) to crunch data.

### Layer 3: The Loom (Interactive Web Interface)
*   **Role**: The visual feedback and performance surface.
*   **Tech**: React + Three.js / p5.js.
*   **Function**:
    *   Visualizes the input data (e.g., the 3D terrain being played).
    *   Provides "XY Pads" and "Sliders" that the Agent can hook up to parameters.
    *   Real-time feedback of what the algorithmic engine is doing.

---

## 3. The "Vocabulary" of Translation
Core to Willickr is the concept of **Translation Modes**—strategies for converting non-musical data into musical events.

### 3.1 Topological & Spatial (Image/3D to Music)
*   **Scanline Synthesis**: converting an image into sound by scanning pixel brightness/hue as pitch/velocity over time.
    *   *App*: Satellite weather maps -> Cloud density controls reverb wetness; storm eye proximity controls LFO rate.
*   **Terrain Walker**: An agent "walks" across a 3D heightmap.
    *   *Altitude* = Pitch
    *   *Slope* = Note Duration
    *   *Terrain Roughness* = Filter Cutoff
*   **Feature Extraction**: using Computer Vision (OpenCV) to identify objects (e.g., edges, circles) and triggering events when they intersect.

### 3.2 Spectral & Mathematical
*   **FFT Translation**: Analyze an audio file or data stream frequency content and map significant bins to chord voicings.
*   **Chaotic Attractors**: Using Lorenz or Rossler attractors to generate modulation curves for synth parameters (Filter, Resonance).

### 3.3 Text & Structural
*   **N-Gram/Markov**: Digesting a text file to generate rhythmic patterns based on syllable structure.
### 3.4 Real-Time Streams (API to Audio)
*   **Astronomy**: Satellite TLE data (CelesTrak) and Constellation coordinates (AstronomyAPI) mapped to orbital LFOs and spatial panning.
*   **Seismic/Geological**: USGS Earthquake feeds where Magnitude = Amplitude and Depth = Reverb.
*   **Weather/Tides**: Open-Meteo data for wind speed (noise generation) and tide height (slow modulation).
*   **Public Transport**: PTV Disruption data for "Urban Dirges" (e.g., tram outages triggering minor chords).
*   **NOAA Scientific**: Space weather (Solar flares -> Distortion) and Global Carbon trends (CO2 -> Drone pitch).

---

## 4. Component Specifications

### 4.1 MIDI & Audio Interaction (The "Output Stage")
We skirt the limitations of UI automation by using standard protocols.
*   **Virtual MIDI Cable (loopMIDI)**: The MCP server sends MIDI messages (Note On/Off, CC) to a virtual port. Waveform listens to this port and routes it to the Roland S-1.
*   **OSC (Open Sound Control)**: For high-resolution parameter control if supported, or bridging to other visualizers.

**New Capabilities:**
*   `play_sequence(notes, quantization)`: Fire a computed sequence.
*   `stream_cc_curve(cc_number, duration, curve_function)`: Send smooth automation data.
*   `sync_clock()`: Ensure Python logic aligns with Waveform's BPM.

### 4.2 The Web "Loom"
A local web app (Next.js/Vite) running at `localhost:3000`.
*   **Canvas**: A main viewport rendering the "Data Subject" (e.g., the image or 3D mesh).
*   **Cursors**: Visual indicators showing where the "Playhead" currently is on the data.
*   **Controls**: Agent-configurable UI elements. "Agent, add a slider for 'Chaos' and link it to the probability of the drum pattern."

### 4.3 DAW Control (Legacy Spec)
Retained for capture and arrangement.
*   `Record`, `Stop`, `Arm Track`, `Save` functionality via keyboard shortcuts remains crucial for *capturing* the generative performance.

---

## 5. Workflow Scenarios

**Scenario A: The Weather Player**
1.  **User**: "Download the latest infrared map of the Pacific Ocean."
2.  **Agent**: Fetches image, displays it on the Loom.
3.  **User**: "Scan across the equator. Map heat to distortion amount and cloud cover to note density."
4.  **Agent**: Writes a Python script using the Math Kernel to sample the image pixels.
5.  **Execution**: The script runs, streaming MIDI notes to the S-1.
6.  **Capture**: User calls `record_for(60)` to capture the result in Waveform.

**Scenario B: The Text Drummer**
1.  **User**: "Load this poem. Create a drum pattern where vowels are kicks and constants are snares."
2.  **Agent**: Parses text, generates a MIDI sequence.
3.  **User**: "Too rigid. Apply a swing groove based on a sine wave function."
4.  **Agent**: Remaps the timing arrays.
5.  **Execution**: Plays the beat.

---

## 6. Implementation Roadmap

### Phase 1: Foundation (The Skeleton)
*   [ ] Set up Python MCP Server + loopMIDI connection.
*   [ ] Verify basic "Send Note" -> Waveform -> S-1 audio path.
*   [ ] Basic Transport Control (Record/Stop) via shortcuts.

### Phase 2: The Loom (The Eyes)
*   [ ] Build basic React scaffolding.
*   [ ] Create a WebSocket bridge between Python MCP and React frontend.
*   [ ] Implement simple 2D Image visualizer.

### Phase 3: The Brain (Math Kernel)
*   [ ] Implement `ImageProcessor` class (PIL/OpenCV).
*   [ ] Implement `Generator` class (Euclidean rhythms, Noise functions).

### Phase 4: Integration
*   [ ] Connect the Agent: "Write a script that uses the ImageProcessor to drive the Generator."

---

## 7. Project Rules (Non-Negotiable)
These rules govern the development lifecycle of Willickr.

1.  **Establish Foundations First**: Define toolsets, libraries, plugins, reference implementations, and architectural design early. Do not build on shifting sand.
2.  **Risk-First Development**: Prioritize elements with high technical risk (SWEBOK principle). Tackle the "hard parts" (e.g., stable MIDI timing from Python) first.
3.  **Prototype Explicitly**: When uncertainty exists, build standalone prototypes in `prototypes/`. These are disposable experiments to validate a theory effectively.
4.  **Instrument Everywhere**: Every major component (MCP, Generators, Web UI) must emit structured logs or events. Visibility is not an addon; it is a core requirement.
5.  **Documentation is Contract**: These instruction are recorded here and in `PROJECT_RULES.md`. Mistakes made by ignoring these rules are unacceptable.