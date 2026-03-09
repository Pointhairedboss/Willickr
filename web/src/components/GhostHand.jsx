import React, { useState, useEffect } from 'react';

// Ghost Hand Activity Indicator - shows AI "touching" parameters
const GhostHand = ({ x, y, label, intensity = 1, delay = 0 }) => {
  const [visible, setVisible] = useState(false);

  useEffect(() => {
    const timer = setTimeout(() => setVisible(true), delay);
    return () => clearTimeout(timer);
  }, [delay]);

  return (
    <div
      className="absolute pointer-events-none transition-all duration-700"
      style={{
        left: x,
        top: y,
        opacity: visible ? intensity * 0.9 : 0,
        transform: `translate(-50%, -50%) scale(${visible ? 1 : 0.5})`,
      }}
    >
      {/* Ripple effect */}
      <div className="absolute inset-0 -m-8">
        <div
          className="w-16 h-16 rounded-full animate-ping"
          style={{
            background: 'radial-gradient(circle, rgba(0,255,200,0.3) 0%, transparent 70%)',
            animationDuration: '2s'
          }}
        />
      </div>
      {/* Core glow */}
      <div
        className="w-3 h-3 rounded-full"
        style={{
          background: 'radial-gradient(circle, #00ffc8 0%, #00a080 50%, transparent 100%)',
          boxShadow: '0 0 20px #00ffc8, 0 0 40px rgba(0,255,200,0.5)',
        }}
      />
      {/* Label */}
      {label && (
        <div
          className="absolute top-6 left-1/2 -translate-x-1/2 whitespace-nowrap text-xs tracking-wider"
          style={{
            color: '#00ffc8',
            fontFamily: '"JetBrains Mono", monospace',
            fontSize: '9px',
            opacity: 0.7,
            textShadow: '0 0 10px rgba(0,255,200,0.5)'
          }}
        >
          {label}
        </div>
      )}
    </div>
  );
};

export default GhostHand;
