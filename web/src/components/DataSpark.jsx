import React, { useState, useEffect } from 'react';

// Data Spark - particles that fly from data source to output
const DataSpark = ({ startX, startY, endX, endY, delay = 0, color = '#00ffc8' }) => {
  const [progress, setProgress] = useState(0);
  const [visible, setVisible] = useState(false);

  useEffect(() => {
    const startTimer = setTimeout(() => {
      setVisible(true);
      const interval = setInterval(() => {
        setProgress(p => {
          if (p >= 1) {
            clearInterval(interval);
            setTimeout(() => {
              setProgress(0);
              setVisible(false);
              setTimeout(() => setVisible(true), Math.random() * 2000);
            }, 100);
            return 1;
          }
          return p + 0.02;
        });
      }, 16);
      return () => clearInterval(interval);
    }, delay);
    return () => clearTimeout(startTimer);
  }, [delay]);

  if (!visible) return null;

  // Bezier curve for smooth arc
  const controlX = (startX + endX) / 2;
  const controlY = Math.min(startY, endY) - 50;

  const t = progress;
  const x = (1 - t) * (1 - t) * startX + 2 * (1 - t) * t * controlX + t * t * endX;
  const y = (1 - t) * (1 - t) * startY + 2 * (1 - t) * t * controlY + t * t * endY;

  return (
    <div
      className="absolute w-2 h-2 -translate-x-1/2 -translate-y-1/2 pointer-events-none"
      style={{
        left: `${x}%`,
        top: `${y}%`,
        opacity: 1 - progress * 0.5,
      }}
    >
      <div
        className="w-full h-full rounded-full"
        style={{
          background: color,
          boxShadow: `0 0 10px ${color}, 0 0 20px ${color}80`,
        }}
      />
      {/* Trail */}
      <div
        className="absolute w-8 h-0.5 -left-8 top-1/2 -translate-y-1/2"
        style={{
          background: `linear-gradient(90deg, transparent, ${color}60)`,
          transform: `rotate(${Math.atan2(endY - startY, endX - startX) * 180 / Math.PI}deg)`,
          transformOrigin: 'right center',
        }}
      />
    </div>
  );
};

export default DataSpark;
