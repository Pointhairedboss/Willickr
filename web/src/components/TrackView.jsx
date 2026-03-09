import React from 'react';

const TrackView = ({ engineState, capabilities, onUpdateTrack, onOpenSoundModal }) => {
  if (!engineState || !engineState.tracks) return <div className="text-xs text-white/30 p-4 font-mono flex items-center justify-center h-full">CONNECTING TO ENGINE...</div>;

  return (
    <div className="flex flex-col h-full bg-[#0a0a0f]">
      {/* Header section - static height */}
      <div className="flex-none p-4 pb-2 border-b border-white/5">
        <div className="flex justify-between items-center">
          <div className="text-xs font-mono tracking-widest text-cyan-400">CONDUCTOR MIXER</div>
          <div className="text-[10px] text-white/40 font-mono border border-white/10 px-2 py-1 rounded bg-black/50">
            {engineState.bpm} BPM • {engineState.style.toUpperCase()} • {engineState.scale_name || "SCALE"}
          </div>
        </div>
      </div>

      {/* Tracks list - scrolling area */}
      <div className="flex-1 overflow-y-auto custom-scrollbar p-4 space-y-3">
        {Object.entries(engineState.tracks).map(([name, track]) => (
          <div key={name} className="bg-[#13131a] border border-white/5 rounded p-3 flex items-center justify-between hover:border-white/20 transition-all group shadow-sm">
            {/* Track Info */}
            <div className="flex items-center gap-4 flex-1">
              <div className={`w-1 h-8 rounded-full flex-none ${track.mute ? 'bg-red-500/50' : 'bg-cyan-400 shadow-[0_0_10px_#22d3ee]'}`} />
              <div className="min-w-0 pr-4">
                <div className="text-sm font-bold tracking-wide text-white/90 group-hover:text-cyan-300 transition-colors uppercase truncate">{name}</div>
                <div className="text-[9px] text-white/40 font-mono flex gap-3 mt-1 items-center">
                  <span>CH: <span className="text-white/70">{track.channel + 1}</span></span>
                  <span>PRG: <span className="text-white/70">{track.program === undefined ? '-' : track.program}</span></span>
                  <select
                    value={track.generator || ""}
                    onChange={(e) => onUpdateTrack(name, "generator", e.target.value)}
                    className="bg-purple-900/20 border border-purple-500/30 text-purple-400/80 rounded px-1.5 py-0.5 text-[9px] font-mono outline-none hover:text-purple-300 hover:border-purple-500/50 cursor-pointer transition-colors"
                    title="Generator Algorithm"
                  >
                    <option value="" disabled>NO GEN</option>
                    {capabilities?.generators?.map(gen => (
                      <option key={gen} value={gen}>{gen.toUpperCase()}</option>
                    ))}
                  </select>
                </div>
              </div>
            </div>

            {/* Controls */}
            <div className="flex items-center gap-2">
              <button
                onClick={() => onUpdateTrack(name, "mute", !track.mute)}
                className={`px-3 py-1.5 rounded text-[9px] font-mono border tracking-wider transition-all ${track.mute ? 'bg-red-500/20 border-red-500 text-red-400' : 'bg-white/5 border-white/10 text-white/40 hover:text-white hover:bg-white/10'}`}
              >
                MUTE
              </button>
              <button
                onClick={() => onUpdateTrack(name, "solo", !track.solo)}
                className={`px-3 py-1.5 rounded text-[9px] font-mono border tracking-wider transition-all ${track.solo ? 'bg-yellow-500/20 border-yellow-500 text-yellow-400' : 'bg-white/5 border-white/10 text-white/40 hover:text-white hover:bg-white/10'}`}
              >
                SOLO
              </button>

              <button
                onClick={() => onOpenSoundModal(name)}
                className={`px-3 py-1.5 rounded text-[9px] font-mono border tracking-wider transition-all bg-white/5 border-white/10 text-white/40 hover:text-white hover:bg-white/10 hover:border-cyan-500/50 hover:text-cyan-400`}
              >
                SOUND
              </button>

              {/* Channel Selector */}
              <select
                value={track.channel}
                onChange={(e) => onUpdateTrack(name, "channel", parseInt(e.target.value))}
                className="bg-black/40 border border-white/10 text-[9px] font-mono rounded px-2 py-1.5 w-16 text-right outline-none text-white/60 hover:text-white hover:border-white/30 cursor-pointer"
                title="MIDI Channel"
              >
                {[...Array(16)].map((_, i) => (
                  <option key={i} value={i}>CH {i + 1}</option>
                ))}
              </select>
            </div>
          </div>
        ))}
      </div>

      {/* Visualizer Footer */}
      <div className="mt-8 border-t border-white/5 pt-4">
        <div className="text-[9px] text-white/20 font-mono tracking-widest text-center mb-2">ACTIVE DATA STREAMS</div>
        <div className="h-16 flex gap-1 items-end justify-center opacity-30">
          {[...Array(32)].map((_, i) => (
            <div key={i} className="w-1 bg-cyan-500 rounded-t animate-pulse" style={{ height: `${Math.random() * 100}%`, animationDelay: `${i * 0.05}s` }} />
          ))}
        </div>
      </div>
    </div>
  );
};

export default TrackView;
