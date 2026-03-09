# Data Sonification Systems: Taxonomy, Libraries, and Techniques

This document catalogs the state-of-the-art in open-source data sonification as observed across GitHub. It provides a taxonomy of systems, highlights the core libraries powering them, and includes abstract code patterns for building these systems.

---

## 1. Taxonomy of Data Sonification Systems

Data sonification projects generally fall into four primary categories based on their goals and execution environments:

### A. Web-Based Analytical Synthesizers (The \"Web DAW\" approach)
* **Goal**: Provide a GUI for users to upload datasets (CSV, JSON) and map data columns to audio properties (pitch, volume, tempo, instrument) in the browser.
* **Examples**: `twotone` (by sonifydata), `data-audio-workstation`
* **Key Characteristic**: Operates entirely client-side using WebAudio for immediate feedback and interactivity.

### B. Programmatic Offline Renderers (The \"Scripting\" approach)
* **Goal**: Convert complex datasets (images, environmental data, seismology) into audio files or MIDI sequences via headless scripts.
* **Examples**: `Image2Music`, `image-2-melody`, `seismic2midi`
* **Key Characteristic**: Uses heavy data-processing languages (Python, R) to generate intermediate formats (MIDI, OSC) or render directly to audio files (WAV). It favors precision and complex mappings over real-time interactivity.

### C. Live / Real-Time Environmental Monitors (The \"Installation\" approach)
* **Goal**: Ingest live data streams (weather, air quality, stock market) and continuously generate an evolving ambient soundscape.
* **Examples**: `Two-Neighborhoods--Air-Quality-Data-Sonification`, `signal-from-dust`
* **Key Characteristic**: Runs as a daemon or background process. Often maps data to abstract, ambient synth parameters rather than distinct \"notes\" to avoid listener fatigue.

### D. DAW Integrations / Creative Tools
* **Goal**: Bridge the gap between data and professional music production tools (Ableton, Logic).
* **Examples**: `SoniZen`
* **Key Characteristic**: Built as plugins (Max for Live, VSTs) or MIDI generators. The sonification system outputs control signals (MIDI/OSC) while the DAW handles the actual sound design and mixing.

---

## 2. Core Libraries & Ecosystems

Almost all projects rely on a few dominant ecosystems, largely split between Web (JavaScript/TypeScript) and Offline (Python).

### WebAudio Ecosystem (JavaScript/TypeScript)
* **`Tone.js`**: The absolute undisputed king of web sonification. It wraps the native WebAudio API to provide synthesizers, effects, and musical timing abstractions (BPM, Transport). Used heavily in projects like `GitSymphony` and `signal-from-dust`.
* **`midi-writer-js`** / **`browser-id3-writer`**: Used by apps like `twotone` to allow users to export their web-synthesized data maps as standard MIDI or tagged MP3/WAV files for use in professional DAWs.

### Python Ecosystem
* **`midiutil`** / **`mido`** / **`midi2audio`**: The standard toolkit for mapping data arrays (like earthquake magnitudes) to MIDI notes and velocities.
* **`pedalboard`** (by Spotify): Used in projects like `image-2-melody` for applying professional-grade VSTs and audio effects (reverb, compression) to generated audio directly in Python scripts.
* **`FoxDot`** & **`SuperCollider`**: Used for algorithmic composition. Python (via FoxDot) sends OSC messages to SuperCollider (the audio engine) to generate complex, non-standard synthesizers based on data matrices (like image pixels).

### Academic / Audio Engines
* **`Csound`**: Used in `datasonification` by `eviau`. An intensely powerful, text-based modular synthesis language. Excellent for granular control, but has a steep learning curve.
* **`Max/MSP`** (Max for Live): Used in `SoniZen`. A visual programming language ideal for routing data into Ableton Live parameters.

---

## 3. Core Techniques & Code Patterns

Regardless of the language or ecosystem, the fundamental challenge of sonification is the **mapping function**: converting an arbitrary data range into a musical range.

### Technique A: Linear Pitch Mapping (The standard approach)
The most common technique. It takes a data value (e.g., Temperature 20°C to 40°C) and maps it linearly to a range of MIDI notes (e.g., C2 to C5).

*Abstract Code Pattern (JavaScript/Tone.js):*
```javascript
// Mapping arbitrary values to a specific octave range
function mapDataToFrequency(value, minData, maxData, minFreq = 100, maxFreq = 1000) {
    // Normalize data between 0 and 1
    const normalized = (value - minData) / (maxData - minData);
    // Scale to frequency range
    return minFreq + (normalized * (maxFreq - minFreq));
}

// Example usage mapping air quality index (AQI) to a synth drone frequency
const aqiValue = 150; 
const freq = mapDataToFrequency(aqiValue, 0, 500, 55, 440);
synth.setNote(freq);
```

### Technique B: Constrained Scale Mapping (The \"Musical\" approach)
Linear mapping often sounds chaotic and atonal. To make data sound \"good\", developers snap the mapped values to a specific musical scale (e.g., C Minor pentatonic).

*Abstract Code Pattern (Python / MIDI):*
```python
# A C Minor Pentatonic scale mapped across a few octaves
SCALE_NOTES = [36, 39, 41, 43, 46, 48, 51, 53, 55, 58]

def map_to_scale(data_val, data_min, data_max):
    # Normalize data
    normalized = (data_val - data_min) / (data_max - data_min)
    
    # Find the corresponding index in our musical scale
    max_index = len(SCALE_NOTES) - 1
    target_index = int(round(normalized * max_index))
    
    return SCALE_NOTES[target_index]

# Example: Mapping earthquake magnitude (1.0 - 9.0) to a musical note
midi_note = map_to_scale(magnitude, 1.0, 9.0)
add_midi_note(track=0, channel=0, pitch=midi_note, time=current_time, duration=1, volume=100)
```

### Technique C: Parameter Modulation (The \"Ambient\" approach)
Instead of triggering new notes for every data point, a single continuous drone is played. The data modulates parameters like filter cutoff, LFO rate, or reverb saturation over time. This is widely used in environmental sonification.

*Abstract Code Pattern (Tone.js Context):*
```javascript
// A continuous drone
const drone = new Tone.FMSynth().toDestination();
const filter = new Tone.Filter(400, "lowpass").toDestination();
drone.connect(filter);
drone.triggerAttack("C2");

function onNewDataRow(data) {
    // Wind Speed modulates the filter cutoff frequency (makes it brighter)
    const newCutoff = mapDataToFrequency(data.windSpeed, 0, 100, 200, 5000);
    filter.frequency.rampTo(newCutoff, 0.5); // Smoothly ramp over 0.5s
    
    // Traffic density modulates the harmonicity of the FM synth (makes it grittier)
    const grit = mapData(data.trafficDensity, 0, 1000, 1, 10);
    drone.harmonicity.rampTo(grit, 0.5);
}
```

## Summary
The current landscape of data sonification leans heavily on **Tone.js** for interactive web experiences and **Python (MIDI/SciPy)** for offline rendering. The most crucial aesthetic decision developers make is whether to use strict linear mapping (which represents data truthfully but often sounds terrible) or constrained scale mapping (which sounds musical but inherently quantizes and smooths the underlying data).
