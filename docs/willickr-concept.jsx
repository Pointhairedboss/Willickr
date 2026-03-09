import React, { useState, useEffect, useRef, useCallback } from 'react';

// ═══════════════════════════════════════════════════════════════════════════════
// WILLICKR: THE COMPUTATIONAL DATA LOOM
// Design Concept: "Data Alchemy" Interface
// ═══════════════════════════════════════════════════════════════════════════════

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
  const x = (1-t)*(1-t)*startX + 2*(1-t)*t*controlX + t*t*endX;
  const y = (1-t)*(1-t)*startY + 2*(1-t)*t*controlY + t*t*endY;
  
  return (
    <div 
      className="absolute w-2 h-2 -translate-x-1/2 -translate-y-1/2 pointer-events-none"
      style={{
        left: x,
        top: y,
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

// The Loom - Main visualization viewport
const TheLoom = ({ mode = 'terrain', scanProgress = 0 }) => {
  const canvasRef = useRef(null);
  const [dimensions, setDimensions] = useState({ width: 0, height: 0 });
  
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const updateDimensions = () => {
      const rect = canvas.parentElement.getBoundingClientRect();
      setDimensions({ width: rect.width, height: rect.height });
      canvas.width = rect.width * window.devicePixelRatio;
      canvas.height = rect.height * window.devicePixelRatio;
    };
    
    updateDimensions();
    window.addEventListener('resize', updateDimensions);
    return () => window.removeEventListener('resize', updateDimensions);
  }, []);
  
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    const dpr = window.devicePixelRatio;
    const width = canvas.width;
    const height = canvas.height;
    
    // Clear
    ctx.fillStyle = '#0a0a0f';
    ctx.fillRect(0, 0, width, height);
    
    // Draw based on mode
    if (mode === 'terrain') {
      // Simulated terrain heightmap visualization
      const gridSize = 40;
      const rows = Math.ceil(height / (gridSize * dpr)) + 1;
      const cols = Math.ceil(width / (gridSize * dpr)) + 1;
      
      ctx.strokeStyle = 'rgba(0, 255, 200, 0.15)';
      ctx.lineWidth = 1;
      
      // Draw perspective grid
      for (let row = 0; row < rows; row++) {
        ctx.beginPath();
        for (let col = 0; col <= cols; col++) {
          const x = col * gridSize * dpr;
          const baseY = row * gridSize * dpr;
          
          // Simulated height based on position (creates rolling hills)
          const noise = Math.sin(col * 0.3) * Math.cos(row * 0.2) * 30 +
                       Math.sin(col * 0.1 + row * 0.1) * 20;
          const y = baseY - noise * dpr;
          
          if (col === 0) ctx.moveTo(x, y);
          else ctx.lineTo(x, y);
        }
        ctx.stroke();
      }
      
      // Draw vertical connections
      for (let col = 0; col < cols; col++) {
        ctx.beginPath();
        for (let row = 0; row <= rows; row++) {
          const x = col * gridSize * dpr;
          const baseY = row * gridSize * dpr;
          const noise = Math.sin(col * 0.3) * Math.cos(row * 0.2) * 30 +
                       Math.sin(col * 0.1 + row * 0.1) * 20;
          const y = baseY - noise * dpr;
          
          if (row === 0) ctx.moveTo(x, y);
          else ctx.lineTo(x, y);
        }
        ctx.stroke();
      }
      
      // Scan line
      const scanX = scanProgress * width;
      const gradient = ctx.createLinearGradient(scanX - 100, 0, scanX + 20, 0);
      gradient.addColorStop(0, 'transparent');
      gradient.addColorStop(0.8, 'rgba(0, 255, 200, 0.3)');
      gradient.addColorStop(1, 'rgba(0, 255, 200, 0.8)');
      
      ctx.fillStyle = gradient;
      ctx.fillRect(scanX - 100, 0, 120, height);
      
      // Scan line itself
      ctx.strokeStyle = '#00ffc8';
      ctx.lineWidth = 2 * dpr;
      ctx.beginPath();
      ctx.moveTo(scanX, 0);
      ctx.lineTo(scanX, height);
      ctx.stroke();
      
      // Data extraction points along scan line
      for (let i = 0; i < 8; i++) {
        const y = (height / 8) * i + (height / 16);
        const pointSize = 4 * dpr;
        
        ctx.fillStyle = '#00ffc8';
        ctx.beginPath();
        ctx.arc(scanX, y, pointSize, 0, Math.PI * 2);
        ctx.fill();
        
        // Glow
        const glowGradient = ctx.createRadialGradient(scanX, y, 0, scanX, y, 20 * dpr);
        glowGradient.addColorStop(0, 'rgba(0, 255, 200, 0.5)');
        glowGradient.addColorStop(1, 'transparent');
        ctx.fillStyle = glowGradient;
        ctx.fillRect(scanX - 20 * dpr, y - 20 * dpr, 40 * dpr, 40 * dpr);
      }
    }
    
    // Vignette overlay
    const vignetteGradient = ctx.createRadialGradient(
      width / 2, height / 2, height * 0.3,
      width / 2, height / 2, height * 0.8
    );
    vignetteGradient.addColorStop(0, 'transparent');
    vignetteGradient.addColorStop(1, 'rgba(0, 0, 0, 0.6)');
    ctx.fillStyle = vignetteGradient;
    ctx.fillRect(0, 0, width, height);
    
    // Scanlines overlay
    ctx.fillStyle = 'rgba(0, 0, 0, 0.03)';
    for (let i = 0; i < height; i += 4) {
      ctx.fillRect(0, i, width, 2);
    }
    
  }, [mode, scanProgress, dimensions]);
  
  return (
    <div className="relative w-full h-full overflow-hidden rounded-lg" style={{ background: '#0a0a0f' }}>
      <canvas 
        ref={canvasRef} 
        className="absolute inset-0 w-full h-full"
        style={{ imageRendering: 'pixelated' }}
      />
      
      {/* Corner brackets */}
      <div className="absolute top-2 left-2 w-8 h-8 border-l-2 border-t-2 border-cyan-400/30" />
      <div className="absolute top-2 right-2 w-8 h-8 border-r-2 border-t-2 border-cyan-400/30" />
      <div className="absolute bottom-2 left-2 w-8 h-8 border-l-2 border-b-2 border-cyan-400/30" />
      <div className="absolute bottom-2 right-2 w-8 h-8 border-r-2 border-b-2 border-cyan-400/30" />
      
      {/* Mode indicator */}
      <div 
        className="absolute top-4 left-4 px-3 py-1 rounded"
        style={{ 
          background: 'rgba(0, 255, 200, 0.1)',
          border: '1px solid rgba(0, 255, 200, 0.3)',
        }}
      >
        <span 
          style={{ 
            fontFamily: '"JetBrains Mono", monospace',
            fontSize: '10px',
            color: '#00ffc8',
            letterSpacing: '0.1em',
          }}
        >
          MODE: TERRAIN_WALKER
        </span>
      </div>
      
      {/* Coordinates */}
      <div 
        className="absolute bottom-4 right-4"
        style={{ 
          fontFamily: '"JetBrains Mono", monospace',
          fontSize: '10px',
          color: 'rgba(255,255,255,0.3)',
        }}
      >
        SCAN: {(scanProgress * 100).toFixed(1)}%
      </div>
    </div>
  );
};

// Activity Log with Ghost indication
const ActivityLog = ({ entries }) => {
  return (
    <div 
      className="space-y-2 max-h-48 overflow-y-auto custom-scrollbar"
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

// Main Application
export default function WillickrConcept() {
  const [scanProgress, setScanProgress] = useState(0);
  const [showSpawnedControl, setShowSpawnedControl] = useState(false);
  const [ghostHands, setGhostHands] = useState([]);
  const [sliderValues, setSliderValues] = useState({
    intensity: 0.7,
    chaos: 0.3,
    resonance: 0.5,
  });
  const [xyValue, setXYValue] = useState({ x: 0.5, y: 0.5 });
  
  const activityLog = [
    { time: '00:12:34', message: 'Terrain data loaded: himalaya_dem.tif', isAI: false },
    { time: '00:12:35', message: 'Analyzing elevation gradients...', isAI: true },
    { time: '00:12:36', message: 'Configured INTENSITY → 70% (optimal for terrain)', isAI: true },
    { time: '00:12:38', message: 'Spawning CHAOS control for ridge variation', isAI: true },
    { time: '00:12:40', message: 'Beginning terrain walk at coordinates (0, 0)', isAI: true },
    { time: '00:12:42', message: 'Mapping elevation to MIDI pitch (C2-C6)', isAI: true },
  ];
  
  // Animate scan progress
  useEffect(() => {
    const interval = setInterval(() => {
      setScanProgress(p => (p + 0.002) % 1);
    }, 50);
    return () => clearInterval(interval);
  }, []);
  
  // Spawn the chaos control after delay
  useEffect(() => {
    const timer = setTimeout(() => setShowSpawnedControl(true), 2000);
    return () => clearTimeout(timer);
  }, []);
  
  // Simulate ghost hand activity
  useEffect(() => {
    const interval = setInterval(() => {
      const newHand = {
        id: Date.now(),
        x: `${Math.random() * 80 + 10}%`,
        y: `${Math.random() * 80 + 10}%`,
        label: ['FILTER', 'RESONANCE', 'ATTACK', 'DECAY'][Math.floor(Math.random() * 4)],
      };
      setGhostHands(prev => [...prev.slice(-3), newHand]);
    }, 3000);
    return () => clearInterval(interval);
  }, []);
  
  return (
    <div 
      className="min-h-screen p-6"
      style={{ 
        background: 'linear-gradient(135deg, #0a0a0f 0%, #0f0f18 50%, #0a0a0f 100%)',
        fontFamily: '"Inter", system-ui, sans-serif',
      }}
    >
      {/* Load fonts */}
      <style>{`
        @import url('https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;500&family=Space+Grotesk:wght@400;500;600&family=Inter:wght@400;500&display=swap');
        
        .custom-scrollbar::-webkit-scrollbar {
          width: 4px;
        }
        .custom-scrollbar::-webkit-scrollbar-track {
          background: rgba(255,255,255,0.05);
        }
        .custom-scrollbar::-webkit-scrollbar-thumb {
          background: rgba(0, 255, 200, 0.3);
          border-radius: 2px;
        }
        
        @keyframes dataFlow {
          0% { stroke-dashoffset: 20; }
          100% { stroke-dashoffset: 0; }
        }
      `}</style>
      
      {/* Header */}
      <header className="flex items-center justify-between mb-6">
        <div className="flex items-center gap-4">
          <h1 
            className="text-2xl font-semibold tracking-tight"
            style={{ 
              fontFamily: '"Space Grotesk", sans-serif',
              color: 'rgba(255,255,255,0.95)',
            }}
          >
            WILLICKR
          </h1>
          <span 
            className="px-2 py-0.5 rounded text-xs tracking-widest"
            style={{ 
              background: 'rgba(168, 85, 247, 0.2)',
              color: '#a855f7',
              fontFamily: '"JetBrains Mono", monospace',
              border: '1px solid rgba(168, 85, 247, 0.3)',
            }}
          >
            DATA LOOM
          </span>
        </div>
        
        <div 
          className="flex items-center gap-2"
          style={{ fontFamily: '"JetBrains Mono", monospace', fontSize: '11px' }}
        >
          <div className="w-2 h-2 rounded-full bg-green-400 animate-pulse" />
          <span style={{ color: 'rgba(255,255,255,0.5)' }}>AGENT ACTIVE</span>
        </div>
      </header>
      
      {/* Main Grid */}
      <div className="grid grid-cols-12 gap-4" style={{ height: 'calc(100vh - 120px)' }}>
        
        {/* Left Panel - Translation Pipeline */}
        <div className="col-span-3 space-y-4">
          <div 
            className="p-4 rounded-lg"
            style={{ 
              background: 'rgba(255,255,255,0.02)',
              border: '1px solid rgba(255,255,255,0.06)',
            }}
          >
            <h2 
              className="text-xs tracking-widest uppercase mb-4"
              style={{ 
                fontFamily: '"JetBrains Mono", monospace',
                color: 'rgba(255,255,255,0.4)',
                letterSpacing: '0.2em',
              }}
            >
              Translation Pipeline
            </h2>
            
            <div className="space-y-3 relative">
              {/* Connection lines */}
              <svg className="absolute inset-0 w-full h-full pointer-events-none overflow-visible" style={{ zIndex: 0 }}>
                <defs>
                  <linearGradient id="lineGradient1" x1="0%" y1="0%" x2="0%" y2="100%">
                    <stop offset="0%" stopColor="#3b82f6" stopOpacity="0.5" />
                    <stop offset="100%" stopColor="#a855f7" stopOpacity="0.5" />
                  </linearGradient>
                  <linearGradient id="lineGradient2" x1="0%" y1="0%" x2="0%" y2="100%">
                    <stop offset="0%" stopColor="#a855f7" stopOpacity="0.5" />
                    <stop offset="100%" stopColor="#00ffc8" stopOpacity="0.5" />
                  </linearGradient>
                </defs>
                <line x1="50%" y1="72" x2="50%" y2="100" stroke="url(#lineGradient1)" strokeWidth="2" strokeDasharray="4 4" style={{ animation: 'dataFlow 1s linear infinite' }} />
                <line x1="50%" y1="178" x2="50%" y2="206" stroke="url(#lineGradient2)" strokeWidth="2" strokeDasharray="4 4" style={{ animation: 'dataFlow 1s linear infinite' }} />
              </svg>
              
              <div style={{ position: 'relative', zIndex: 1 }}>
                <PipelineNode type="input" label="himalaya_dem.tif" active>
                  <div className="text-xs mt-2" style={{ color: 'rgba(255,255,255,0.4)' }}>
                    Elevation Data • 4096×4096
                  </div>
                </PipelineNode>
              </div>
              
              <div style={{ position: 'relative', zIndex: 1 }}>
                <PipelineNode type="algorithm" label="Terrain Walker" active>
                  <div className="text-xs mt-2" style={{ color: 'rgba(255,255,255,0.4)' }}>
                    Scanline • 120 BPM
                  </div>
                </PipelineNode>
              </div>
              
              <div style={{ position: 'relative', zIndex: 1 }}>
                <PipelineNode type="output" label="MIDI Ch. 1" active>
                  <div className="text-xs mt-2" style={{ color: 'rgba(255,255,255,0.4)' }}>
                    Pitch: C2-C6 • Velocity: Dynamic
                  </div>
                </PipelineNode>
              </div>
            </div>
          </div>
          
          {/* Activity Log */}
          <div 
            className="p-4 rounded-lg flex-1"
            style={{ 
              background: 'rgba(255,255,255,0.02)',
              border: '1px solid rgba(255,255,255,0.06)',
            }}
          >
            <h2 
              className="text-xs tracking-widest uppercase mb-3"
              style={{ 
                fontFamily: '"JetBrains Mono", monospace',
                color: 'rgba(255,255,255,0.4)',
                letterSpacing: '0.2em',
              }}
            >
              Agent Activity
            </h2>
            <ActivityLog entries={activityLog} />
          </div>
        </div>
        
        {/* Center - The Loom */}
        <div className="col-span-6 relative">
          <TheLoom mode="terrain" scanProgress={scanProgress} />
          
          {/* Ghost Hands overlay */}
          {ghostHands.map(hand => (
            <GhostHand 
              key={hand.id}
              x={hand.x}
              y={hand.y}
              label={hand.label}
              intensity={0.8}
            />
          ))}
          
          {/* Data Sparks */}
          {[...Array(5)].map((_, i) => (
            <DataSpark
              key={i}
              startX={scanProgress * 100 + '%'}
              startY="50%"
              endX="100%"
              endY={`${20 + i * 15}%`}
              delay={i * 400}
            />
          ))}
        </div>
        
        {/* Right Panel - Ephemeral Controls */}
        <div className="col-span-3 space-y-4">
          <div 
            className="p-4 rounded-lg"
            style={{ 
              background: 'rgba(255,255,255,0.02)',
              border: '1px solid rgba(255,255,255,0.06)',
            }}
          >
            <h2 
              className="text-xs tracking-widest uppercase mb-4"
              style={{ 
                fontFamily: '"JetBrains Mono", monospace',
                color: 'rgba(255,255,255,0.4)',
                letterSpacing: '0.2em',
              }}
            >
              Parameters
            </h2>
            
            <div className="space-y-6">
              <EphemeralSlider 
                label="Intensity"
                value={sliderValues.intensity}
                onChange={(v) => setSliderValues(prev => ({ ...prev, intensity: v }))}
                color="#00ffc8"
              />
              
              <EphemeralSlider 
                label="Resonance"
                value={sliderValues.resonance}
                onChange={(v) => setSliderValues(prev => ({ ...prev, resonance: v }))}
                color="#3b82f6"
              />
              
              {/* Spawned control */}
              {showSpawnedControl && (
                <div className="relative">
                  <div 
                    className="absolute -top-2 -right-2 px-1.5 py-0.5 rounded text-xs"
                    style={{
                      background: 'rgba(168, 85, 247, 0.2)',
                      color: '#a855f7',
                      fontFamily: '"JetBrains Mono", monospace',
                      fontSize: '8px',
                      border: '1px solid rgba(168, 85, 247, 0.3)',
                    }}
                  >
                    AI SPAWNED
                  </div>
                  <EphemeralSlider 
                    label="Chaos"
                    value={sliderValues.chaos}
                    onChange={(v) => setSliderValues(prev => ({ ...prev, chaos: v }))}
                    spawned
                    color="#a855f7"
                  />
                </div>
              )}
            </div>
          </div>
          
          {/* XY Pad */}
          <div 
            className="p-4 rounded-lg"
            style={{ 
              background: 'rgba(255,255,255,0.02)',
              border: '1px solid rgba(255,255,255,0.06)',
            }}
          >
            <EphemeralXYPad 
              label="Harmonic Space"
              value={xyValue}
              onChange={setXYValue}
              color="#ff6b35"
            />
          </div>
          
          {/* Output Meters */}
          <div 
            className="p-4 rounded-lg"
            style={{ 
              background: 'rgba(255,255,255,0.02)',
              border: '1px solid rgba(255,255,255,0.06)',
            }}
          >
            <h2 
              className="text-xs tracking-widest uppercase mb-3"
              style={{ 
                fontFamily: '"JetBrains Mono", monospace',
                color: 'rgba(255,255,255,0.4)',
                letterSpacing: '0.2em',
              }}
            >
              Output
            </h2>
            
            <div className="space-y-2">
              {['PITCH', 'VELOCITY', 'GATE'].map((label, i) => {
                const value = Math.sin(Date.now() / 1000 + i) * 0.3 + 0.5;
                return (
                  <div key={label} className="flex items-center gap-3">
                    <span 
                      className="w-16 text-xs"
                      style={{ 
                        fontFamily: '"JetBrains Mono", monospace',
                        color: 'rgba(255,255,255,0.4)',
                        fontSize: '9px',
                      }}
                    >
                      {label}
                    </span>
                    <div 
                      className="flex-1 h-1.5 rounded-full overflow-hidden"
                      style={{ background: 'rgba(255,255,255,0.05)' }}
                    >
                      <div 
                        className="h-full rounded-full transition-all duration-100"
                        style={{
                          width: `${value * 100}%`,
                          background: 'linear-gradient(90deg, #00ffc8, #00ffc8)',
                          boxShadow: '0 0 8px rgba(0, 255, 200, 0.5)',
                        }}
                      />
                    </div>
                  </div>
                );
              })}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
