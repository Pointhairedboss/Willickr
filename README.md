# Willickr

**Willickr** is an intelligent, node-graph-driven multitrack audio synthesis pipeline. It provides a visual block-based interface for drag-and-drop algorithmic composition, seamlessly routing MIDI data and generative musical patches through either attached hardware (like a Roland AIRA S-1) or headless browser-based offline renderers (Tone.js / libpd). 

## Features

- **Dynamic Pipeline Construction:** A React Flow node-canvas allowing you to link discrete MIDI Files, generative algorithmic `Cartridges`, and Output Engines together visually.
- **Universal Parameter Ontology:** Modify abstract semantic parameters like `Loudness`, `SpectralCentroid`, `RoomSize`, and `ModulationRate` directly on the graph via dynamic sliders. The backend automatically translates these to standardized hardware MIDI CCs globally.
- **Modular Output Engines:** 
  - **Hardware (S-1):** Live real-time playback routing out to a physical USB MIDI device and recording back via its USB Audio interface.
  - **Headless Offline (Tone.js / libpd):** Virtual software synthesizers that render algorithmic patches in-memory via headless instances without occupying physical hardware.
- **Automated Mixdown:** The backend API autonomously normalizes, stereophonically aligns, and mixes the multi-track render jobs into one master `.wav` file presented synchronously to the frontend track timeline.

## Project Structure & Architecture

Willickr utilizes a hybrid stack Architecture:
- `web/` - A modern React + Vite graphical interface. Features an intelligent floating asset library that queries the backend to hydrate available plugins, an interactive LLM simulation chat, and the core Visual Node Mapping interface using `@xyflow/react`.
- `server/` - A centralized Python FastAPI backend application that acts as the coordinator.
  - `willickr_api.py`: Manages REST routes, dynamic file indexing (`/assets`), and parallel multi-track rendering jobs. Handles mixing down temp `.wav` channels via `numpy` and `soundfile`.
  - `kernel/engine_router.py`: Handles execution threading for both real-time S-1 audio recording capture loops (`sounddevice`) and virtual memory dumps to offline `node.js` scripts.
  - `kernel/Stories/`: Contains all of the generative Algorithmic preset patches—written as `BaseCartridges` that encapsulate specific acoustic and procedural logic (the Syntheory catalog).

## Setup Instructions

### Prerequisites
- Python 3.10+
- Node.js v18+ 
- A connected USB Hardware Synthesizer supporting MIDI CC (Built iteratively around the Roland S-1, but can be dynamically directed).

### 1. Boot the Backend (Python FastAPI)

Navigate to the `server/` directory and install its external requirements:
```bash
cd server
pip install -r requirements.txt
```
*(Dependencies generally include `fastapi`, `uvicorn`, `rtmidi`, `mido`, `sounddevice`, `soundfile`, `numpy`)*

Launch the Python server:
```bash
uvicorn willickr_api:app --reload
```
This will run the routing engine locally at `http://127.0.0.1:8000`.

### 2. Prepare Tone.js Headless Components (Optional but Recommended)
For software rendering capabilities, ensure the Node dependencies are populated in the sub-engine layer:
```bash
cd server/engine_b_tonejs
npm install puppeteer
```

### 3. Boot the Frontend Interface (React JS)

In a new terminal, navigate into the main `web/` folder, install JS packages, and boot the frontend dev server:
```bash
cd web
npm install
npm run dev
```

### Flow Walkthrough

1. Open your browser to the local `Vite` address (typically `localhost:5173`).
2. Explore the Floating Asset Library on the right sidebar containing your Indexed `.mid` traces and generative Python Algorithm Cartridges.
3. Drag inputs and algorithms onto the dark Canvas.
4. Drag a DAW Mixdown node into the center and connect your pathways.
5. Choose an Audio Engine (e.g., S-1 or ToneJS).
6. Press the **EXECUTE PIPELINE NOW** button. The frontend will generate a structured JSON payload interpreting the visual connections and ship it to the `FastAPI` server. 
7. Sit back as the routing engine sequentially tracks down channels and compiles the master mixdown.
