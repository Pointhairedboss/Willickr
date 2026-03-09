import React from 'react';

// Pipeline Node - visualizes a step in the translation chain
const PipelineNode = ({ type, label, active, children }) => {
  const colors = {
    input: '#3b82f6',
    algorithm: '#a855f7',
    output: '#00ffc8',
  };
  const color = colors[type] || '#666';

  return (
    <div className="relative">
      {/* Connection line (rendered by parent) */}

      {/* Node container */}
      <div
        className="relative p-4 rounded-lg transition-all duration-300"
        style={{
          background: active ? `${color}10` : 'rgba(255,255,255,0.02)',
          border: `1px solid ${active ? color : 'rgba(255,255,255,0.1)'}`,
          boxShadow: active ? `0 0 30px ${color}20, inset 0 0 30px ${color}05` : 'none',
        }}
      >
        {/* Type badge */}
        <div
          className="text-xs tracking-widest uppercase mb-2"
          style={{
            color: color,
            fontFamily: '"JetBrains Mono", monospace',
            fontSize: '9px',
            letterSpacing: '0.15em',
          }}
        >
          {type}
        </div>

        {/* Label */}
        <div
          className="font-medium"
          style={{
            color: 'rgba(255,255,255,0.9)',
            fontFamily: '"Space Grotesk", sans-serif',
            fontSize: '14px',
          }}
        >
          {label}
        </div>

        {/* Active indicator */}
        {active && (
          <div
            className="absolute -right-1 top-1/2 -translate-y-1/2 w-2 h-2 rounded-full animate-pulse"
            style={{ background: color, boxShadow: `0 0 10px ${color}` }}
          />
        )}

        {children}
      </div>
    </div>
  );
};

export default PipelineNode;
