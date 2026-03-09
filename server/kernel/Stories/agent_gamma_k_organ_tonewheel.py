"""
Agent Gamma-K: Tonewheel Organ Transcription
Source: Gordon Reid's Synth Secrets (Chapters 53-57)

Acoustic Theory & Translation Strategy:
- Hammond Tonewheels generate almost pure sine waves at specific harmonic intervals (Drawbars).
- The S-1 cannot do perfect additive synthesis. We approximate the 88 8000 000 registration by heavily mixing the Sub-oscillator (16' equivalent) and the Square wave (odd harmonics).
- Filter Resonance is completely suppressed (CC 71: 0) to avoid artificial peaks, letting the raw oscillator mixture pass.
- B3 Key Click is a well-known artifact of the mechanical busbar contacts. We emulate this using a micro-envelope on the filter cutoff: instant attack, extremely fast decay.
- The Amp Envelope is a pure Gate: instant attack, maximum sustain, instant release.

Taxonomic Application:
[Origin: Strike/Artifacting] + [Behavior: Static] + [Emotion: Euphoria/Tension] + [Stress: Safe-Mode] + [Role: Lead] + [Historical: Organ-Emulation]
"""

import time
from s1_midi import Midi, CC

def main():
    s1 = Midi(channel=2)
    s1.panic()
    time.sleep(0.5)

    print("--- Loading Patch: Tonewheel Organ (Gamma-K) ---")

    # 1. Oscillator Mix: Sub + Square to mimic fundamental/odd harmonic drawbars
    s1.cc(CC.SUB_LEVEL, 127)
    s1.cc(CC.OSC_SQUARE, 110)
    s1.cc(CC.SAW_LEVEL, 0) # Suppress saw to avoid too much brightness
    s1.cc(CC.NOISE_LEVEL, 0)

    # 2. Envelope (VCA): Pure Gate (Instant On/Off)
    s1.cc(CC.AMP_ATTACK, 0)
    s1.cc(CC.AMP_DECAY, 0)
    s1.cc(CC.AMP_SUSTAIN, 127)
    s1.cc(CC.AMP_RELEASE, 0) # Instant release for organ

    # 3. Filter: Suppress resonance, create key click
    s1.cc(CC.FILTER_RES, 0)
    s1.cc(CC.FILTER_CUTOFF, 80) # Open enough for the square wave harmonics
    
    # Key-Click emulation via shared Envelope (Affects Filter)
    # Note: Since VCA and VCF share the envelope, setting Decay to 15 while Sustain is max 
    # means the filter drops from (Cutoff + Env_Depth) down to Cutoff very quickly!
    s1.cc(CC.AMP_DECAY, 15)      # Fast decay for the click
    s1.cc(CC.FILTER_ENV, 50)     # Depth of the key click transient

    # 4. LFO: Chorus/Vibrato scanner emulation (C-3 style)
    s1.cc(CC.LFO_MODE, 0) # Normal Mode
    s1.cc(CC.LFO_RATE, 65) # Approx 6Hz scanner speed
    s1.cc(CC.PITCH, 0) # Use the Chorus effect instead of raw pitch mod for a richer sound 

    # 5. Effects: Chorus gives us the Scanner V/C sound, overdrive via high volume
    s1.cc(CC.CHORUS_LEVEL, 90)
    s1.cc(CC.REVERB_LEVEL, 60) # A100 Spring Reverb imitation
    s1.cc(CC.DELAY_LEVEL, 0)

    print("Tonewheel Organ patch loaded.")

    # Demonstration
    demo_riff = [
        (60, 0.2), (63, 0.2), (65, 0.4), (60, 0.2), (63, 0.2), (66, 0.1), (65, 0.3),
        (60, 0.2), (63, 0.2), (65, 0.4), (63, 0.2), (60, 0.4)
    ]

    for note, dur in demo_riff:
        s1.on(note, velocity=100)
        time.sleep(dur)
        s1.off(note)
        time.sleep(0.05)

    print("Demo complete.")

if __name__ == "__main__":
    main()
