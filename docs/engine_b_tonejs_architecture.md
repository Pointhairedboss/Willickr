# Phase V Experiment: Dual-Engine Architecture (S-1 + Tone.js)

## Executive Summary
To execute procedurally complex physical models (like Gordon Reid's Pure Data patches for Bells, Fire, Wind, etc.), Willickr requires an additive software synthesis core ("Engine B"). This experiment outlines the deployment of a **Web Audio API (Tone.js)** engine running within the `willickr-concept.jsx` React app, handling the computational load the monotimbral Roland S-1 hardware cannot process.

## The Dual-Engine Router Concept
The Willickr Orchestrator (Python) must act as a **Router** during the MIDI-to-WAV multitrack process outlined in `s1_offline_bounce_workflow.md`. 

During **Phase 2: Patch Assignment**, the router intercepts track requirements:
1. **Engine A Routing (S-1):** Tracks requesting Level 1 Analog Primitives (`[Origin: Brass]`, `[Origin: Bow]`) are assigned to `rtmidi` and queued for the hardware audio looper.
2. **Engine B Routing (Tone.js):** Tracks requesting Level 1 Software Primitives (`[Origin: Additive-Bell]`, `[Origin: Procedural-Fire]`) are assigned to the browser. The Router transmits the isolated MIDI track data and patch configuration via WebSocket to the running React application.

## The Tone.js Experiment: The Additive Bell
To validate this architecture, we will translate the `BOOK-PUREDATA/BELL/A4-bell-telephone.pd` patch into JavaScript.

**Objective:**
Replicate the strict additive layout of the Pure Data bell using Tone.js within the React frontend.
- Initialize `Tone.js` within a hidden React component.
- Generate an array of 9 `Tone.Oscillator` nodes correctly tuned to the complex inharmonic ratios of bell overtones.
- Assign 9 independent `Tone.Envelope` nodes, giving the fundamental a long decay while the "strike" partials decay almost instantly.
- Expose a listener for a `Trigger` event from the Python backend.

## Pipeline Integration (Offline Mixdown Parity)
The most critical requirement of Engine B is that it must yield `.wav` files perfectly synchronized with the S-1 hardware tracking.

To achieve parity with `s1_offline_bounce_workflow.md`:
1. **The Bounce Command:** Python sends a WebSocket payload containing the isolated MIDI sequence for the Bell track and a command to "Offline Render".
2. **Offline Rendering:** The React app utilizes `Tone.Offline(callback, duration)`. This executes the entire Tone.js performance instantly in a web worker *without* playing it through the user's speakers, returning a completed `AudioBuffer`.
3. **Data Return:** The React application converts the `AudioBuffer` to a standard `.wav` Blob and POSTs it back to the local Python server.
4. **Digital Mixdown:** The Python backend receives `engine_b_bell.wav` and drops it seamlessly into the **Phase 4** NumPy summation array alongside the `engine_a_bass.wav` recorded from the S-1.

Because `Tone.Offline` guarantees rendering from absolute `0.00s`, the software primitive and the hardware primitive will sum perfectly in phase.
