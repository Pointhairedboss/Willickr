Roland S-1: Sound Synthesis Session
Voice Generation, Bit-Bashing, Spectral Analysis & Reasoning Captured
Session: 2026-03-06  |  Claude Sonnet 4.6  |  Context seed preservation

Purpose & Scope
This document preserves the complete reasoning thread, design decisions, alternative approaches considered, and working code produced during a single context window exploring what could be done with the Roland S-1 as a controlled synthesis instrument. The session began with LLM-driven patch design, evolved through formant/speech synthesis, and culminated in a novel PWM bit-bashing technique for spectral audio analysis.
The document is structured as a design journal — not just what was decided, but why, what was rejected, and what the implicit synthesis principles are that shaped each decision. It is intended to be readable both by a future LLM context as a seed, and by a human practitioner.

1. The Foundational Architecture: LLM → S-1 via MIDI CC
1.1 The Core Idea
The first question was: can an LLM control the S-1 meaningfully from a prompt like 'slow dark ambient pad in D minor'? The answer is yes, cleanly, because:
All 54 S-1 synthesis parameters are CC-addressable — no parameters are hardware-only for live performance
The CC space is small and well-scoped — a single JSON object covers an entire patch
Musical concepts map cleanly to parameter ranges without fine-tuning — only prompt engineering is required
The LLM already understands synthesis concepts from training; it just needs the CC map as grounding
1.2 The Architecture
The established pipeline:
User prompt (natural language)
    ↓
LLM (Qwen via LM Studio, or Claude API)
    ↓  JSON output: { bpm, notes[], cc: { filter_cutoff: 40, resonance: 60, ... } }
MIDI translation layer  ←── CC map for S-1
    ↓
python-rtmidi / mido
    ↓
S-1 via USB MIDI (channel 3 default, 0-indexed = 2)
The LLM does not need to know MIDI. The system prompt encodes the CC map and maps musical vocabulary to parameter ranges. The LLM outputs structured JSON; the Python layer translates to MIDI messages.
◆ Key insight: This is a prompt engineering task, not ML training. The knowledge is in the system prompt, not the weights.
1.3 Conceptual CC Groupings for Prompt Engineering
For a system prompt, parameters cluster as follows:
Parameter
CC
Range
Sound Design Role
Filter Frequency
74
0–127
Primary tonal openness — the most important single CC
Filter Resonance
71
0–127
Vowel character/peak — self-oscillates at 127
Envelope Attack
73
0–127
Percussive (0) vs slow bloom (high)
Envelope Decay
75
0–127
Note length character
Envelope Sustain
30
0–127
Pad sustain level
Envelope Release
72
0–127
Tail length
LFO Rate
3
0–127
Modulation speed — audio rate in Fast mode
LFO Depth → Pitch
13
0–127
Vibrato depth
LFO Depth → Filter
25
0–127
Filter wobble/growl
Reverb Level
91
0–127
Space — essential for ambient/bell
Reverb Time
89
0–127
Decay time of reverb
Delay Level
92
0–127
Echo presence
Square Level
19
0–127
Hollow/square character
Saw Level
20
0–127
Rich harmonic content
Sub Level
21
0–127
Sub-bass weight
Noise Level
23
0–127
Breath/friction/hi-hat content
Filter Env Depth
24
0–127
How much envelope opens filter
Polyphony Mode
80
0–127
Mono/Unison/Poly/Chord
Chorus Type
93
0–127
0=off, then types 1–4 (JUNO-derived)


2. Speech and Voice Synthesis — Approaches Considered
The session explored making the S-1 'speak' — using synthesis parameters to generate voice-like sounds. Four distinct approaches were identified. They are preserved here with their reasoning and relative merits.
2.1 Approach A: TTS Audio Through the S-1's Audio Input
The S-1 has two audio paths:
A 3.5mm audio input on the front panel that bypasses the synth engine and mixes directly with the synth output
USB audio class-compliant interface — the computer can send audio to the S-1's output over USB-C
This means TTS speech from an LLM pipeline (Kokoro, Coqui, ElevenLabs) can literally play through the S-1's output jack. The same USB-C cable carries MIDI CC patch control and audio output simultaneously.
LLM generates speech  →  TTS engine
                      →  routed to S-1 USB audio output
LLM generates patch   →  MIDI CCs
                      →  S-1 USB MIDI
Both streams: one cable, one box, AI speaks and plays simultaneously.
⚑ macOS aggregate device setup can be complex. On Windows/Linux, direct audio routing to S-1 as output device is straightforward.
◆ This is the 'obvious' approach. Clean, no synthesis complexity, but the S-1 is just a speaker in this mode — no synthesis character in the speech itself.
2.2 Approach B: Formant Synthesis via Filter + Resonance
Human vowels are defined by two formant frequencies — resonant peaks in the vocal tract. The S-1's filter resonance (CC71) creates a single peak at the cutoff frequency. This gives one-formant synthesis: crude but immediately vocal-sounding.
The pipeline:
Text → phoneme breakdown
     → pitch contour (intonation)
     → rhythm/timing
           ↓
     MIDI notes (pitch + timing)
     CC stream (filter/noise shaping per phoneme)
           ↓
          S-1
Phoneme-to-parameter rough mappings developed during the session:
Phoneme
Filter Freq (CC74)
Resonance (CC71)
Noise (CC23)
Notes
"ah"
60
50
0
Open vowel
"ee"
90
70
0
High front vowel — bright
"oh"
40
60
0
Rounded vowel
"oo"
25
55
0
Closed rounded — dark
"ss"
100
20
90
Noise dominant — sibilance
"sh"
80
10
80
Softer fricative
"mm"
30
30
0
Nasal — low cutoff, close filter

The S-1 tools that help:
OSC Draw — sculpt waveforms with formant-like harmonic content baked in
Noise + filter — classic sibilance ('s', 'sh') is filtered noise
Portamento (CC5) — gliding between pitches mimics vocal intonation
LFO on filter (CC25) — slow wobble approximates vocal tremor/vibrato
⚑ This is one-formant synthesis. True speech intelligibility needs two formants (F1, F2). The S-1 cannot do true two-formant vocal synthesis — it has a single resonance peak. The result will be vocal-like, not speech-intelligible.
◆ Best use: give the synth voice a character. Cold mechanical = closed filter, tight envelope, no vibrato. Warm breathy = open filter, slow LFO on filter, long release, noise blended in.
2.3 Approach C: Audio-to-MIDI Transcription + Resynthesis
Feed audio (voice, instrument, any source) through pitch/onset detection, generate MIDI note and CC stream, re-synthesise on the S-1. The audio source controls the S-1 but the S-1 sounds like itself.
Tools identified:
Aubio — lightweight, real-time pitch tracking and onset detection, Python-friendly, ~10-20ms latency
CREPE (Google) — neural pitch detection, more accurate, heavier — better for near-real-time than live
Basic Pitch (Spotify) — polyphonic audio to MIDI, open source, excellent for offline
The interesting twist: the LLM sits between transcription and playback and interprets rather than mirrors. Instead of exactly reproducing input pitch, it can transpose to a different key, harmonise, add countermelody, or change rhythmic feel.
Voice input → pitch detection → intonation contour
           → phoneme-to-CC mapping layered on top
The synth speaks with your vocal rhythm but in its own synthetic voice.
◆ Most useful for real-time performance: sing or hum, S-1 follows pitch but with synth timbre. Drum track → onset detection → trigger S-1 rhythmically.
2.4 Approach D: Raw Spectral Forcing (No Interpretation)
The most unusual approach. No pitch detection, no note events, no interpretation. Just FFT spectral analysis every ~20ms, map spectral features directly to CC parameters, flood the S-1 as fast as it will accept messages.
The mapping philosophy:
Audio frame
    ↓
FFT spectral analysis
    ↓
Map spectral peaks directly to:
  dominant frequency → filter cutoff (CC74) — chases pitch
  spectral centroid  → resonance (CC71) — bright = more resonant peak
  low band ratio     → square level (CC19) — match spectral balance
  mid band ratio     → saw level (CC20)
  high band ratio    → noise level (CC23) — fricative/high energy
  spectral flatness  → resonance — flat = noise-like source
  spectral flux      → LFO rate (CC3) — fast-changing = fast LFO
  RMS amplitude      → sub level (CC21)
⚑ The S-1 will not sound like the original audio. It will sound like the S-1 trying to sound like the original and failing in interesting ways. This is the point — unpredictable, glitchy, alive.
◆ The key constraint is MIDI CC bandwidth. Too many CC messages per second backs up the buffer. Use a priority queue — filter frequency and amplitude contribute most to perceived character, so weight them highest.

3. The PWM Bit-Bashing Technique — Origin and Reasoning
3.1 The Problem: 7-bit MIDI Resolution
MIDI CC values are 7-bit integers: 0–127. For synthesis parameters like filter cutoff, this is often too coarse — you can hear the steps. The question was: can we achieve sub-7-bit resolution, i.e., finer than 128 steps, without using high-resolution MIDI (NRPN)?
3.2 The Insight: 286 PC Speaker PWM
The original inspiration was the technique used by demo scene coders on 286 PCs to produce sampled audio through a single-bit speaker pin. The PC speaker could only be on or off. By toggling it rapidly at rates faster than the ear could resolve, the duty cycle of the toggling encoded amplitude. A 50% duty cycle felt like half volume. This was 1-bit DAC through timing rather than value.
The parallel for MIDI CC:
Instead of sending CC value 64 (50% of 127):
  → send CC 127, wait 5ms, send CC 0, wait 5ms, repeat

Instead of sending CC value 32 (25%):
  → send CC 127, wait 2.5ms, send CC 0, wait 7.5ms, repeat

Duty cycle encodes target value. Period = 20ms (50Hz switching rate).
3.3 Why This Works on the S-1
The S-1 models analog circuits via ACB. Analog circuits have slew rate — they cannot change instantaneously. The filter's ACB model physically integrates rapid switching, smoothing it out the same way a speaker cone averaged PWM pulses. You are driving the synth engine like a 1-bit DAC.
◆ The 'glitch' between extremes becomes part of the texture at audio-rate switching. At sub-audio PWM rates (20ms period = 50Hz), the S-1's parameter response integrates to the duty-cycle average — smooth control.
⚑ You need to know the S-1's parameter response time empirically. Too fast (period < ~5ms for some parameters) and messages queue up and back off. 20ms period proved reliable in practice.
3.4 Why PWM + Spectral Analysis Is a Novel Combination
In the spectral chasing application, the FFT window rate and the PWM rate become the same thing. The synth is being clocked by the audio analysis itself. The analysis window is ~23ms (1024 samples at 44100Hz), the PWM period is 20ms. They interlock naturally.
The result is a system where:
Audio complexity drives parameter density (more spectral change = faster CC updates)
The S-1's inability to reproduce the input becomes an expressive constraint rather than a failure
The priority queue ensures the most perceptually important parameters (filter freq, oscillator mix) track the source most faithfully
Lower-priority parameters (LFO rate, reverb) lag behind or approximate — creating an 'interpretation' effect even without an LLM

4. The Code: s1_spectral_pwm.py
4.1 Architecture
Three classes:
SpectralDriver — audio capture, queue management, analysis loop
PWMEncoder — per-parameter PWM thread, duty-cycle toggling
DirectCCDriver — simpler non-PWM mode for comparison
4.2 Key Design Decisions
Audio Buffer Management
Audio arrives in 512-sample hop-size blocks. A rolling 1024-sample buffer accumulates them with np.roll(). If the analysis thread can't keep up, frames are dropped (queue.Full silently discarded) — this is correct: it is better to drop frames than to accumulate latency.
Spectral Feature Extraction
Six features extracted per frame:
RMS amplitude — overall loudness → sub level weight
Spectral centroid — perceived brightness → resonance (capped at 0.7× to prevent self-oscillation trigger)
Dominant frequency — strongest spectral peak → filter cutoff (tracks pitch)
Low/mid/high band energy ratios — spectral tilt → oscillator mix balance
Spectral flatness — noise-like vs tonal → noise level
Spectral flux (approximated as high-freq variance) — rate of change → LFO rate
Resonance Cap
Filter resonance (CC71) is capped at centroid_norm × 0.7. This is intentional: centroid_norm at maximum would push CC71 to 89 (0.7 × 127), keeping it below the self-oscillation cliff at ~CC 120. Feeding chaotic audio into the S-1 without this cap would constantly trigger self-oscillation, turning the spectral chasing into uncontrolled laser noise.
⚑ The resonance cap value (0.7) is a tunable parameter. Lower it for more stable operation, raise it for more aggressive filter character. Do not exceed ~0.9 (CC 114) without testing.
PWM Period and CC Rate
PWM_PERIOD    = 0.020   # 20ms per cycle
MAX_CC_RATE   = 200     # CC messages per second ceiling
PWM_MIN_DUTY  = 0.05    # keeps parameter alive at minimum
PWM_MAX_DUTY  = 0.95    # prevents full saturation
With 11 parameters and 2 messages per parameter per cycle (HIGH and LOW phases), each full PWM cycle sends 22 CC messages in 20ms = 1100 CC/s theoretical. MAX_CC_RATE = 200 is the enforced ceiling. The loop paces itself: if a cycle completes faster than 22/200 = 0.11s, it sleeps the remainder.
Priority Queue
CC_PRIORITY determines the order parameters are updated within each PWM cycle:
CC_PRIORITY = [
    "filter_freq",    # most important — tracks pitch
    "osc_square",     # second — low-mid spectral weight
    "filter_res",     # third — tonal character
    "noise_level",    # fourth — fricative/high content
    "osc_saw",
    "osc_sub",
    "lfo_rate",
    "lfo_depth",
    "reverb_level",
    "env_attack",
    "env_release",    # least time-critical
]
4.3 Usage
# List devices
python s1_spectral_pwm.py --list

# Basic direct CC mode (7-bit)
python s1_spectral_pwm.py --device 1 --midi S-1 --channel 3

# PWM mode (sub-7-bit resolution)
python s1_spectral_pwm.py --device 1 --midi S-1 --channel 3 --pwm

# Requirements:
pip install numpy scipy sounddevice python-rtmidi
4.4 Known Limitations and Future Work
Spectral flux is approximated as high-frequency variance, not true frame-to-frame difference — implement a previous_spectrum buffer for proper flux calculation
PWM is per-parameter serial, not truly parallel — a future version could use one thread per parameter
The LFO rate mapping (flux → CC3) pushes the LFO into audio-rate territory at high flux values. In Fast mode (CC79=127) this creates FM effects — potentially desirable, but can be startling. Add a lfo_fast_mode flag
No LFO key trigger reset (CC105) — in current form, LFO phase is continuous. For rhythmically locked spectral analysis, trigger LFO reset at hop boundaries
USB audio latency on macOS can drift — use TRS MIDI in + separate audio interface for most stable operation

5. Synthesis Principles Formed During the Session
These are not general synth rules — they are S-1-specific principles derived from the session reasoning:
5.1 Filter as Voice Rather Than Just Tone
The S-1's IR3109 OTA filter has a pronounced resonant peak that tracks vowel-like formant positions when CC71 is in the 40–90 range. Used deliberately, this makes the filter not just a tone-shaper but a vowel generator. The distinction matters for sound design: low resonance = tonal shaping; mid resonance = character/vowel; high resonance = singing; maximum = sine oscillator.
5.2 Attack = 0 for Everything Percussive
This came directly from the bell synthesis debugging. CC73 (attack) must be 0 for any sound defined by an instant transient: bells, plucks, drums, stabs. Any non-zero attack introduces a bloom that destroys the perceptual onset characteristic of the sound. The S-1's envelope has no minimum attack — it can be fully instantaneous.
5.3 The Shared Envelope Constraint
The S-1 has one ADSR for both filter and VCA. This is not a bug — it is a design philosophy inherited from the SH-101. Work with it: use CC24 (filter envelope depth) to make the filter envelope's contribution larger or smaller than the amplitude envelope's natural curve. A pluck patch with low CC24 has a sharp amplitude transient with a gentler filter sweep; with high CC24, filter and amp are closely coupled.
5.4 Noise Is Not Just for Percussion
CC23 (noise level) can be blended into any patch at low levels (5–20) to add breath, air, and texture. A pad with a small noise component sounds more like air moving through pipes than a pure electronic tone. A bell with noise (CC23 = 8) has clapper strike character. This is the 'clapper transient' technique used in the harbour bells synthesis.
5.5 The 7-bit CC Discretisation Problem
At slow parameter sweep speeds, 7-bit CC resolution (128 steps) produces audible stepping — particularly on filter cutoff (CC74) which has a large Hz range. Three solutions: (1) use smooth automation curves that update every 10–20ms to create pseudo-continuous motion; (2) add small random ±1 CC jitter to dither the steps; (3) use PWM encoding for sub-7-bit resolution. For generative music, (1) and (2) are usually sufficient.
5.6 Reverb Type Selection Matters
The S-1 has 7 reverb types. For distant/ambient sounds (buoy bells, harbour scenes), Plate or Hall 1 with moderate pre-delay (20–40ms via menu) is most convincing. Spring reverb adds character but introduces flutter that is rarely appropriate for continuous ambient work. Modulate reverb adds waver that suits drone patches but clashes with rhythmic material.
5.7 The Local-Off Problem in Generative Contexts
The S-1 has no local-off mode — it echoes all incoming MIDI. In a DAW with MIDI thru active, this creates feedback loops. In a standalone Python MIDI script, it means every note-on you send comes back as a second note-on. Solution: use TRS MIDI in rather than USB MIDI for playback, or implement duplicate-message filtering at the receiving layer.

6. Approaches Considered and Not Pursued
6.1 Vocoder
The S-1's audio input (which bypasses the synth engine and mixes directly with output) cannot act as a vocoder modulator for the internal synth signal. A true vocoder needs the audio to modulate the filter — the S-1's input path does not connect to the filter. There is no vocoder mode. A software vocoder (VCV Rack, external plugin) could process audio and send resulting CC values to the S-1 as a carrier, but this adds significant complexity for marginal benefit over approach D.
6.2 Two-Formant Vocal Synthesis
True vowel intelligibility requires two independent formant peaks (F1 and F2 in speech). The S-1 has one filter with one resonance peak. F1 could be placed at the filter cutoff; F2 would require a second formant oscillator or filter — not available on the S-1. OSC Draw could theoretically encode a two-peak spectral shape, but the Draw system operates on the waveform shape, not on explicit formant positions. Not practical.
6.3 Fine-Grained Pitch Tracking via CC76
CC76 (fine tune) covers ±1 octave — a large range. For pitch tracking applications (approaches C and D), the dominant frequency → filter cutoff mapping is more responsive than using CC76 for pitch. Filter cutoff has faster slew response in ACB than oscillator pitch. For precise pitch tracking, MIDI note numbers are better than CC76 — they retrigger the envelope, which is usually desirable for transcription but not for spectral chasing.
6.4 Osc Chop as Formant Tool
OSC Chop can create comb-filter-like resonances that superficially resemble formant peaks. Explored briefly, but rejected: (1) Chop has no audible effect above ~1kHz fundamental, limiting vocal-register usefulness; (2) Chop positions are fixed relative to the waveform period, not to absolute frequency — they shift with pitch, unlike true formants which are fixed in Hz; (3) CC control resolution for Chop Comb and Overtone is coarse at extreme values.

7. Lateral Applications Noted
7.1 Sonification Engine
Map any real-time data stream to CCs. Server metrics, network traffic, game state, sensor data. The S-1 as auditory display: filter cutoff tracks CPU load, reverb depth tracks network latency, LFO rate tracks request rate. The 5–10ms USB MIDI response time is fast enough for real-time monitoring feedback.
7.2 Game Audio Reactor (Air Combat Sim)
For the flight simulator project: bind game state directly to the S-1. Altitude → filter frequency. Airspeed → LFO rate. Damage state → resonance. Engine stress → noise level. Not triggered one-shot sounds but a continuously evolving sonic environment that physically responds to flight state — closer to physical modelling than triggered SFX.
7.3 AI Agent Sonic Signatures
In a multi-agent system (SparxOS/ADOPTG), different agents could have different characteristic patches. When an agent is active, its signature patch plays. Makes invisible agent activity audible. Each agent is a timbre; interactions are chord clusters; state changes are filter sweeps.
7.4 Raspberry Pi Synthesis Node
S-1 connected to Pi over USB becomes a networked synthesiser node driven from anywhere on the LAN. IoT sensor data → Pi → S-1. The Pi handles spectral analysis if needed; the S-1 is the output-only leaf. This offloads compute from the audio host machine entirely.

8. File Registry
Filename
Created
Contents
s1_spectral_pwm.py
2026-03-06 (session 1)
Real-time spectral analysis + PWM CC driver. Two modes: direct CC and PWM bit-bashing. Full CLI.
harbour_bells_v3.py
2026-03-06 (session 2)
Harbour soundscape. VCO-based bell synthesis, Oranges & Lemons melody, buoy bing-bong pairs.
harbour_bells_fix.py
2026-03-06 (session 2)
Intermediate version — bing-bong pairs added but still self-oscillating filter (superseded by v3).
s1_voice_synthesis_preservation.docx
2026-03-06
This document.


Session captured 2026-03-06 | Claude Sonnet 4.6 | This document is a context seed intended for re-ingestion into a future LLM session with the S-1 as the synthesis target.