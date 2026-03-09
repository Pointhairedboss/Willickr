# Agent Alpha: Algorithmic Rules for the S-1

**Mandate**: To synthesize credible acoustic phenomena on the strictly subtractive 4-voice Roland S-1 architecture by applying mathematical acoustics and DSP principles derived from Miller Puckette.

## 1. Harmonic Ratios via Filter Keytracking
When attempting additive synthesis via the subtractive engine, we cannot simply use a generic sawtooth. We must generate precise overtones.

**Rule**: To create artificial formants and simulate specific harmonic partials:
- **Resonance ($Q$)**: Must be pushed high enough to induce self-oscillation or heavily emphasize the cutoff frequency without entering uncontrolled clipping (unless explicitly pursuing `Artifacting`).
- **Cutoff ($\omega_c$)**: Must be tuned to a specific integer multiple of the fundamental frequency ($f_0$) to act as a harmonic partial.
- **Keytracking**: Set to 100% so that the resonant peak tracks the fundamental perfectly across the keyboard, maintaining the $f_0 \times N$ ratio.

*Examples:*
- **Clarinet / Hollow Tube**: Emphasize odd harmonics. Tune filter cutoff to $3f_0$ or $5f_0$.
- **Bowed String**: Emphasize even and odd harmonics. Use a sawtooth, but tune the sub-oscillator exactly one octave down ($f_0 / 2$) and use the filter to emphasize $2f_0$ (the first overtone).

## 2. Pseudo-FM via Audio-Rate Modulation
The S-1 lacks a dedicated FM matrix. We will use Index Modulation by driving the LFO to its absolute maximum frequency.

**Rule**: The Carrier ($C$) is the main oscillator. The Modulator ($M$) is the LFO. The Modulation Index ($I$) is controlled by the LFO depth.
- **Hardware Constraint**: Empirical data proves the S-1's DSP limits LFO speed to a maximum of **~140 Hz**. This fundamentally changes the math. True high-ratio FM ($M >> C$) is only possible in the lower octaves (where $C < 140 \text{ Hz}$).
- **Inharmonicity (Bells, Percussion, Metallic)**: Achieved when $\frac{M}{C}$ is a non-integer fraction (e.g., $1:\sqrt{2}$). Because the S-1 LFO rate is physically capped and un-synced to key tracking, the resulting $\frac{140}{C}$ ratio shifts on *every single key*. As you play up the keyboard, $C$ surpasses $140$, turning the sidebands from bell-like ($M > C$) into subtle chorus/vibrato ($M < C$). This must be exploited for `Strike` physics in the bass/tenor registers exclusively.

## 3. Transient Envelope Mathematics
Perception of physical origin (`Strike`, `Pluck`, `Bow`) depends heavily on the mathematical curve of the attack and decay phases.

**Rule**:
- **Strike (Mallet/Hammer)**: Exponential decay. The filter envelope must have a 0ms attack and a very short exponential decay, routed to both cut-off and pitch (if available) to simulate the brief non-harmonic transient of a physical strike.
- **Pluck (String)**: Linear or slightly exponential decay. Longer decay than a strike, with the filter closing over time to simulate the loss of high-frequency energy as the string loses momentum.
- **Micro-Envelopes for Pseudo-FM**: If true audio-rate LFO is impossible, use the filter envelope with a 0-attack / 0-sustain / 1-decay routed to pitch, with an extreme depth to create a transient pitch-dive (a rapid chirp) that the human ear perceives as a "thwack" or "click" rather than a portamento.

## Directives for Implementation
- Every patch designed under my supervision must document its structural math. If you are modifying the filter cutoff to act as a formant, state the intended harmonic ratio.
- Overdriving the VCA or Filter to create intentional clipping should be mathematically justified (e.g., "Square-wave generation via hard-clipping a sine wave").

*Updated: Modulator ratios finalized based on Agent Epsilon's 140Hz DSP limit constraint.*
