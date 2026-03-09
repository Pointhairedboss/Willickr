"""
Test script to verify that linear and ordered buffers are actually different.
"""
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))

import axes

def test_buffer_difference():
    print("=== Testing Buffer Difference ===\n")
    
    # Create test content - a simple log-like pattern
    content = "2025-01-22 INFO Starting application...\n" * 100
    content += "2025-01-22 ERROR Something went wrong!\n" * 50  
    content += "2025-01-22 DEBUG Debugging output here\n" * 100
    
    print(f"Content length: {len(content)} bytes")
    
    # Run analysis (like the server does)
    result = axes.run_best_axis(content, sample_size=16000, window_size=512, max_windows=32)
    
    print(f"Best view: {result.get('best_view')}")
    print(f"Timeline length: {len(result.get('timeline', []))}")
    
    # Get ordered_stream
    ordered_stream = result.get("ordered_stream", b"")
    print(f"Ordered stream length: {len(ordered_stream)} bytes")
    
    # Create LINEAR buffer (like server does)
    preview_len = 256
    step_sz_linear = max(1, len(content) // preview_len)
    linear_buffer = [ord(c) for c in content[::step_sz_linear][:preview_len]]
    
    # Create ORDERED buffer
    if isinstance(ordered_stream, bytes) and len(ordered_stream) > 0:
        step_sz_ordered = max(1, len(ordered_stream) // preview_len)
        ordered_buffer = list(ordered_stream[::step_sz_ordered][:preview_len])
    else:
        ordered_buffer = linear_buffer
        print("WARNING: ordered_buffer fell back to linear_buffer!")
    
    print(f"\nLinear buffer: {len(linear_buffer)} samples")
    print(f"Ordered buffer: {len(ordered_buffer)} samples")
    
    # Compare buffers
    if linear_buffer == ordered_buffer:
        print("\n*** BUFFERS ARE IDENTICAL! ***")
        print("This explains why the music sounds the same.")
    else:
        # Count differences
        diff_count = sum(1 for a, b in zip(linear_buffer, ordered_buffer) if a != b)
        print(f"\nBuffers differ at {diff_count} / {min(len(linear_buffer), len(ordered_buffer))} positions")
        print(f"That's {diff_count / len(linear_buffer) * 100:.1f}% different")
    
    print("\n--- First 20 values comparison ---")
    print(f"Linear:  {linear_buffer[:20]}")
    print(f"Ordered: {ordered_buffer[:20]}")
    
    print("\n--- Last 20 values comparison ---")
    print(f"Linear:  {linear_buffer[-20:]}")
    print(f"Ordered: {ordered_buffer[-20:]}")

if __name__ == "__main__":
    test_buffer_difference()
