import React, { useState, useEffect } from 'react';

// Ephemeral Control - "Grown" slider that spawns organically
const EphemeralSlider = ({ label, value, onChange, spawned = false, color = '#00ffc8' }) => {
  const [grown, setGrown] = useState(!spawned);
  const [localValue, setLocalValue] = useState(value);

  useEffect(() => {
    if (spawned) {
      const timer = setTimeout(() => setGrown(true), 100);
      return () => clearTimeout(timer);
    }
  }, [spawned]);

  const handleChange = (e) => {
    const newVal = parseFloat(e.target.value);
    setLocalValue(newVal);
    onChange?.(newVal);
  };

  return (
    <div
      className="relative transition-all duration-700 ease-out"
      style={{
        opacity: grown ? 1 : 0,
        transform: `scaleY(${grown ? 1 : 0}) translateY(${grown ? 0 : -20}px)`,
        transformOrigin: 'top center',
      }}
    >
      {/* Spawn particles */}
      {spawned && !grown && (
        <div className="absolute inset-0 flex items-center justify-center">
          {[...Array(6)].map((_, i) => (
            <div
              key={i}
              className="absolute w-1 h-1 rounded-full animate-ping"
              style={{
                background: color,
                left: `${50 + Math.cos(i * Math.PI / 3) * 30}%`,
                top: `${50 + Math.sin(i * Math.PI / 3) * 30}%`,
                animationDelay: `${i * 100}ms`,
              }}
            />
          ))}
        </div>
      )}

      {/* Label */}
      <div
        className="text-xs tracking-widest mb-2 uppercase"
        style={{
          color: color,
          fontFamily: '"JetBrains Mono", monospace',
          fontSize: '10px',
          letterSpacing: '0.2em',
          opacity: 0.8,
        }}
      >
        {label}
      </div>

      {/* Track container */}
      <div className="relative h-2 rounded-full overflow-hidden" style={{ background: 'rgba(255,255,255,0.05)' }}>
        {/* Active fill with glow */}
        <div
          className="absolute inset-y-0 left-0 rounded-full transition-all duration-150"
          style={{
            width: `${localValue * 100}%`,
            background: `linear-gradient(90deg, ${color}40, ${color})`,
            boxShadow: `0 0 15px ${color}60`,
          }}
        />
        {/* Scanline effect */}
        <div
          className="absolute inset-0 opacity-20"
          style={{
            background: 'repeating-linear-gradient(0deg, transparent, transparent 1px, rgba(255,255,255,0.1) 1px, rgba(255,255,255,0.1) 2px)',
          }}
        />
      </div>

      {/* Invisible range input */}
      <input
        type="range"
        min="0"
        max="1"
        step="0.01"
        value={localValue}
        onChange={handleChange}
        className="absolute inset-0 w-full opacity-0 cursor-pointer"
        style={{ height: '24px', top: '16px' }}
      />

      {/* Value display */}
      <div
        className="text-right mt-1"
        style={{
          fontFamily: '"JetBrains Mono", monospace',
          fontSize: '11px',
          color: 'rgba(255,255,255,0.4)',
        }}
      >
        {(localValue * 100).toFixed(0)}%
      </div>
    </div>
  );
};

export default EphemeralSlider;
