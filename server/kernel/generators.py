import numpy as np
import random
from typing import List, Union

class Generator:
    @staticmethod
    def euclidean_rhythm(steps: int, pulses: int) -> List[int]:
        """
        Generates a Euclidean rhythm using the Bjorklund algorithm logic.
        Returns a list of 1s (hits) and 0s (rests).
        """
        if pulses >= steps:
            return [1] * steps
        if pulses <= 0:
            return [0] * steps
            
        pattern = []
        counts = [pulses, steps - pulses]
        remainders = [1] * pulses + [0] * (steps - pulses)
        
        # Iterative reduction (simple approximation of Bjorklund for music purposes)
        # Using a simpler distribution method that is functionally equivalent for music
        # (Bresenham line algo approach used in some seqs)
        
        pattern = []
        slope = steps / pulses
        current = 0
        for i in range(pulses):
            idx = int(current)
            pattern.append(idx)
            current += slope
            
        # Convert indices to step array
        result = [0] * steps
        for idx in pattern:
            if idx < steps:
                result[idx] = 1
        return result

    @staticmethod
    def cellular_automaton(rule: int, width: int, generations: int, init_state: List[int] = None) -> List[List[int]]:
        """
        Generates a 1D cellular automaton Grid (e.g., Rule 30).
        Returns list of rows (generations).
        """
        if init_state is None:
            init_state = [0] * width
            init_state[width // 2] = 1 # Center seed
            
        history = [init_state]
        current = init_state
        
        for _ in range(generations - 1):
            next_gen = []
            # Wrap around edges
            extended = [current[-1]] + current + [current[0]]
            
            for i in range(width):
                # Get local neighborhood 3 bits -> integer
                # Left, Self, Right
                neighborhood = (extended[i] << 2) | (extended[i+1] << 1) | extended[i+2]
                
                # Check bit in rule
                bit = (rule >> neighborhood) & 1
                next_gen.append(bit)
            
            history.append(next_gen)
            current = next_gen
            
        return history

    @staticmethod
    def quantize_to_scale(values: List[float], scale_root: int, scale_type: str = "major") -> List[int]:
        """
        Maps normalized 0-1 values to MIDI notes constrained to a scale.
        """
        # Offsets from root
        scales = {
            "major": [0, 2, 4, 5, 7, 9, 11],
            "minor": [0, 2, 3, 5, 7, 8, 10],
            "pentatonic": [0, 2, 4, 7, 9],
            "chromatic": list(range(12))
        }
        intervals = scales.get(scale_type, scales["major"])
        
        # Expand scale across octaves (e.g., 3 octaves = 36 semitones)
        # range C2 (36) to C5 (72)
        base_note = 36 + (scale_root % 12)
        range_span = 36 # 3 octaves
        
        result_notes = []
        
        full_scale = []
        for octave in range(4):
            for interval in intervals:
                note = base_note + (octave * 12) + interval
                full_scale.append(note)
        
        full_scale.sort()
        if not full_scale: return []
        
        min_note = full_scale[0]
        max_note = full_scale[-1]
        
        for v in values:
            # Map 0-1 to index in full_scale
            idx = int(v * (len(full_scale) - 1))
            idx = max(0, min(idx, len(full_scale) - 1))
            result_notes.append(full_scale[idx])
            
        return result_notes

# Helper for testing
if __name__ == "__main__":
    print(Generator.euclidean_rhythm(16, 5))
    print(Generator.quantize_to_scale([0.1, 0.5, 0.9], 60, "minor"))
