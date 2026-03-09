import os

app_path = r'c:\Users\Owner\OneDrive\Documents\code\willickr\web\src\App.jsx'

with open(app_path, 'r', encoding='utf-8') as f:
    lines = f.readlines()

imports = """import GhostHand from './components/GhostHand';
import EphemeralSlider from './components/EphemeralSlider';
import EphemeralXYPad from './components/EphemeralXYPad';
import PipelineNode from './components/PipelineNode';
import DataSpark from './components/DataSpark';
import SoundSelectionModal from './components/SoundSelectionModal';
import TrackView from './components/TrackView';
import TheLoom from './components/TheLoom';
import ActivityLog from './components/ActivityLog';
import HelpModal from './components/HelpModal';
"""

new_lines = []
new_lines.extend(lines[0:8])
new_lines.append(imports + '\n')

singleton_idx = -1
for i, line in enumerate(lines):
    if line.startswith('// Singleton WebSocket'):
        singleton_idx = i
        break

main_app_idx = -1
for i, line in enumerate(lines):
    if line.startswith('// Main Application'):
        main_app_idx = i
        break

if singleton_idx != -1:
    new_lines.append(lines[singleton_idx])
    new_lines.append(lines[singleton_idx+1])
    new_lines.append('\n')

if main_app_idx != -1:
    new_lines.extend(lines[main_app_idx:])

with open(app_path, 'w', encoding='utf-8') as f:
    f.writelines(new_lines)

print("Modification complete.")
