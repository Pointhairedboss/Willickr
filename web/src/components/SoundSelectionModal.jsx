import React from 'react';
import { createPortal } from 'react-dom';

// Sound Presets for Ambient Context
export const SOUND_PRESETS = [
  { name: "Acoustic Grand", program: 0, category: "Keys" },
  { name: "Electric Piano 1", program: 4, category: "Keys" },
  { name: "Vibraphone", program: 11, category: "Keys" },
  { name: "Rock Organ", program: 18, category: "Keys" },
  { name: "Acoustic Bass", program: 32, category: "Bass" },
  { name: "Electric Bass", program: 33, category: "Bass" },
  { name: "Synth Bass 1", program: 38, category: "Bass" },
  { name: "Violin", program: 40, category: "Strings" },
  { name: "String Ensemble 1", program: 48, category: "Strings" },
  { name: "Synth Strings 1", program: 50, category: "Strings" },
  { name: "Voice Oohs", program: 53, category: "Strings" },
  { name: "Lead 1 (Square)", program: 80, category: "Synth" },
  { name: "Pad 1 (New Age)", program: 88, category: "Pad" },
  { name: "Pad 2 (Warm)", program: 89, category: "Pad" },
  { name: "Pad 4 (Choir)", program: 91, category: "Pad" },
  { name: "Pad 8 (Sweep)", program: 95, category: "Pad" },
  { name: "FX 1 (Rain)", program: 96, category: "FX" },
  { name: "FX 2 (Soundtrack)", program: 97, category: "FX" },
  { name: "FX 4 (Atmosphere)", program: 99, category: "FX" },
];

const SoundSelectionModal = ({ trackName, currentProgram, onSelect, onClose }) => {
  if (!trackName) return null;

  return createPortal(
    <div className="fixed inset-0 z-[100] flex items-center justify-center p-8 backdrop-blur-sm bg-black/80">
      <div className="bg-[#0f0f15] border border-white/10 rounded-xl w-full max-w-lg flex flex-col shadow-2xl overflow-hidden relative animate-in fade-in zoom-in duration-200">
        <button onClick={onClose} className="absolute top-4 right-4 text-white/40 hover:text-white transition-colors">✕</button>

        <div className="p-6 border-b border-white/10 bg-[#13131a]">
          <h2 className="text-xl font-bold tracking-tight text-white">ASSIGN SOUND</h2>
          <div className="text-xs text-white/40 font-mono mt-1">TRACK: <span className="text-cyan-400">{trackName}</span></div>
        </div>

        <div className="p-6 overflow-y-auto max-h-[60vh] custom-scrollbar grid grid-cols-2 gap-2">
          {SOUND_PRESETS.map((p) => (
            <button
              key={p.program}
              onClick={() => onSelect(p.program)}
              className={`text-left p-3 rounded border text-xs font-mono transition-all flex justify-between group ${currentProgram === p.program
                ? 'bg-cyan-500/20 border-cyan-500 text-cyan-300'
                : 'bg-white/5 border-white/5 text-white/60 hover:bg-white/10 hover:border-white/20 hover:text-white'
                }`}
            >
              <span>{p.name.toUpperCase()}</span>
              <span className={`opacity-30 group-hover:opacity-100 ${currentProgram === p.program ? 'text-cyan-300' : 'text-white/30'
                }`}>{p.program}</span>
            </button>
          ))}
        </div>

        <div className="p-4 bg-[#13131a] border-t border-white/10 text-[10px] text-white/30 font-mono text-center">
          Standard GM Mapping. Requires compatible Synth/Soundfont on Backend.
        </div>
      </div>
    </div>,
    document.body
  );
};

export default SoundSelectionModal;
