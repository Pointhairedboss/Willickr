import React from 'react';
import TrackView from './TrackView';

// The Loom - Now renders TrackView
const TheLoom = ({ engineState, capabilities, onUpdateTrack, onOpenSoundModal }) => {
  return (
    <div className="relative w-full h-full bg-[#0a0a0f] border border-white/10 rounded-lg overflow-hidden shadow-inner">
      {/* Grid Background */}
      <div
        className="absolute inset-0 opacity-20 pointer-events-none"
        style={{
          backgroundImage: 'linear-gradient(rgba(255,255,255,0.05) 1px, transparent 1px), linear-gradient(90deg, rgba(255,255,255,0.05) 1px, transparent 1px)',
          backgroundSize: '20px 20px'
        }}
      />
      <TrackView engineState={engineState} capabilities={capabilities} onUpdateTrack={onUpdateTrack} onOpenSoundModal={onOpenSoundModal} />
    </div>
  );
};

export default TheLoom;
