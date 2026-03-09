import React, { useState } from 'react';
import { createPortal } from 'react-dom';

// Help Modal for User Manual
const HelpModal = ({ onClose, sendCommand }) => {
  const [instruction, setInstruction] = useState("");
  const [sent, setSent] = useState(false);

  const handleSend = () => {
    if (!instruction.trim()) return;
    sendCommand({ action: "update_agent_instruction", text: instruction });
    setSent(true);
    setTimeout(() => setSent(false), 3000);
  };


  return createPortal(
    <div
      style={{ position: 'fixed', top: 0, left: 0, width: '100vw', height: '100vh', zIndex: 99999, background: 'rgba(0,0,0,0.9)', display: 'flex', alignItems: 'center', justifyContent: 'center' }}
    >
      <div className="bg-[#0f0f15] border border-white/10 rounded-xl w-full max-w-4xl h-full max-h-[85vh] flex flex-col shadow-2xl overflow-hidden relative">
        <button onClick={onClose} className="absolute top-4 right-4 text-white/40 hover:text-white transition-colors z-10">✕</button>

        <div className="p-6 border-b border-white/10 flex justify-between items-center bg-[#13131a] relative">
          <div>
            <h2 className="text-xl font-bold tracking-tight text-white">OPERATOR MANUAL</h2>
            <div className="text-xs text-white/40 font-mono mt-1">WILLICKR GENERATIVE ENGINE v2.0</div>
          </div>
          {sent && <div className="absolute right-12 top-1/2 -translate-y-1/2 text-green-400 text-xs font-mono animate-pulse">✓ INSTRUCTION SENT</div>}
        </div>

        <div className="p-8 overflow-y-auto font-sans space-y-10 text-white/80 leading-relaxed custom-scrollbar">

          <section>
            <h3 className="text-cyan-400 font-mono text-sm tracking-widest mb-3 uppercase border-b border-cyan-400/20 pb-2">1. Operating the Interface</h3>
            <ul className="list-disc pl-5 space-y-2 text-sm text-white/60">
              <li><b>Header</b>: Use Play/Stop to control the engine. Select visual Styles (Chaos, Baroque) to change the generator algorithms.</li>
              <li><b>Pipeline (Left)</b>: Click Data Sources (e.g. "USGS QUAKES") to fetch live data. This primes the engine with raw entropy.</li>
              <li><b>Track View (Center)</b>: Monitor active voices. Mute/Solo tracks to arrange the composition in real-time.</li>
            </ul>
          </section>

          <section className="bg-white/5 p-6 rounded-lg border border-white/10">
            <h3 className="text-purple-400 font-mono text-sm tracking-widest mb-4 uppercase flex items-center gap-2">
              <span className="w-2 h-2 rounded-full bg-purple-400 animate-pulse" />
              2. Instructing the Agent
            </h3>
            <p className="mb-4 text-sm text-white/70">
              The Agent can autonomously configure the engine based on your high-level intent. Send an instruction below to guide its behavior.
            </p>
            <div className="space-y-3">
              <textarea
                className="w-full bg-black/40 border border-white/10 rounded p-3 text-sm text-white/90 focus:border-purple-500/50 outline-none font-mono resize-none h-24"
                placeholder="e.g. 'Analyze the earthquake data and create a tense, chaotic soundscape using the Whole Tone scale.'"
                value={instruction}
                onChange={(e) => setInstruction(e.target.value)}
              />
              <button
                onClick={handleSend}
                className="px-4 py-2 bg-purple-600/20 border border-purple-500/50 text-purple-300 text-xs font-mono rounded hover:bg-purple-600/40 transition-all tracking-wider disabled:opacity-50"
                disabled={!instruction.trim()}
              >
                SEND INSTRUCTION TO CONDUCTOR
              </button>
            </div>
          </section>

          <section>
            <h3 className="text-green-400 font-mono text-sm tracking-widest mb-3 uppercase border-b border-green-400/20 pb-2">3. Boot Sequence</h3>
            <div className="grid grid-cols-2 gap-6">
              <div className="text-sm">
                <div className="font-bold text-white mb-2">Step A: Start Environment</div>
                <code className="block bg-black/50 p-2 rounded text-xs font-mono text-white/50 mb-2">
                  python server/willickr_mcp.py
                </code>
                <p className="text-white/40 text-xs">Starts the Engine, WebSocket Server (Port 3001), and MCP Tools.</p>
              </div>
              <div className="text-sm">
                <div className="font-bold text-white mb-2">Step B: Launch Agent</div>
                <code className="block bg-black/50 p-2 rounded text-xs font-mono text-white/50 mb-2">
                  antigravity
                </code>
                <p className="text-white/40 text-xs">Opens the Agent interface. Connects to the Engine via MCP.</p>
              </div>
            </div>
          </section>

          <section>
            <h3 className="text-white/40 font-mono text-sm tracking-widest mb-3 uppercase border-b border-white/10 pb-2">4. Architecture</h3>
            <p className="text-sm mb-2 text-white/60">The engine runs a real-time 16th-note clock loop with 3 default voices.</p>
            <div className="grid grid-cols-3 gap-4 text-xs font-mono text-white/50">
              <div className="p-2 border border-white/5 rounded text-center">CH 1: KICK</div>
              <div className="p-2 border border-white/5 rounded text-center">CH 2: BASS</div>
              <div className="p-2 border border-white/5 rounded text-center">CH 3: LEAD</div>
            </div>
          </section>

        </div>
      </div>
    </div>
    , document.body);
};

export default HelpModal;
