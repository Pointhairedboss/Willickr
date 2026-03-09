"""
Test the exact ordered buffer creation logic from the server.
"""
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "scripts"))

import axes

def test_server_logic():
    print("=== Testing Server Ordered Buffer Logic ===\n")
    
    # Create test content
    content = "2025-01-22 INFO Starting application...\n" * 500
    print(f"Content length: {len(content)} bytes")
    
    # Run analysis (like the server does)
    result = axes.run_best_axis(content, sample_size=256000, window_size=4096, max_windows=160)
    
    print(f"Best view: {result.get('best_view')}")
    print(f"Order indices type: {type(result.get('order_indices', []))}")
    order_indices = result.get("order_indices", [])
    if order_indices:
        print(f"First index type: {type(order_indices[0])}")
        print(f"First 5 indices: {order_indices[:5]}")
    
    # Replicate server logic
    preview_len = 256
    content_bytes = content.encode('utf-8', errors='ignore')
    
    step_sz_linear = max(1, len(content) // preview_len)
    linear_buffer = [ord(c) for c in content[::step_sz_linear][:preview_len]]
    
    window_size = 4096
    
    try:
        if order_indices and len(content_bytes) > window_size:
            sample_size = min(256000, len(content_bytes))
            sample = content_bytes[:sample_size]
            
            original_windows = []
            for i in range(0, len(sample) - window_size + 1, window_size):
                original_windows.append(sample[i:i + window_size])
            
            print(f"Original windows count: {len(original_windows)}")
            print(f"Order indices count: {len(order_indices)}")
            
            # This line might fail with numpy int64
            valid_indices = [idx for idx in order_indices if idx < len(original_windows)]
            print(f"Valid indices count: {len(valid_indices)}")
            
            if valid_indices:
                reordered_content = b"".join(original_windows[idx] for idx in valid_indices)
                step_sz_ordered = max(1, len(reordered_content) // preview_len)
                ordered_buffer = list(reordered_content[::step_sz_ordered][:preview_len])
                print(f"Ordered buffer length: {len(ordered_buffer)}")
                print(f"First 10 ordered: {ordered_buffer[:10]}")
            else:
                ordered_buffer = linear_buffer
                print("Fell back to linear (no valid indices)")
        else:
            ordered_buffer = linear_buffer
            print("Fell back to linear (no order_indices or content too small)")
            
    except Exception as e:
        print(f"ERROR: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_server_logic()
