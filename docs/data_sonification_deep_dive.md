# Advanced Data Sonification: Architecture, Math, and Engineering

This document expands on the theoretical foundations of data sonification by providing the exact mathematical implementations and architectural patterns required to build a production-grade sonification system. 

It is designed so that a software engineer can read this and immediately reconstruct a system like Google's [TwoTone](https://github.com/sonifydata/twotone) or algorithmic composers like [Image2Music](https://github.com/brihijoshi/Image2Music).

---

## 1. System Architecture of a Sonification App

Whether you are building a web-based "Data DAW" (like TwoTone) or an offline Python rendering script, the architecture is nearly identical. A robust sonification system separates data ingestion from audio synthesis using a "Mapping Engine."

### The 4-Stage Pipeline
1.  **Data Ingestion & Normalization**: The system reads raw JSON/CSV data. Every numerical column is immediately normalized to a `[0.0, 1.0]` float scale. *This is critical—the audio engine must never know if it is processing 1,000,000 population count or 0.05 temperature variance.*
2.  **The Playhead (Transport)**: A global clock (Transport) ticks forward at a set BPM (Beats Per Minute) or Hz rate. If the dataset has 365 rows, the Transport iterates from `index = 0` to `index = 364`.
3.  **The Mapping Engine**: For the current `index`, the Mapping Engine reads the normalized `[0.0, 1.0]` values and applies a mathematical transform to convert them into Acoustic Units (Hz for frequency, dB for volume, Pan for space).
4.  **The Audio Engine**: The system sends standard control signals (like `triggerAttackRelease(frequency, duration, velocity)`) to a Synthesizer, Sampler, or MIDI-Out node.

---

## 2. The core Mathematics: Scaling Functions

You cannot map data to sound linearly. Hearing is logarithmic. The following functions are required in the Mapping Engine to correctly translate the `[0.0, 1.0]` normalized data into human-perceivable audio.

### A. Parameter Mapping: Logarithmic Frequency
If you map data linearly to Hertz (e.g., $0.0 \rightarrow 100\text{Hz}$, $1.0 \rightarrow 1000\text{Hz}$), a $0.5$ data value will play at $550\text{Hz}$. To the human ear, $550\text{Hz}$ sounds much "higher" than the midpoint. We perceive pitch logarithmically.

To map data so that it sounds perceptually linear to the listener, you must use **Exponential Scaling**:

$$ f_{target} = f_{min} \times \left( \frac{f_{max}}{f_{min}} \right)^{x_{norm}} $$

*   **$f_{max}$ / $f_{min}$**: The minimum and maximum frequencies of your synthesizer (e.g., 50Hz to 2000Hz).
*   **$x_{norm}$**: Your normalized data value `[0.0, 1.0]`.

**TypeScript Implementation:**
```typescript
function getPerceptualFrequency(normalizedData: number, minFreq: number, maxFreq: number): number {
    return minFreq * Math.pow((maxFreq / minFreq), normalizedData);
}
```

### B. Parameter Mapping: Quantized Musical Scales (The TwoTone Approach)
Raw logarithmic frequencies sound alien. Almost all popular sonification tools (like TwoTone) use **Scale Quantization**. Instead of mapping to raw Hertz, the `[0.0, 1.0]` value is mapped an index in an array of specific MIDI notes (e.g., C Harmonic Minor).

$$ \text{Index} = \lfloor x_{norm} \times (N_{notes} - 1) \rfloor $$

Using MIDI notes solves the logarithmic problem automatically, because the MIDI standard itself maps note integers to frequencies logarithmically (MIDI Note 60 is Middle C = 261.63Hz; MIDI Note 69 is A4 = 440Hz).

**Python Implementation:**
```python
import math

# A C Minor Pentatonic scale spread across 3 octaves (MIDI note numbers)
SCALE = [36, 39, 41, 43, 46, 48, 51, 53, 55, 58, 60, 63, 65, 67, 70]

def get_midi_note(normalized_data):
    # Clamp to [0.0, 1.0] just in case
    val = max(0.0, min(1.0, normalized_data))
    
    # Map to array index
    max_index = len(SCALE) - 1
    index = math.floor(val * max_index)
    
    return SCALE[index]

def midi_to_freq(midi_note):
    return 440.0 * math.pow(2.0, (midi_note - 69.0) / 12.0)
```

### C. Parameter Mapping: Decibel Loudness (Stevens' Power Law)
If you map data `[0.0, 1.0]` directly to synthesizer amplitude multiplier `[0.0, 1.0]`, the audio will sound abruptly loud and then barely change. Human loudness perception is described by Stevens' Power Law with an exponent of roughly $0.6$ or by standard Decibel (dB) scaling.

To map data to a perceived volume slider smoothly:
$$ \text{Amplitude}_{multiplier} = (x_{norm})^{2.0} \quad \text{(or up to } 3.0 \text{ for dramatic dynamic range)} $$

Alternatively, mapping to dB for Tone.js or professional DAWs:
```javascript
// Map 0.0 -> -60dB (silence), 1.0 -> 0dB (max volume)
function getDecibels(normalizedData) {
    if (normalizedData <= 0.01) return -Infinity; // Mute
    const minDb = -60;
    const maxDb = 0;
    // Linear interpolation works here because dB is ALREADY a logarithmic scale!
    return minDb + (normalizedData * (maxDb - minDb)); 
}
```

---

## 3. Engineering a Complete Flow: The "TwoTone" Clone Strategy

If you want to recreate a fully functional, multi-instrument data sonification app like TwoTone, you need three discrete code modules running in a loop.

### Module 1: The Dataset Store
Load your CSV. Extract the `min` and `max` for every column. Store a normalized version of the dataset in memory.

```javascript
// State
const columnsInfo = {
    temperature: { min: -10, max: 40 },
    windSpeed: { min: 0, max: 150 }
};

const tracks = [
    { column: 'temperature', instrument: 'piano', scale: 'C_Minor' },
    { column: 'windSpeed', instrument: 'synth_drone', scale: 'Modulation' }
];

let currentIndex = 0; // The playhead
```

### Module 2: The Scheduling Loop (Tone.js / Transport)
In WebAudio, you cannot use a simple `setInterval`, as it drifts due to JS single-threading. You must use `Tone.Transport` or an offline script loop.

```javascript
import * as Tone from 'tone';

const piano = new Tone.Sampler({ urls: { "C4": "C4.mp3" } }).toDestination();
const drone = new Tone.FMSynth().toDestination();
drone.triggerAttack("C2"); // Starts playing immediately

// This loop runs EXACTLY every 8th note
Tone.Transport.scheduleRepeat((time) => {
    const row = normalizedDataset[currentIndex];
    
    tracks.forEach(track => {
        if (track.instrument === 'piano') {
            // Technique B: Musical Scale Mapping
            const midiNote = getMidiNote(row[track.column], scales[track.scale]);
            const freq = Tone.Frequency(midiNote, "midi");
            
            // Schedule the note stroke perfectly on the AudioThread 'time'
            piano.triggerAttackRelease(freq, "8n", time);
        }
        
        if (track.instrument === 'synth_drone') {
            // Technique A/C: Parameter Modulation (Continuous Sound)
            // Wind speed modulates the harmonicity of the FM synth
            const harmonicity = 0.5 + (row[track.column] * 5.0);
            
            // Smoothly ramp the value over 0.2 seconds so it doesn't "click"
            drone.harmonicity.rampTo(harmonicity, 0.2, time);
        }
    });

    currentIndex++;
    if (currentIndex >= normalizedDataset.length) Tone.Transport.stop();
}, "8n");
```

### Module 3: Export and Render (MidiOut)
A true sonification app shouldn't just play audio; it should export MIDI so composers can use the data in Ableton or Logic.

For offline rendering (like the `Image2Music` Python scripts), you accumulate these events into a MIDI file rather than playing them live.

```python
from midiutil import MIDIFile

# Create a 2-track MIDI file
midi = MIDIFile(2)
midi.addTempo(0, 0, 120)

for time_index, row in enumerate(normalized_dataset):
    temp_norm = row['temperature']
    wind_norm = row['windSpeed']
    
    # Track 0: Temperature mapped to Piano notes
    midi_note = get_midi_note(temp_norm)
    midi.addNote(track=0, channel=0, pitch=midi_note, time=time_index, duration=1, volume=100)
    
    # Track 1: Wind mapped to Continuous Controller (CC / Modulation Wheel)
    # MIDI CC values are integers from 0 to 127
    cc_value = int(wind_norm * 127)
    midi.addControllerEvent(track=1, channel=1, time=time_index, controller_number=1, parameter=cc_value)

with open("sonification_export.mid", "wb") as output_file:
    midi.writeFile(output_file)
```

## Conclusion Summary
To recreate any of the major open-source sonification projects, the core engineering requirement is mastering the **Mapping Engine**. 

You must break data away from its raw values, normalize it to `[0.0, 1.0]`, and then selectively apply logarithmic frequency math (for raw pitch), integer array indexing (for musical scales), and exponent/dB math (for volume envelops). Whether built in React/Tone.js or pure Python, this architecture remains identical.
