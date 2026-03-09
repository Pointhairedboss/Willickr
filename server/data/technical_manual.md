# Willickr Engine: Technical Manual

## 1. Core Architecture
Willickr is a **Real-Time Generative Engine**, not a batch file renderer.
*   **Clock Loop**: The `Conductor` runs an asynchronous loop triggered by `transport_play`.
*   **Granularity**: The loop ticks at 16th-note intervals.
*   **Immediacy**: Generators are queried *per tick*. Any change to global state (Scale, Chaos Level) or Track configuration is reflected **immediately** in the very next generated note. It is designed for live performance.

## 2. Polyphony & Voices
The engine defaults to **3 Concurrent Voices** (Tracks), routed to separate MIDI channels:
1.  **Kick (Channel 1)**: Rhythmic foundation.
2.  **Bass (Channel 2)**: Harmonic grounding.
3.  **Lead (Channel 3)**: Melodic narrative.

*Each Track operates independently with its own assigned Generator.*

## 3. Signal Flow
1.  **Data In**: External data (e.g., Earthquake Mag 7.0) is pushed to the `Conductor.data_context`.
2.  **Context**: The Conductor updates global parameters (BPM, Scale) and broadcasting the data context to all tracks.
3.  **Generation**: At each tick, active Generators (Lorenz, Markov) calculate the next note based on the *current* context.
4.  **Quantization**: The generated raw value is snapped to the Global Scale (e.g., Whole Tone) to ensure harmonic coherence.
5.  **MIDI Out**: The result is sent to the `MidiBridge` and on to the synthesis hardware/software.
