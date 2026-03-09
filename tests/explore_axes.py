"""
Exploration script for axes.py output structure.
DO NOT MODIFY the production codebase.
This script tests the analysis pipeline independently.
"""
import sys
import os

# Add scripts directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))

import axes
import json

def test_small_data():
    """Test with very small synthetic data."""
    print("=== Test: Small Synthetic Data ===")
    data = b"AAAA" * 100 + b"BBBB" * 100 + b"CCCC" * 100
    result = axes.run_best_axis(data, sample_size=1024, window_size=128, max_windows=16)
    
    print(f"Best View: {result.get('best_view')}")
    print(f"Score: {result.get('score')}")
    print(f"Timeline Length: {len(result.get('timeline', []))}")
    print(f"Metrics: {json.dumps(result.get('metrics', {}), indent=2)}")
    print(f"Evidence: {result.get('evidence')}")
    print()

def test_random_data():
    """Test with random-ish data (high entropy)."""
    print("=== Test: Random-ish Data ===")
    import random
    data = bytes([random.randint(0, 255) for _ in range(50000)])
    result = axes.run_best_axis(data, sample_size=16000, window_size=512, max_windows=32)
    
    print(f"Best View: {result.get('best_view')}")
    print(f"Score: {result.get('score')}")
    print(f"Timeline Length: {len(result.get('timeline', []))}")
    
    timeline = result.get('timeline', [])
    if timeline:
        entropies = [t['entropy'] for t in timeline]
        print(f"Entropy Range: {min(entropies):.2f} - {max(entropies):.2f}")
        print(f"Mean Entropy: {sum(entropies)/len(entropies):.2f}")
    
    print(f"Metrics: {json.dumps(result.get('metrics', {}), indent=2)}")
    print()

def test_structured_data():
    """Test with structured/repeating data."""
    print("=== Test: Structured Repeating Data ===")
    pattern = b"LOG: 2025-01-22 INFO - Application started.\n" * 200
    result = axes.run_best_axis(pattern, sample_size=8000, window_size=256, max_windows=32)
    
    print(f"Best View: {result.get('best_view')}")
    print(f"Score: {result.get('score')}")
    print(f"Timeline Length: {len(result.get('timeline', []))}")
    
    timeline = result.get('timeline', [])
    if timeline:
        entropies = [t['entropy'] for t in timeline]
        print(f"Entropy Range: {min(entropies):.2f} - {max(entropies):.2f}")
        print(f"Mean Entropy: {sum(entropies)/len(entropies):.2f}")
    
    print(f"Metrics: {json.dumps(result.get('metrics', {}), indent=2)}")
    print()

def show_playback_buffer_mapping():
    """Demonstrate how the server creates the 256-step playback buffer."""
    print("=== Playback Buffer Creation Logic ===")
    # Simulating line 170-178 from willickr_mcp.py
    content = "A" * 1000 + "Z" * 1000  # 2000 chars
    preview_len = 256
    step_sz = max(1, len(content) // preview_len)  # 2000 // 256 = 7
    
    playback_buffer = [ord(c) for c in content[::step_sz][:preview_len]]
    
    print(f"Content Length: {len(content)}")
    print(f"Step Size: {step_sz}")
    print(f"Buffer Length: {len(playback_buffer)}")
    print(f"First 10 values: {playback_buffer[:10]}")
    print(f"Last 10 values: {playback_buffer[-10:]}")
    print()

if __name__ == "__main__":
    print("=" * 60)
    print("Willickr Axes.py Exploration")
    print("=" * 60)
    print()
    
    test_small_data()
    test_random_data()
    test_structured_data()
    show_playback_buffer_mapping()
    
    print("Exploration complete.")
