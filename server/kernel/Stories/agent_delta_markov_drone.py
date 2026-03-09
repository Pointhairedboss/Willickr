import time
import random
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from s1_midi import Midi, CC

"""
Agent Delta: Markov Drone Parameter Shifter

Acoustic Theory & Synthesis Strategy:
This script employs a Markov chain to steer the slow evolution of a continuous 
drone. Instead of sequencing notes, it sequences the parameters themselves. 
By constantly, stochastically shifting the LFO Rate and LFO-to-Filter Depth
against a static core waveform, it emulates the slow beating and shifting 
harmonics of a complex multi-operator ambient patch.

Hardware constraints: To prevent voice stealing clicks on a drone, we use
a single voice and never send a Note-Off until the sequence finishes.

Taxonomic Application:
[Origin: System] + [Behavior: Generative] + [Emotion: Tension] + [Stress: Safe-Mode] + [Role: Drone]
"""

# Define states for our Markov chain representing "Moods" or "Textures"
STATES = ["DARK_SUB", "BRIGHT_WASH", "NOISY_FLUTTER", "PULSING_BEAT"]

# Define the transition probabilities
# Format: {Current_State: {Next_State: Probability, ...}}
TRANSITIONS = {
    "DARK_SUB":      {"DARK_SUB": 0.6, "BRIGHT_WASH": 0.2, "NOISY_FLUTTER": 0.1, "PULSING_BEAT": 0.1},
    "BRIGHT_WASH":   {"DARK_SUB": 0.3, "BRIGHT_WASH": 0.5, "NOISY_FLUTTER": 0.1, "PULSING_BEAT": 0.1},
    "NOISY_FLUTTER": {"DARK_SUB": 0.2, "BRIGHT_WASH": 0.2, "NOISY_FLUTTER": 0.4, "PULSING_BEAT": 0.2},
    "PULSING_BEAT":  {"DARK_SUB": 0.2, "BRIGHT_WASH": 0.2, "NOISY_FLUTTER": 0.2, "PULSING_BEAT": 0.4}
}

def get_next_state(current_state):
    """Given a state, returns the next state based on Markov probabilities."""
    probs = TRANSITIONS[current_state]
    rand_val = random.random()
    cumulative = 0.0
    for state, prob in probs.items():
        cumulative += prob
        if rand_val <= cumulative:
            return state
    return current_state # Fallback

def apply_state(synth, state):
    """Translates abstract Markov states into S-1 Parameter Locks."""
    print(f"Agent Delta: Shifting to Texture [ {state} ]")
    
    if state == "DARK_SUB":
        synth.cc(CC.FILTER_CUTOFF, random.randint(20, 40))
        synth.cc(CC.FILTER_RES, random.randint(10, 30))
        synth.cc(CC.NOISE_LEVEL, random.randint(0, 10))
        # Slow LFO Sweeping Filter
        synth.cc(CC.LFO_MODE, 0) # Normal Mode
        synth.cc(CC.LFO_RATE, random.randint(1, 10))
        synth.cc(CC.FILTER_LFO, random.randint(40, 60))
        
    elif state == "BRIGHT_WASH":
        synth.cc(CC.FILTER_CUTOFF, random.randint(80, 110))
        synth.cc(CC.FILTER_RES, random.randint(40, 70))
        synth.cc(CC.NOISE_LEVEL, random.randint(20, 50))
        synth.cc(CC.CHORUS_LEVEL, random.randint(80, 127))
        # Medium LFO
        synth.cc(CC.LFO_MODE, 0)
        synth.cc(CC.LFO_RATE, random.randint(20, 40))
        synth.cc(CC.FILTER_LFO, random.randint(20, 50))
        
    elif state == "NOISY_FLUTTER":
        synth.cc(CC.FILTER_CUTOFF, random.randint(60, 90))
        synth.cc(CC.FILTER_RES, random.randint(80, 110))
        synth.cc(CC.NOISE_LEVEL, random.randint(80, 127))
        synth.cc(CC.LFO_MODE, 127) # Audio-rate mode for flutter
        synth.cc(CC.LFO_RATE, random.randint(40, 100))
        synth.cc(CC.FILTER_LFO, random.randint(50, 127))
        
    elif state == "PULSING_BEAT":
        synth.cc(CC.FILTER_CUTOFF, random.randint(40, 70))
        synth.cc(CC.FILTER_RES, random.randint(90, 120))
        synth.cc(CC.NOISE_LEVEL, random.randint(10, 30))
        synth.cc(CC.LFO_MODE, 0) # Synced or semi-synced pulsing
        synth.cc(CC.LFO_RATE, random.randint(80, 110))
        synth.cc(CC.FILTER_LFO, 127) # Max depth

def run_markov_drone_patch():
    print("Agent Delta: Initializing Markov Drone Parameter Shifter...")
    try:
        synth = Midi()
    except Exception as e:
        print(f"Failed to connect: {e}")
        return

    # Basic setup
    synth.cc(CC.VOLUME, 100)
    synth.cc(CC.OSC_SQUARE, 60)
    synth.cc(CC.SAW_LEVEL, 60)
    synth.cc(CC.SUB_LEVEL, 127)
    
    # Envelope Setup - Drone (infinite sustain until killed)
    synth.cc(CC.AMP_ATTACK, 127) # Slow fade in
    synth.cc(CC.AMP_DECAY, 0)
    synth.cc(CC.AMP_SUSTAIN, 127)
    synth.cc(CC.AMP_RELEASE, 80) # Long fade out
    
    # Delay and Reverb for max ambience
    synth.cc(CC.REVERB_LEVEL, 127)
    synth.cc(CC.DELAY_LEVEL, 100)
    
    # Start the drone
    drone_note = 36 # C2
    synth.on(drone_note, 80)
    
    current_state = "DARK_SUB"
    apply_state(synth, current_state)
    
    print("Drone activated. Evolving via Markov states. Press Ctrl+C to stop.")
    
    try:
        while True:
            # Wait a random duration before the next state shift (3 to 8 seconds)
            time.sleep(random.uniform(3.0, 8.0))
            
            # Transition state
            current_state = get_next_state(current_state)
            apply_state(synth, current_state)
            
            # Add minute micro-drifts between major state changes
            if random.random() < 0.5:
                synth.cc(CC.PITCH, random.randint(0, 10)) # Slight pitch wow
                
    except KeyboardInterrupt:
        print("\nAgent Delta drone terminated. Fading out...")
        synth.off(drone_note)
        time.sleep(2) # Allow release tail before panic
        synth.panic()

if __name__ == "__main__":
    run_markov_drone_patch()
