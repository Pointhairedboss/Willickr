import React, { useState, useEffect, useRef, useCallback } from 'react';

// XY Pad Control - for 2D parameter space
const EphemeralXYPad = ({ label, value = { x: 0.5, y: 0.5 }, onChange, color = '#ff6b35' }) => {
  const padRef = useRef(null);
  const [localValue, setLocalValue] = useState(value);
  const [isDragging, setIsDragging] = useState(false);

  const handleMove = useCallback((e) => {
    if (!padRef.current) return;
    const rect = padRef.current.getBoundingClientRect();
    const x = Math.max(0, Math.min(1, (e.clientX - rect.left) / rect.width));
    const y = Math.max(0, Math.min(1, 1 - (e.clientY - rect.top) / rect.height));
    setLocalValue({ x, y });
    onChange?.({ x, y });
  }, [onChange]);

  const handleMouseDown = (e) => {
    setIsDragging(true);
    handleMove(e);
  };

  useEffect(() => {
    if (!isDragging) return;
    const handleMouseMove = (e) => handleMove(e);
    const handleMouseUp = () => setIsDragging(false);
    window.addEventListener('mousemove', handleMouseMove);
    window.addEventListener('mouseup', handleMouseUp);
    return () => {
      window.removeEventListener('mousemove', handleMouseMove);
      window.removeEventListener('mouseup', handleMouseUp);
    };
  }, [isDragging, handleMove]);

  return (
    <div>
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

      <div
        ref={padRef}
        className="relative w-full aspect-square rounded cursor-crosshair overflow-hidden"
        style={{
          background: 'rgba(255,255,255,0.03)',
          border: `1px solid ${color}30`,
        }}
        onMouseDown={handleMouseDown}
      >
        {/* Grid lines */}
        <div className="absolute inset-0 opacity-20">
          {[...Array(5)].map((_, i) => (
            <React.Fragment key={i}>
              <div
                className="absolute w-full h-px"
                style={{ top: `${(i + 1) * 16.66}%`, background: `${color}40` }}
              />
              <div
                className="absolute h-full w-px"
                style={{ left: `${(i + 1) * 16.66}%`, background: `${color}40` }}
              />
            </React.Fragment>
          ))}
        </div>

        {/* Crosshair position */}
        <div
          className="absolute w-full h-px transition-all duration-75"
          style={{
            top: `${(1 - localValue.y) * 100}%`,
            background: `linear-gradient(90deg, transparent, ${color}60, transparent)`,
          }}
        />
        <div
          className="absolute h-full w-px transition-all duration-75"
          style={{
            left: `${localValue.x * 100}%`,
            background: `linear-gradient(0deg, transparent, ${color}60, transparent)`,
          }}
        />

        {/* Position indicator */}
        <div
          className="absolute w-4 h-4 -translate-x-1/2 -translate-y-1/2 transition-all duration-75"
          style={{
            left: `${localValue.x * 100}%`,
            top: `${(1 - localValue.y) * 100}%`,
          }}
        >
          <div
            className="w-full h-full rounded-full"
            style={{
              background: `radial-gradient(circle, ${color} 0%, transparent 70%)`,
              boxShadow: `0 0 20px ${color}`,
            }}
          />
        </div>
      </div>

      <div
        className="flex justify-between mt-1"
        style={{
          fontFamily: '"JetBrains Mono", monospace',
          fontSize: '9px',
          color: 'rgba(255,255,255,0.3)',
        }}
      >
        <span>X: {(localValue.x * 100).toFixed(0)}</span>
        <span>Y: {(localValue.y * 100).toFixed(0)}</span>
      </div>
    </div>
  );
};

export default EphemeralXYPad;
