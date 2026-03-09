# Willickr: The Universal Parameter Ontology

The true power of Willickr as a unified system relies on abstracting away the complex, engine-specific technical parameters (MIDI CC numbers for S-1, C++ float messages for WASM) into a **Universal Musical Ontology**.

## 1. The Problem
*   **S-1 Hardware:** Changing the "brightness" requires sending MIDI CC `74` (Filter Cutoff).
*   **WASM (Wind Model):** Changing the "brightness" might require sending a float value to the `high_frequency_damping` math node.
*   **User/AI Intention:** The user just wants the sound to be "Brighter". They do not want to know about MIDI CCs or C++ variable names.

## 2. The Semantic Foundation (Macro Controls)

We establish a unified layer of **Macro Controls**. These are human-readable, universally understood musical dimensions, co-opting existing Web Semantic standards:
1.  **Music Ontology (`mo:`):** Structural concepts (`mo:Key`, `mo:Tempo`, `mo:Genre`).
2.  **Audio Features Ontology (`afo:`):** Perceptual descriptions.

### Proposed Core Macros (The "Dials"):
*   **Intensity:** (`afo:Loudness` / `afo:Energy`) - drive, volume, velocity.
*   **Timbre (Brightness/Color):** (`afo:SpectralCentroid`) - Filter cutoff, harmonic content, noise ratio.
*   **Density / Sparsity:** (`afo:ZeroCrossingRate` / `mo:NoteDensity`) - Event probability, note density, granular spawn rate.
*   **Motion / Modulation:** (`afo:ModulationRate`) - LFO depth, wind turbulence, tremolo rate.
*   **Space (Environment):** (`afo:RoomSize`) - Reverb depth, delay feedback, physical room size.
*   **Tonal Center (Key/Scale):** (`mo:Key`) - MIDI root note, generative scale constraint, physics fundamental frequency.

---

## 3. The Implementation: The Translation Schema

To make this work, every single Willickr "Cartridge" (whether it's an S-1 Python patch or a WASM physics model) must be able to accept these Ontological definitions as generic inputs (usually `0.0` to `1.0` normalized) and translate them into their specific hardware/math engine constraints.

### Example A: A Roland S-1 Patch (`gamma_k_tonewheel.json`)
When the script receives `afo:SpectralCentroid = 0.8`, the backend/script translates that into turning the S-1's filter knob (CC 74) to ~101.
```json
{
  "name": "Gamma Tonewheel",
  "engine": "S1",
  "mappings": {
    "afo:SpectralCentroid": {
      "target": "midi_cc",
      "parameter": 74,
      "range_min": 0,
      "range_max": 127
    },
    "afo:RoomSize": {
      "target": "midi_cc",
      "parameter": 91, 
      "range_min": 0,
      "range_max": 127
    }
  }
}
```

### Example B: A Pure Data WASM Physics Model (`dark_storm.json`)
When the user/LLM provides the exact same `afo:SpectralCentroid = 0.8` to the WASM model, the system sends floating-point messages to the C++ headless browser.
```json
{
  "name": "Dark Storm Environment",
  "engine": "libpd_wasm",
  "mappings": {
    "afo:Loudness": {
      "target": "pd_receive",
      "parameter": "storm_velocity",
      "range_min": 0.0,
      "range_max": 100.0
    },
    "afo:SpectralCentroid": {
      "target": "pd_receive",
      "parameter": "thunder_lpf_cutoff",
      "range_min": 200,
      "range_max": 8000
    }
  }
}
```
