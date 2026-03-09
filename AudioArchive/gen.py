import numpy as np
import soundfile as sf
import os

sample_rate = 44100
duration = 10.0 # seconds
t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)

# Generate a high drone (440Hz + 880Hz so it's VERY audible)
frequency = 440.0 # Hz (A4)
drone = 0.5 * np.sin(2 * np.pi * frequency * t) + 0.25 * np.sin(2 * np.pi * frequency * 2 * t)
drone = np.column_stack((drone, drone)) # Stereo
sf.write("ambient_drone.wav", drone, sample_rate, subtype='PCM_16')

# Generate a rhythmic drum loop (simple noise burst loop)
bpm = 120
beats_per_sec = bpm / 60
samples_per_beat = int(sample_rate / beats_per_sec)

drums = np.zeros(len(t))
for i in range(0, len(t), samples_per_beat):
    end = min(i + int(sample_rate * 0.1), len(t))
    drums[i:end] = np.random.uniform(-1, 1, end - i) * np.exp(-np.linspace(0, 5, end - i))

drums = np.column_stack((drums, drums)) * 0.5
sf.write("drums_break.wav", drums, sample_rate, subtype='PCM_16')

print("Generated dummy WAVs successfully!")
