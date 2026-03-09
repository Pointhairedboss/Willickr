# Roland S-1 Tweak Synthesizer: complete technical breakdown for MIDI CC programming

The Roland S-1 is a **4-voice digital polysynth** built on Roland's ACB (Analog Circuit Behavior) engine, modeling the 1982 SH-101 at the component level. It shares its core DSP engine with the SH-01A Boutique but adds polyphony, OSC Draw/Chop waveform tools, JUNO/JX-3P-derived chorus, delay, seven reverb types, and a motion sequencer. For generative MIDI CC work, the S-1 exposes **54 CC-addressable parameters** covering every synthesis parameter — but ships with a single shared ADSR, no oscillator sync, no ring mod, no FM, and no local-off mode. Understanding these constraints and the CC map below is essential to getting the most from it as an external sound module.

---

## 1. Architecture and signal flow

**Signal path**: Oscillator sources (square/pulse + sawtooth + sub-oscillator + noise) → Source Mixer → per-voice 24dB/oct LPF → per-voice VCA → Chorus → Delay → Reverb → stereo output.

In Poly mode, the S-1 runs **four independent voice paths** — each with its own oscillator, filter, and amplifier — merged at the effects bus. This is not a shared filter topology. The effects are global (post-mix), running in series: chorus first, then delay, then reverb.

**ACB modeling basis**: The S-1 models the Roland SH-101's analog circuit at the component level. The original SH-101 used a **CEM3340 VCO** and a **Roland IR3109 filter chip** — a 4-pole cascaded OTA (operational transconductance amplifier) design, the same chip family found in the Jupiter-6, Jupiter-8, and Juno-106. This is **not a ladder filter** in the Moog (transistor) or TB-303 (diode) sense. The IR3109 uses four OTA stages with external feedback for resonance, producing a characteristically smooth self-oscillation curve and the warm Roland low-pass signature. Roland states ACB works from "original design specs, consultation with original engineers, and a detailed, part-by-part analysis of each analog circuit," including modeled instabilities and drift.

**Polyphony and voice modes** (CC80):

- **Mono**: Single voice. Note priority configurable via menu (`n.Pri`): last-note or lowest-note.
- **Unison**: All 4 voices stacked on one note with slight detuning — universally praised as thick and satisfying.
- **Poly**: 4-voice polyphonic, each voice independently filtered.
- **Chord**: Single key triggers up to 4 voices at configurable semitone intervals (CC81–83 toggle voices on/off; CC85–87 set transposition ±12 semitones per voice).

**Voice stealing**: In Poly mode, the S-1 uses standard voice-stealing when all 4 voices are occupied. When envelope trigger mode is set to Gate+Trig (CC29), every keypress forces a retrigger regardless of legato state.

**Hidden voice behavior**: The internal audio bus can clip when all four oscillator sources are at maximum across all voices. The per-pattern `uOL` (internal volume) parameter — accessible only via menu — attenuates the synth engine before the output stage. Community consensus is to set this to **80–90** (out of 100) as a default. Neither the output volume knob nor `uOL` affects the noise floor (approximately **−80 dB**, matching the original SH-101).

---

## 2. Oscillator section

The S-1 provides four simultaneously mixable oscillator sources, blended before the filter. There is **no oscillator sync, no ring modulation, and no cross-modulation/FM** at the oscillator level. Audio-rate LFO (see Section 5) is the only route to FM-like effects.

### Waveforms and their CCs

| Source | Level CC | Notes |
|---|---|---|
| **Square/Pulse** | CC19 (0–127) | Variable pulse width. Replaced by OSC Draw waveform when Draw is active |
| **Sawtooth** | CC20 (0–127) | Classic saw, all integer harmonics at 1/n amplitude |
| **Sub-oscillator** | CC21 (0–127) | Square/pulse wave only (not sine). Three types via CC22 |
| **Noise** | CC23 (0–127) | Pink or white, selectable via CC78. Also controls Riser level when Riser mode is active |

### Sub-oscillator types (CC22)

The sub is always a square-type wave:
- **−2 oct asymmetric** (`-2o.A`): Two octaves below, narrow pulse width — adds grit and edge.
- **−2 oct symmetric** (`-2oc`): Two octaves below, true square wave — cleaner sub-bass reinforcement.
- **−1 oct symmetric** (`-1oc`): One octave below, true square — standard SH-101 sub behavior.

### Pulse width modulation

PWM is fully available on the square wave. **CC15** sets the pulse width value (0–127, mapped internally to 0–255). **CC16** selects the modulation source: manual/fixed (`NAn`), LFO, or envelope. When source is LFO or envelope, CC15 still sets the base width around which modulation occurs. PWM is **disabled when OSC Draw is active** (Draw replaces the square wave entirely).

### Oscillator range and tuning

**CC14** (Oscillator Range) selects coarse octave: 64′, 32′, 16′, 8′ (default, where lowest C = MIDI 60), 4′, 2′. This CC maps to **discrete steps**, not a continuous sweep — expect jumps. **CC76** (Range Fine Tune) provides ±1 octave continuous tuning. **CC18** sets pitch bend sensitivity (internal 0–240; 120 = ±1 octave, 240 = ±2 octaves).

### OSC Draw and OSC Chop (unique to S-1, not on SH-101)

**OSC Draw** replaces the square wave with a user-defined waveform drawn across 16 amplitude steps (−100 to +100 each). Display modes: Step (staircase) or Slope (interpolated), selectable via **CC107**. **CC102** (Draw Multiply, internal 1.0–32.0) repeats the waveform within one cycle — each doubling adds one octave of harmonic content, producing hard-sync-like timbres.

**OSC Chop** divides each waveform into 16 time segments that can be independently muted or phase-reversed. Separate chop patterns exist for square, saw, sub, and noise. **CC103** (Chop Overtone, internal 0–200): 0 = no effect, 100 = full mute of chopped segments, >100 = reverse-phase emphasis creating aggressive overtones. **CC104** (Chop Comb, internal 1.0–32.0) repeats the chop pattern for metallic, comb-filter-like textures. **Important**: Chop Comb has no audible effect above approximately 1 kHz note frequency.

---

## 3. Filter section

### Filter type and circuit character

The S-1 models a **4-pole (−24 dB/oct) low-pass filter** based on the SH-101's IR3109 cascaded OTA topology. There is no high-pass, band-pass, or state-variable mode — it is LPF only. The original circuit includes Q compensation (input signal boost as resonance increases), faithfully reproduced in ACB. Professional reviewers describe the low-end character as having "surprising warmth and silkiness" (Engadget) with particular strength in sub-bass frequencies. Some community members note the ACB version sounds **slightly thinner than original SH-101 hardware**, with marginally less bass saturation — a common observation across ACB emulations.

### Parameters and CCs

| Parameter | CC | Internal range | Notes |
|---|---|---|---|
| **Cutoff frequency** | CC74 | 0–127 | Full range from sub-audio to open |
| **Resonance** | CC71 | 0–127 | Self-oscillation at maximum |
| **Envelope depth** | CC24 | 0–127 | Envelope → cutoff modulation intensity |
| **LFO depth** | CC25 | 0–127 | LFO → cutoff modulation intensity |
| **Keyboard follow** | CC26 | 0–255 (mapped from 0–127) | 255 = perfect 1V/oct tracking |
| **Bend sensitivity** | CC27 | 0–255 (mapped from 0–127) | Pitch bend → cutoff range |

### Self-oscillation

The filter **does self-oscillate** at CC71 = 127, producing a clean sine wave at the cutoff frequency. The transition into self-oscillation occurs approximately in the **CC71 120–127 range** — it is not a gradual onset but a relatively sharp cliff in the final few CC values. With keyboard follow (CC26) at maximum and all oscillator levels at zero, you get a playable sine wave source that tracks pitch. Because there are **4 independent filters in Poly mode**, you can play 4-note sine wave chords this way. Community users confirm this technique produces "nice clean controllable sine waves that pitch all the way down to sub frequencies" and works well for basic kick drum synthesis.

### Drive and saturation

There is **no dedicated drive, overdrive, or saturation effect** on the S-1. The filter's ACB modeling includes the IR3109's inherent nonlinearities, but multiple community members note the sound is "a bit clean" compared to running a real SH-101 hot. The internal bus clipping when `uOL` is set high and oscillators are maxed is uncontrolled distortion, not a useful drive circuit.

---

## 4. Amplifier and envelope section

The S-1 has a **single shared ADSR envelope** for both filter and amplifier. This matches the original SH-101 architecture but is a significant constraint for complex sound design — there is no independent filter envelope.

### Envelope CCs

| Parameter | CC | Notes |
|---|---|---|
| **Attack** | CC73 | 0–127 |
| **Decay** | CC75 | 0–127 |
| **Sustain** | CC30 | 0–127 |
| **Release** | CC72 | 0–127 |
| **Amp mode** | CC28 | Gate (constant volume while held) or Envelope (VCA follows ADSR) |
| **Trigger mode** | CC29 | LFO (retrigger at LFO rate), Gate (no retrigger on legato), Gate+Trig (always retrigger) |

### Velocity sensitivity

The S-1's built-in rubber pads are **not velocity-sensitive**. However, **velocity data received via external MIDI is recognized** and can be recorded into sequencer steps (per-step velocity, range 1–127). The manual does not document a velocity-to-filter or velocity-to-amplitude scaling curve — velocity primarily affects the internal sequencer's per-step dynamics rather than acting as a real-time modulation source in the traditional sense.

### Expression and volume

**CC7** is not explicitly documented in the S-1's CC map. **CC11** (Expression) is supported and controls volume in the negative direction (attenuation only, matching D-Motion expression behavior). **CC10** controls stereo pan (64 = center).

---

## 5. LFO

### Waveforms (CC12)

Six waveforms, selected by CC12 value ranges (the CC divides 0–127 into six zones):
1. **Sawtooth** (ramp down)
2. **Inverted sawtooth** (ramp up)
3. **Triangle**
4. **Square**
5. **Random** (sample-and-hold — stepped random values at LFO rate)
6. **Noise** (continuous random — smooth noise modulation source)

### Rate and audio-rate capability

**CC3** controls LFO rate (0–127, mapped internally to 0–255). **CC79** (LFO Mode) toggles between Normal and **Fast mode**. Fast mode extends the LFO range dramatically — **confirmed by multiple reviewers to reach audio rate**, enabling quasi-FM effects when routed to oscillator pitch or filter cutoff. MusicTech: "The LFO can more than hit audio rate." Fast mode is disabled when LFO Sync is on.

### LFO destinations

The LFO can modulate three targets:
- **Oscillator pitch** (CC13 controls depth) — vibrato, trills, audio-rate FM
- **Filter cutoff** (CC25 controls depth) — wah, growl, rhythmic filter sweeps
- **Pulse width** (when CC16 PWM source = LFO) — animated timbral movement

Additionally, the LFO drives **envelope retriggering** when CC29 (Trigger Mode) = LFO — the envelope restarts at the LFO rate, creating rhythmic amplitude/filter gating.

### Sync and retrigger

**CC106** (LFO Sync Mode, added in firmware v1.02): Syncs LFO rate to MIDI clock tempo with note-value subdivisions (128th note to 8× whole note, including dotted and triplet). **CC105** (LFO Key Trigger): When on, LFO phase resets on each new note-on — critical for deterministic generative patches where you need consistent modulation phase per note.

### Mod wheel interaction

**CC1** (Mod Wheel) controls a **dedicated sine-wave LFO output** applied to pitch or filter (depending on routing), separate from the main LFO waveform. **CC17** sets the modulation depth for this secondary mod path.

---

## 6. Effects

### Chorus (CC93)

Derived from the **JUNO-60 and JX-3P chorus circuits** via ACB. Five settings:
- OFF
- **Type 1**: Standard JUNO-style chorus — warm stereo widening
- **Type 2**: Faster modulation rate
- **Type 3**: Rotary speaker (fast) emulation
- **Type 4**: Relaxed, slow modulation

Chorus is **not directly panel-accessible** — it lives in the menu and is controlled only via CC93 or menu navigation. No depth or rate controls beyond type selection.

### Delay (CC90, CC92)

| Parameter | CC | Notes |
|---|---|---|
| **Delay time** | CC90 | 1–740 ms free-running, or tempo-synced note values |
| **Delay level** | CC92 | Internal 0–255. Delay Level Mode (menu) selects input-send vs output-level behavior |

The delay supports **both free-running and MIDI-clock-synced** operation (configurable via menu). Additional menu parameters include feedback amount, low-cut (20 Hz–800 Hz or flat), and high-cut (630 Hz–12.5 kHz or flat). A **pre/post mode** for the level knob allows the delay to function as a send (delay tail rings out when level is reduced) or as a straight output level. This is useful for generative work: automate CC92 to zero and the delay tail sustains.

### Reverb (CC89, CC91)

| Parameter | CC | Notes |
|---|---|---|
| **Reverb time** | CC89 | Internal 0–255 |
| **Reverb level** | CC91 | Internal 0–255 |

Seven reverb types (menu-selectable): **Ambience** (off-mic simulation), **Room**, **Hall 1** (clear, spacious), **Hall 2** (mild), **Plate**, **Spring** (guitar-amp style), **Modulate** (hall with wavering modulation). Additional menu parameters: pre-delay (0–100 ms), low-cut, high-cut, density (0–10). Professional opinion is mixed — Sound On Sound calls the reverbs "impressive," Engadget says "merely ok."

### Effect tails across patterns

A global/per-pattern switch determines whether delay and reverb **tails continue across pattern changes** or are muted on switch. When set to global, effect tails persist — a rare and valuable feature for live and generative contexts.

### What's missing

There is **no drive, overdrive, distortion, or saturation effect**. No phaser, flanger, or EQ. The effects palette is strictly chorus → delay → reverb.

---

## 7. Complete MIDI implementation

### Full CC map

| CC | Parameter | Value behavior |
|---|---|---|
| 1 | Mod wheel | 0–127, controls sine LFO depth to pitch/filter |
| 3 | LFO rate | 0–127 (internal 0–255) |
| 5 | Portamento time | 0–127 (internal 0–255) |
| 10 | Pan | 0–127 (64 = center) |
| 11 | Expression | 0–127 (attenuation only) |
| 12 | LFO waveform | 0–127, six discrete zones |
| 13 | Oscillator LFO pitch depth | 0–127 |
| 14 | Oscillator range | Discrete steps: 64′/32′/16′/8′/4′/2′ |
| 15 | Square pulse width | 0–127 (internal 0–255) |
| 16 | PWM source | Discrete: Envelope / Manual / LFO |
| 17 | LFO modulation depth | 0–127 (internal 0–255) |
| 18 | Pitch bend sensitivity | 0–127 (internal 0–240; 120=±1oct) |
| 19 | Square wave level | 0–127 |
| 20 | Sawtooth level | 0–127 |
| 21 | Sub-oscillator level | 0–127 |
| 22 | Sub-oscillator type | Discrete: −2oct asym / −2oct sym / −1oct sym |
| 23 | Noise level | 0–127 (also Riser level when Riser active) |
| 24 | Filter envelope depth | 0–127 |
| 25 | Filter LFO depth | 0–127 |
| 26 | Filter keyboard follow | 0–127 (internal 0–255; max = perfect tracking) |
| 27 | Filter bend sensitivity | 0–127 (internal 0–255) |
| 28 | Amp envelope mode | Discrete: Gate / Envelope |
| 29 | Envelope trigger mode | Discrete: LFO / Gate / Gate+Trig |
| 30 | Envelope sustain | 0–127 |
| 31 | Portamento mode | Discrete: OFF / On / Auto (legato only) |
| 64 | Damper (sustain) pedal | 0–63 off, 64–127 on |
| 65 | Portamento switch | 0–127 (overlaps with CC31) |
| 71 | Filter resonance | 0–127 (self-oscillation at max) |
| 72 | Envelope release | 0–127 |
| 73 | Envelope attack | 0–127 |
| 74 | Filter cutoff | 0–127 |
| 75 | Envelope decay | 0–127 |
| 76 | Oscillator fine tune | 0–127 (±1 octave) |
| 77 | Keyboard transpose | 0–127 (±60 semitones) |
| 78 | Noise mode | Discrete: Pink / White |
| 79 | LFO mode | Discrete: Normal / Fast |
| 80 | Polyphony mode | Discrete: Mono / Unison / Poly / Chord |
| 81 | Chord voice 2 on/off | 0–63 off, 64–127 on |
| 82 | Chord voice 3 on/off | 0–63 off, 64–127 on |
| 83 | Chord voice 4 on/off | 0–63 off, 64–127 on |
| 85 | Chord voice 2 key shift | 0–127 (maps to −12 to +12 semitones) |
| 86 | Chord voice 3 key shift | 0–127 (maps to −12 to +12 semitones) |
| 87 | Chord voice 4 key shift | 0–127 (maps to −12 to +12 semitones) |
| 89 | Reverb time | 0–127 (internal 0–255) |
| 90 | Delay time | 0–127 (1–740 ms free, or synced note values) |
| 91 | Reverb level | 0–127 (internal 0–255) |
| 92 | Delay level | 0–127 (internal 0–255) |
| 93 | Chorus type | Discrete: OFF / 1 / 2 / 3 / 4 |
| 102 | OSC Draw multiply | 0–127 (internal 1.0–32.0) |
| 103 | OSC Chop overtone | 0–127 (internal 0–200) |
| 104 | OSC Chop comb | 0–127 (internal 1.0–32.0) |
| 105 | LFO key trigger | Discrete: OFF / ON |
| 106 | LFO sync mode | Discrete: OFF / ON (firmware v1.02+) |
| 107 | OSC Draw step/slope | Discrete: OFF / Step / Slope |

### MIDI channel and configuration

Default synth channel is **3** (Roland designed 1=J-6, 2=T-8, 3=S-1, 4=E-4 for AIRA Compact daisy-chaining). Program change channel is **16**. Both configurable 1–16 via menu. The S-1 operates in MIDI Mode 3 (Poly) or Mode 4.

### Pitch bend

Received and transmitted. Range is **configurable via CC18** (oscillator) and **CC27** (filter). Not a fixed ±2 semitone default — it scales continuously from zero to ±2 octaves for pitch and 0–255 for filter. There is no panel pitch bend wheel; the unit relies on external MIDI or D-Motion tilt.

### Aftertouch

**Not supported.** The official MIDI implementation chart does not list channel aftertouch or polyphonic aftertouch as recognized messages. Do not rely on aftertouch for expressive control.

### Note priority and voice stealing

Configurable via menu parameter `n.Pri`: **last-note priority** (default) or **lowest-note priority**. When envelope trigger is Gate+Trig (CC29), the unit forces last-note priority regardless of this setting. In Poly mode, standard round-robin voice allocation applies with oldest-voice stealing when all 4 are occupied.

### MIDI clock

The S-1 transmits and receives MIDI clock, Start, and Stop. LFO sync (CC106) and delay sync lock to received clock. The internal sequencer and arpeggiator also sync to external clock.

### Critical MIDI gotchas

- **No Local Off mode.** The S-1 echoes incoming MIDI notes back to its output. In a DAW environment, this creates feedback loops unless your DAW's MIDI routing explicitly filters the echo. This is the single most common complaint for DAW integration.
- **CC65 and CC31 overlap** — both relate to portamento switching, and their interaction is ambiguously documented.
- **Discrete-valued CCs** (CC12, 14, 16, 22, 28, 29, 31, 78, 79, 80, 93, 105, 106, 107) jump between states rather than sweeping continuously. Sending intermediate values selects the nearest discrete state — watch for unexpected snaps in generative automation.
- **Filter frequency motion recording bug** (firmware v1.02): Recording filter cutoff (CC74) motion into the internal sequencer can produce corrupted playback. CC values sent over external MIDI appear clean — the bug is in the pattern record routine only.

---

## 8. Known tricks, oddities, and workarounds

### Self-oscillating filter as a sine source

Set all oscillator levels (CC19, 20, 21, 23) to 0. Set CC71 (resonance) to 127. Set CC26 (keyboard follow) to 127. Adjust CC74 (cutoff) to tune the pitch. You now have a playable sine wave — **4 of them in Poly mode**. Use short envelopes for mallet/bell tones, or sustain for pure drones and sub-bass. Community members use this for kick drum synthesis by setting a low range and short decay.

### Audio-rate LFO for FM-like effects

Set CC79 (LFO Mode) to Fast. Crank CC3 (LFO Rate) high. Route to oscillator pitch (CC13) for sidebands, or to filter cutoff (CC25) for aggressive growling textures. Combined with self-oscillating filter, this produces genuine FM bell tones: all oscillators off, resonance maxed, keyboard follow maxed, audio-rate LFO modulating cutoff. The LFO **does not track keyboard pitch**, so FM timbres shift across the register — a limitation, but exploitable for evolving generative textures.

### The 1/128 delay trick

Set delay time to 1/128 note (tempo synced). Crank delay feedback. The extremely short delay time creates **metallic, comb-filter-like resonances**. Combined with high reverb, this produces "howling metallic textures" (Engadget). Useful for industrial or experimental sound design.

### OSC Chop as a pseudo-sync/ring-mod substitute

Since there is no oscillator sync or ring mod, OSC Chop (CC103, CC104) is your primary tool for inharmonic, metallic timbres. Chop Comb values above 8.0 create pronounced comb-filter effects. Overtone values above 100 reverse phase on chopped segments, generating aggressive upper partials. This only works below ~1 kHz fundamental — above that, chop has no audible effect.

### Hidden riser mode

**Hold Shift + press pads 1 and 2 simultaneously** to cycle through riser modes: OFF, Sync (quarter-note upbeat sweeps), Quiver (accelerating intervals), QuivPan (accelerating with stereo panning). The riser function is **not MIDI-mappable** — a limitation for external control.

### Stereo output phase cancellation trap

The S-1's MIX OUT is stereo (TRRS). Using a **mono TS cable causes phase cancellation**, potentially resulting in no audible signal. Always use a stereo TRS-to-dual-mono splitter or a stereo cable.

### Pattern reload without power cycling

Turning knobs during playback alters the patch, and these changes persist if you switch patterns and return. The **only way to reload the saved state** without power cycling is the `rLod` command (menu item #37).

### USB vs TRS MIDI differences

**USB-C**: Class-compliant audio + MIDI + charging on a single cable. No driver needed on macOS; Windows may require one. The S-1 registers as a USB audio interface — on iPad, it takes over as the system audio device, which can complicate multi-device setups. Ground loop noise is reported when connected to powered equipment; a USB isolator (iFi iDefender or ADUM3160) helps.

**TRS MIDI**: Requires **Type A** (BOSS/Roland standard). This is the most common connectivity complaint — Type B cables will not work. Roland does not include adapters. The BOSS BMIDI-5-35 is the recommended adapter.

Both transports carry identical MIDI data. The USB path adds audio streaming and the no-local-off echo problem; TRS MIDI avoids the echo issue since the S-1's note echo appears to be USB-specific behavior.

### Differences from the original SH-101

| Aspect | Original SH-101 | S-1 ACB emulation |
|---|---|---|
| Tuning stability | Analog drift, requires warm-up | Rock-solid, never drifts |
| Bass saturation | Warmer, more saturated at low frequencies | Slightly thinner, cleaner |
| Polyphony | Monophonic only | 4-voice poly/unison/chord |
| Sub-oscillator | −1 octave square only | −1 oct square, −2 oct square, −2 oct pulse |
| LFO waveforms | Triangle, square, random | 6 waveforms including inverse saw and noise |
| Effects | None | Chorus, delay, reverb |
| Extra oscillator tools | None | OSC Draw, OSC Chop, Riser |
| Noise type | Fixed (white) | Selectable pink/white |
| Sequencer | Basic step sequencer | 64-step with motion, probability, sub-steps |
| Patch storage | None on SH-101 (SH-01A had separate patch/sequence storage) | 64 patterns bundling patch + sequence together |

### Non-linear CC behaviors to watch

- **CC14 (Oscillator Range)**: Discrete octave jumps, not continuous pitch sweep.
- **CC71 (Resonance) above ~120**: Sharp cliff into self-oscillation — small CC changes produce dramatic timbral shifts.
- **CC80, 93, 12, 22** and other discrete CCs: Snap between states, not smooth transitions.
- **CC102 (Draw Multiply), CC104 (Chop Comb)**: Logarithmic-feeling mapping — doubling the internal value doubles the frequency effect, so the upper CC range compresses many octaves into a small value span.
- **CC103 (Chop Overtone)**: Behavior flips at internal value 100 (approximately CC64) — below is progressive muting, above is phase-reversed emphasis. This is a hard behavioral boundary.

---

## 9. Sound design recipes with CC values

### Bass (classic SH-101 sub)

CC80=Mono or Unison. CC19=0, CC20=127 (saw only), CC21=127 (sub maxed), CC22=−1oct. CC74=60–80 (partially closed filter). CC71=20–40 (mild resonance). CC24=70 (moderate envelope-to-filter). CC73=0, CC75=70, CC30=20, CC72=30. For the fattest result, use Unison mode — four detuned voices push enormous sub energy. Community advice: "Try NOT to use resonance — the 101 can sound very nice without it if tweaked right."

### Lead (acid squelch)

CC80=Mono. CC19=127 (square), CC20=0. CC74=40–60 (low cutoff as starting point). CC71=100–120 (high resonance for squelch, just below self-oscillation). CC24=80–100 (heavy envelope sweep). CC73=0, CC75=90–110, CC30=0, CC72=50. CC5=10–20 (short portamento for acid slides), CC31=Auto. Automate CC74 via generative sequencer for evolving acid lines.

### Pad (warm polyphonic)

CC80=Poly. CC20=127, CC19=80 (saw + pulse blend). CC15=95, CC16=LFO (PWM for movement). CC3=35 (slow LFO). CC74=65–80. CC71=15–30 (gentle resonance). CC73=50–70 (slow attack), CC75=90, CC30=100–127, CC72=70–80 (long release). CC93=Type 1 (JUNO chorus for stereo width). CC91=60–90 (reverb). The JUNO-derived chorus is integral to the S-1 pad sound — it transforms a thin 4-voice polysynth into something convincingly lush.

### Pluck

CC80=Poly. CC20=127 or CC19=127 (saw or square). CC74=25 (closed filter). CC24=100–127 (maximum envelope sweep). CC73=0, CC75=40–60 (short decay), CC30=0, CC72=15. CC71=40–60 (resonance adds a "ping" to the attack transient). CC26=80–100 (keyboard follow opens filter for higher notes). Short decay + high filter envelope depth is the essential pluck formula.

### Bell (FM via self-oscillating filter)

CC19=0, CC20=0, CC21=0, CC23=0 (all oscillators off). CC71=127 (self-oscillation). CC26=127 (keyboard follow for pitch tracking). CC74=tune to desired pitch. CC79=Fast (audio-rate LFO). CC3=100–120 (high LFO rate). CC25=40–70 (filter LFO depth controls harmonic richness). CC73=0, CC75=60–80, CC30=10–30, CC72=40. CC80=Poly for polyphonic bells. The inharmonicity from the non-tracking LFO adds metallic character.

### Noise percussion

CC23=127 (noise dominant), CC19=0, CC20=0, CC21=0. CC78=White for hi-hats, Pink for darker hits. CC74=90–127. CC24=80–127 (envelope sweep). CC73=0, CC75=10–30 (very short decay), CC30=0, CC72=5–10. For kick: add CC21=127 (sub), CC22=−2oct, set CC14 to lowest range, CC75=20–40. For snare: CC23=100, CC19=60 (noise + square burst), CC75=15–25.

### Drone

CC80=Unison (maximum thickness). CC20=127, CC19=100, CC15=90, CC16=LFO. CC3=15–25 (very slow LFO). CC25=20–35 (slow filter undulation). CC74=55–70. CC73=100–127 (very slow attack), CC30=127, CC72=127 (infinite sustain and release). CC91=90–127 (deep reverb), CC89=100+ (long reverb time). CC92=50–80 (delay adds spatial depth). Use the Hold button or sustain pedal (CC64) for indefinite sustain. The Unison mode detuning combined with slow PWM and deep reverb creates massive, evolving textures.

### Resonance as a tonal tool

Filter resonance is far more than a cutoff-sweep accessory. At **CC71 0–30**, it adds subtle warmth and presence around the cutoff frequency. At **CC71 40–70**, it creates nasal, vowel-like formant character — useful for "talking" bass lines. At **CC71 80–110**, it produces a dramatic singing peak that, with keyboard follow at maximum, creates a tuned resonant body effect — the filter becomes an additional pitched element interacting with the oscillators. At **CC71 120–127**, self-oscillation creates beat frequencies against the oscillator signal, yielding complex interference patterns useful for experimental and drone work. In generative contexts, slowly sweeping CC71 alongside CC74 produces more timbral variety than cutoff movement alone.

---

## Conclusion: pragmatic assessment for generative MIDI CC work

The S-1's 54 CC parameters cover every synthesis parameter that matters, making it an excellent generative target — you can build and morph entire patches from an external sequencer without touching the hardware. The core SH-101 engine delivers convincing analog character, and the **4 independent voice paths with per-voice filtering** give it genuine polyphonic depth rare at this price point.

The critical constraints to design around are the **single shared ADSR** (you cannot independently shape filter and amplitude envelopes), the **absence of oscillator sync, ring mod, and FM** (audio-rate LFO is your only inharmonic tool), and the **no-local-off problem** over USB. For generative work specifically, watch the discrete-valued CCs that snap rather than sweep (CC14, 80, 93, 12, 22) and the sharp resonance cliff above CC71 ~120. The OSC Draw and Chop systems are the S-1's secret weapons — they extend the timbral range well beyond what any SH-101 clone normally offers, and they are fully CC-addressable. The JUNO-derived chorus, tempo-synced delay with tail persistence, and 7 reverb types complete a surprisingly capable effects palette for a $199 pocket synth. Route your generative automation to CC74, CC71, CC25, CC3, CC15, and CC92 as your primary timbral axes, and you will find the S-1 responds with more character and range than its size suggests.
