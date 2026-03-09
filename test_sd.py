import sounddevice as sd
import queue

q = queue.Queue()

def cb(indata, frames, time, status):
    q.put(indata.copy())

dev_id = None
for i, d in enumerate(sd.query_devices()):
    if d['max_input_channels'] > 0 and ('S-1' in d['name'].upper() or 'ROLAND' in d['name'].upper()):
        dev_id = i
        break

print(f"Device ID: {dev_id}")
if dev_id is not None:
    try:
        stream = sd.InputStream(device=dev_id, channels=2, callback=cb)
        with stream:
            data = q.get(timeout=2.0)
            print(f"Success, got data chunk of shape {data.shape}")
    except Exception as e:
        print(f"Error: {e}")
