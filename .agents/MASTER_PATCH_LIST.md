# Syntheory S-1: Master Taxonomy & Core Patch Library

## 1. Multi-Dimensional Taxonomy Schema
Based on the initial findings from the agent roster, every patch generated for the Syntheory S-1 project will be classified using the following dimensions to ensure intention and logical retrieval.

### A. Acoustic Physics (Origin)
Defines the sound by mechanical emulation or failure state.
- `Strike`, `Pluck`, `Bow`, `Breath`, `Friction`, `Fracture`
- `Artifacting/Failure-State` *(For sounds relying on DSP/ACB engine limits)*

### B. Temporal Behavior
Defines the lifecycle and motion of the patch.
- `Static`, `Evolving`, `Generative`, `Rhythmic`, `Decaying`, `Unstable`

### C. Emotional Resonance
Maps the psychological and atmospheric intent of the sound.
- `Tension`, `Euphoria`, `Melancholia`, `Nostalgia`, `Dread`, `Tranquility`

### D. Engine Stress (The Exploration Axis)
Categorizes the computational strain requested from the hardware.
- `Safe-Mode`: Within documented limits.
- `Edge-Case`: Pushing maximum LFO rates, complex rapid envelope retriggers.
- `Glitch-State` / `Buffer-Overload`: Exploiting MIDI CC rate limits, intentional voice-stealing clicks.

### E. Functional Role
Standard usability categorization for the Production Library mandate.
- `Lead`, `Bass`, `Bed/Pad`, `Percussive`, `Drone`, `FX`

### F. Historical/Generic (Dual-Tagging)
Maintained specifically for classic subtractive recreations to aid end-user searchability.
- `Brass-Subtractive`, `String-Machine`, `Percussive-Analog`, etc.

---

## 2. Core Patch Library Outline
The initial library generation will be divided into the following focus areas based on agent domains.

### I. The Classic Subtractive Foundation (Agent Gamma & Alpha)
Recreating historic synth techniques with precise mathematical boundaries.
- **Acoustic Brass Recreations**: Utilizing delayed/steep filter envelopes to mimic the "blat" (`Breath`, `Brass-Subtractive`).
- **Bowed Strings**: Slow harmonic builds using precisely tuned LFO vibrato (`Bow`, `String-Machine`).
- **Analog Percussion**: Pitch-envelope approximations for kicks and snares using LFO single-shot or filter/pitch routing (`Strike`, `Percussive-Analog`).
- **Sub-Oscillator Basslines**: Phase-aligned foundational tones (`Strike/Sustain`, `Bass`).

**Generated Patches:**
- `[001]` **The Synthetic Brass Blat** (`agent_gamma_classic_brass.py`): `[Origin: Breath] + [Behavior: Decaying] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Brass-Subtractive]`
- `[002]` **The Solina Bow** (`agent_gamma_string_1.py`): `[Origin: Bow] + [Behavior: Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: String-Machine]`
- `[003]` **The 808-Style Analog Kick** (`agent_gamma_kick_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Percussive-Analog]`

### Phase IV: The Gordon Reid Transcription (Gamma Subclasses)
Parallel mass construction of specific acoustic models.

**Gamma-P (Percussion) Patches:**
- `[004]` **The 808-Style Cowbell**: `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]`

**Gamma-K (Keys/Organs) Patches:**
- `[005]` **The Tonewheel Drawbar Foundation**: `[Origin: Friction] + [Behavior: Static] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Organ-Emulation]`

**Gamma-W (Winds/Strings) Patches:**
- `[006]` **The Pure Sine Flute**: `[Origin: Breath] + [Behavior: Evolving] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]`

### II. Ambient Environments & Micro-Spaces (Agent Beta)
Treating the S-1 as a perceptual environment generator.
- **Base Beds**: Sparse inputs smeared by extreme Delay/Reverb tails to fake $>4$ polyphony (`Friction`, `Bed/Pad`).
- **Organic Motion Layers**: Sub-Hz LFO drift on cutoff/pitch coupled with sequencer probability (`Generative`, `Drone`).
- **Textural Room Tones**: DRAW and CHOP/MULTIPLY modes yielding customized non-linear noise floors (`Fracture`, `FX`).

**Generated Patches:**
- `[001]` **The Fracture Bed** (`agent_beta_ambient_1.py`): `[Origin: Fracture] + [Behavior: Generative] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Bed/Pad]`
- `[002]` **The Harmonic Tide** (`agent_beta_ambient_2.py`): `[Origin: Flow] + [Behavior: Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Bed/Pad]`
- `[003]` **The Neon Buzz** (`agent_beta_ambient_3.py`): `[Origin: Fracture] + [Behavior: Static] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: FX]`
- `[004]` **The Glacial Pad** (`agent_beta_glacial_pad.py`): `[Origin: Oscillator mix] + [Behavior: Static] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Pad]`
- `[005]` **Abyssal Chimes** (`agent_beta_abyssal_chimes.py`): `[Origin: Strike/Metallic] + [Behavior: Generative] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Bed/Pad]`

### III. Algorithmic Translation & DSP Exploration (Agent Delta & Alpha)
Compressing complex signal flow concepts into the 4-voice ACB limits.
- **Pseudo-FM & Sidebands**: Audio-rate LFO modulation of Pitch/Filter/PWM to create inharmonic, metallic timbres (`Strike`, `Edge-Case`).
- **Algorithmic Step-Sequencing**: Markov-chain emulations utilizing probability, sub-steps, and aggressive multi-parameter Motion Recording (`Rhythmic`, `Generative`).
- **Carrier-Modulator Illusions**: Balancing oscillator vs. sub-oscillator volumes dynamically via loops to fake multi-operator relationships.

**Generated Patches:**
- `[001]` **The Markov Chain Sequence** (`agent_delta_algo_1.py`): `[Origin: Flow] + [Behavior: Generative] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead]`
- `[002]` **The Carrier-Modulator Illusion** (`agent_delta_fm_1.py`): `[Origin: Flow] + [Behavior: Evolving] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Pad]`
- `[003]` **Micro-Envelope Markov** (`agent_delta_markov_sequence.py`): `[Origin: Artifacting] + [Behavior: Generative] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead]`
- `[004]` **Euclidean FM** (`agent_delta_euclidean_fm.py`): `[Origin: System] + [Behavior: Rhythmic] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive]`
- `[005]` **Stochastic Pseudo-FM** (`agent_delta_algorithmic_fm.py`): `[Origin: System] + [Behavior: Generative] + [Emotion: Abrasive] + [Stress: Failure-State] + [Role: Texture/Percussion]`
- `[006]` **Euclidean Rhythm Generator** (`agent_delta_euclidean_rhythm.py`): `[Origin: System] + [Behavior: Rhythmic] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive]`
- `[007]` **Markov Drone Parameter Shifter** (`agent_delta_markov_drone.py`): `[Origin: System] + [Behavior: Generative] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Drone]`
- `[008]` **Stochastic Pseudo-FM V2** (`agent_delta_stochastic_fm_v2.py`): `[Origin: System] + [Behavior: Generative] + [Emotion: Abrasive] + [Stress: Edge-Case] + [Role: Lead]`

### IV. Hardware Stress & Boundary Testing (Agent Epsilon)
Patches that exist *only* because of hardware failure points.
- **CC Data Floods**: Max-density MIDI CC scripting to induce zipper noise or buffer overloads (`Artifacting/Failure-State`, `Glitch-State`).
- **Voice-Stealing Rhythms**: Intentional triggering of the 5th note under specific envelope conditions to generate rhythmic clicking (`Unstable`, `Artifacting/Failure-State`).

### V. Phase IV: The Gordon Reid Transcriptions (Agent Gamma Subclasses)
Parallel mass transcription of structural acoustic modeling derived from the 'SyntheoryGordonReid' corpus, utilizing shared `s1_midi.py` wrappers and strict DSP/Hardware bounds.
- `[004]` **808-Style Cowbell** (`gamma_p_cowbell_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]`
- `[005]` **Tonewheel Drawbar Foundation** (`gamma_k_tonewheel_1.py`): `[Origin: Friction] + [Behavior: Static] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Organ-Emulation]`
- `[006]` **Pure Sine Flute** (`gamma_w_flute_1.py`): `[Origin: Breath] + [Behavior: Evolving] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]`
- `[007]` **The Analog Snare** (`gamma_p_snare_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]`
- `[008]` **Synthetic Acoustic Piano** (`gamma_k_piano_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Acoustic-Emulation]`
- `[009]` **The Andean Pan Pipe** (`gamma_w_panpipe_1.py`): `[Origin: Breath] + [Behavior: Evolving] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]`
- `[010]` **The Realistic Cymbal** (`gamma_p_cymbal_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Cymbal-Emulation]`
- `[011]` **The Bowed Violin** (`gamma_w_violin_1.py`): `[Origin: Bow] + [Behavior: Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Bowed-String]`
- `[012]` **The Theoretical Acoustic Guitar** (`gamma_k_guitar_1.py`): `[Origin: Pluck] + [Behavior: Decaying] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Plucked-String]`
- `[013]` **The Orchestral Timpani** (`gamma_p_timpani_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]`
- `[014]` **The Synthetic Electric Piano** (`gamma_k_epiano_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Keys] + [Historical: Acoustic-Emulation]`
- `[015]` **The Synthetic Choir** (`gamma_w_choir_1.py`): `[Origin: Breath] + [Behavior: Evolving] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Pad] + [Historical: Vocal-Emulation]`
- `[016]` **Acoustic Piano Transcription** (`agent_gamma_k_piano_acoustic.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`
- `[017]` **Electric Piano Transcription** (`agent_gamma_k_piano_electric.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`
- `[018]` **String Machine Ensemble** (`agent_gamma_w_string_machine.py`): `[Origin: Artifacting/Emulation] + [Behavior: Evolving] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Pad] + [Historical: String-Machine]`
- `[019]` **Tonewheel Organ Emulation** (`agent_gamma_k_organ_tonewheel.py`): `[Origin: Strike] + [Behavior: Static] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Organ-Emulation]`
- `[020]` **Transistor Combo Organ** (`agent_gamma_k_organ_combo.py`): `[Origin: Strike] + [Behavior: Static] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Transistor-Combo]`
- `[021]` **The Synthesized Bell** (`agent_gamma_p_bell.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Percussive/Lead] + [Historical: Percussive-Analog]`
- `[022]` **The Claves** (`agent_gamma_p_claves.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]`
- `[023]` **The TR-808 Hi-Hat** (`agent_gamma_p_hihat_808.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Percussive] + [Historical: Drum-Machine]`
- `[024]` **The Clarinet** (`agent_gamma_w_clarinet.py`): `[Origin: Breath] + [Behavior: Evolving] + [Emotion: Tranquility] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Wind-Emulation]`
- `[021]` **Bowed String Articulation** (`agent_gamma_w_bowed_articulation.py`): `[Origin: Bow/Friction] + [Behavior: Rhythmic/Generative] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Ondes-Martenot]`
- `[022]` **Bowed Strings 1** (`agent_gamma_w_bowed_strings_1.py`): `[Origin: Bow/Friction] + [Behavior: Evolving] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`
- `[023]` **Bowed Strings 2** (`agent_gamma_w_bowed_strings_2.py`): `[Origin: Bow/Friction] + [Behavior: Generative/Evolving] + [Emotion: Melancholia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Performative-Control]`
- `[024]` **Orchestral Flute** (`agent_gamma_w_flute.py`): `[Origin: Edge-Blown] + [Behavior: Tremulous] + [Emotion: Ethereal] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`
- `[025]` **Pan Pipes** (`agent_gamma_w_pan_pipes.py`): `[Origin: Edge-Blown] + [Behavior: Percussive Attack] + [Emotion: Meditative] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`
- `[026]` **PWM Strings** (`agent_gamma_w_pwm_strings.py`): `[Origin: Emulation/Synthesis] + [Behavior: Rhythmic] + [Emotion: Euphoria] + [Stress: Safe-Mode] + [Role: Pad] + [Historical: PWM-Synthesis]`
- `[027]` **Simple Flutes (Recorders)** (`agent_gamma_w_recorder.py`): `[Origin: Edge-Blown] + [Behavior: Plucked/Sustained] + [Emotion: Nostalgia] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`
- `[028]` **The Violin Ensemble** (`agent_gamma_w_violin.py`): `[Origin: Bow/Friction] + [Behavior: Evolving] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Acoustic-Emulation]`


**Generated Patches:**
- `[001]` **The Inharmonic Bell** (`agent_alpha_bell_1.py`): `[Origin: Strike] + [Behavior: Decaying] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: FX/Percussive]` *(Agent Alpha DSP Test)*
- `[002]` **The Buffer Overload (Zipper Glitch)** (`agent_epsilon_glitch_1.py`): `[Origin: Artifacting/Failure-State] + [Behavior: Unstable] + [Emotion: Dread] + [Stress: Glitch-State] + [Role: FX]`
- `[003]` **The Voice-Stealing Rhythm** (`agent_epsilon_voice_steal_1.py`): `[Origin: Artifacting/Failure-State] + [Behavior: Rhythmic] + [Emotion: Tension] + [Stress: Edge-Case] + [Role: Rhythmic]`
- `[004]` **LFO Frequency Cap Stress Test** (`agent_epsilon_stress_test_1.py`): `[Origin: Artifacting/Failure-State] + [Behavior: Static] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: FX]`
