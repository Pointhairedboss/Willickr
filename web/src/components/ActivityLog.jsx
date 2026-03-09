import React from 'react';

// Activity Log with Ghost indication
const ActivityLog = ({ entries }) => {
  return (
    <div
      className="space-y-2"
      style={{
        fontFamily: '"JetBrains Mono", monospace',
        fontSize: '11px',
      }}
    >
      {entries.map((entry, i) => (
        <div
          key={i}
          className="flex items-start gap-2 py-1 px-2 rounded transition-colors"
          style={{
            background: entry.isAI ? 'rgba(0, 255, 200, 0.05)' : 'transparent',
            borderLeft: entry.isAI ? '2px solid #00ffc8' : '2px solid transparent',
          }}
        >
          {entry.isAI && (
            <span
              className="w-2 h-2 rounded-full mt-1 flex-shrink-0 animate-pulse"
              style={{ background: '#00ffc8', boxShadow: '0 0 8px #00ffc8' }}
            />
          )}
          <span style={{ color: 'rgba(255,255,255,0.5)' }}>{entry.time}</span>
          <span style={{ color: entry.isAI ? '#00ffc8' : 'rgba(255,255,255,0.7)' }}>
            {entry.message}
          </span>
        </div>
      ))}
    </div>
  );
};

export default ActivityLog;
