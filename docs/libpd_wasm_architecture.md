# Phase V: Engine B (libpd.wasm Architecture)

## The Limitation of Native Tone.js & WebPd

To execute Gordon Reid's complex, chaotic physical models (like `FIRE` and `WIND`), Willickr initially explored two web-based solutions:
1.  **Tone.js Rewrite**: Flawless for additive synthesis (Bells) but incapable of modeling the 1-sample feedback loops and non-linear analog filter topologies required for environmental physics in a browser without extremely complex WebAudio AudioWorklet C++ rewrites.
2.  **WebPd Compiler**: A tool that attempts to transpile `.pd` text schematics into JavaScript/AssemblyScript. This failed because it is an alpha project that does not yet support fundamental Pure Data physics objects like the `[env~]` envelope follower.

## The Ultimate Solution: `libpd` in WebAssembly

Instead of translating the Pure Data schematic into a new language, we will compile the literal **C-language source code of Pure Data** into a WebAssembly (`.wasm`) binary using Emscripten.

`libpd` is the official C-engine of Pure Data, stripped of its GUI. When compiled to WASM, it runs natively inside the browser (or a headless Node.js Puppeteer shell).

### Why this is the Holy Grail:
1.  **100% Object Support**: Because it is the literal Pure Data C-engine running in memory, it natively supports `[env~]`, `[catch~]`, `[throw~]`, and every other chaotic math object Gordon Reid uses. If it runs in desktop Pure Data, it runs in the browser.
2.  **Web Deployment Phase**: By encapsulating `libpd.wasm` inside Engine B, the Willickr Orchestrator can seamlessly trigger complex generative audio environments locally during development *and* universally when deployed as a Web Application later.

## Architectural Flow

1.  **The Python Router**: `audio_looper.py` reads `track_names.json`. If a track is assigned `Engine: libpd` and `Patch: fire_all.pd`, it launches the headless Node shell.
2.  **The Headless Shell**: `render_libpd.js` launches a Chromium Puppeteer instance.
3.  **WASM Initialization**: The browser loads `libpd.wasm` and initializes it inside an `AudioWorkletNode`.
4.  **Audio Context Processing**: The literal C-code of Pure Data receives `pd.sendFloat("velocity", 110)` via the JavaScript bridge, calculates the chaotic audio float arrays, and passes the output buffer back up to the WebAudio API.
5.  **The Offline Bounce**: The `OfflineAudioContext` mathematically renders 45 seconds of the output, encodes it to a `.wav` Data URI, and saves it to the local project folder.
6.  **Digital Mixdown**: The Python router mixes the `fire_test.wav` with the hardware S-1 tracks via NumPy.
