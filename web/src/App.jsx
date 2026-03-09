import React, { useState, useCallback, useRef, useEffect } from 'react';
import { ReactFlow, Controls, Background, applyNodeChanges, applyEdgeChanges, addEdge, Handle, Position, useNodes, useEdges, useReactFlow } from '@xyflow/react';
import '@xyflow/react/dist/style.css';
import { Send, Bot, User, Settings2 } from 'lucide-react';

const initialNodes = [];
const initialEdges = [];

export default function AgenticStudio() {
    // left pane chat state
    const [messages, setMessages] = useState([
        { role: 'assistant', content: 'Agent Zeta online. Semantic Audio Engineer ready for graph wiring. Willickr API endpoints engaged.' }
    ]);
    const [inputValue, setInputValue] = useState('');
    const [isProcessing, setIsProcessing] = useState(false);
    const messagesEndRef = useRef(null);
    
    // NEW: Asset Library State
    const [assets, setAssets] = useState({ inputs: [], algorithms: [], mixdown: [], engines: [] });
    const [searchTerms, setSearchTerms] = useState({ inputs: '', algorithms: '', engines: '' });
    const [globalDuration, setGlobalDuration] = useState(10.0);

    useEffect(() => {
        messagesEndRef.current?.scrollIntoView({ behavior: 'smooth' });
    }, [messages]);
    
    // Load Dynamic Assets
    useEffect(() => {
        fetch('http://127.0.0.1:8000/api/v1/assets')
            .then(res => res.json())
            .then(data => setAssets(data))
            .catch(err => console.error("Failed to load assets API", err));
    }, []);

    const [nodes, setNodes] = useState(initialNodes);
    const [edges, setEdges] = useState(initialEdges);
    
    // NEW: The actual blueprint we are editing
    const [currentBlueprint, setCurrentBlueprint] = useState(null);

    const onNodesChange = useCallback(
        (changes) => setNodes((nds) => applyNodeChanges(changes, nds)),
        [],
    );
    const onEdgesChange = useCallback(
        (changes) => setEdges((eds) => applyEdgeChanges(changes, eds)),
        [],
    );
    const onConnect = useCallback(
        (params) => setEdges((eds) => addEdge({ ...params, animated: true, style: { stroke: '#22d3ee' } }, eds)),
        [],
    );

    const onNodesDelete = useCallback(
        (deleted) => {
            const hasInputDeleted = deleted.find(n => n.type === 'input' || n.type === 'customInput');
            const hasCartridgeDeleted = deleted.find(n => n.type === 'cartridgeNode');
            
            if (hasInputDeleted) {
                setCurrentBlueprint(prev => prev ? { ...prev, midi_file: null } : prev);
                setMessages(prev => [...prev, {
                    role: 'assistant',
                    content: `System update: Input node deleted. Removed data source from blueprint.`
                }]);
            }
            
            if (hasCartridgeDeleted) {
                setCurrentBlueprint(null);
                setMessages(prev => [...prev, {
                    role: 'assistant',
                    content: `System update: Core Cartridge node deleted. Blueprint cleared.`
                }]);
            }
        },
        [setCurrentBlueprint, setMessages]
    );

    // MANUAL BLUEPRINT UPDATE
    const handleSliderChange = (paramKey, newValue) => {
        let globalParams;
        if (!currentBlueprint) {
            globalParams = { "afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.2, [paramKey]: parseFloat(newValue) };
            setCurrentBlueprint({ parameters: globalParams, duration: globalDuration });
        } else {
            globalParams = { ...currentBlueprint.parameters, [paramKey]: parseFloat(newValue) };
            setCurrentBlueprint({ ...currentBlueprint, parameters: globalParams });
        }
        
        // Update visual nodes to match
        setNodes(nds => nds.map(n => {
            if (n.type === 'cartridgeNode') {
                return {
                    ...n,
                    data: { ...n.data, paramObj: { ...n.data.paramObj, ...globalParams } }
                };
            }
            return n;
        }));
    };

    // THE EXECUTE FUNCTION (Now separate from chat)
    const executeBlueprint = async () => {
        if (!currentBlueprint && nodes.length === 0) return;
        
        const hasMixdown = nodes.some(n => n.type === 'mixdownNode');
        const outputNode = nodes.find(n => n.type === 'output' || n.type === 'customOutput');
        const targetEngine = outputNode ? outputNode.data.label.split('\n')[1] : "S1";
        
        let payload, msgStr;
        
        if (hasMixdown) {
            // Build track list logically from the canvas
            let mappedTracks = [];
            
            // Unconnected Inputs (e.g. Direct WAVs)
            const inputs = nodes.filter(n => n.type === 'input' || n.type === 'customInput');
            const cartridges = nodes.filter(n => n.type === 'cartridgeNode');
            
            for (const input of inputs) {
                const filePath = input.data.label.split('\n')[1];
                // Check if this input is connected to a cartridge
                const outEdge = edges.find(e => e.source === input.id);
                if (!outEdge && filePath.toLowerCase().endsWith('.wav')) {
                    // Direct Audio Bypass Channel
                    mappedTracks.push({
                        engine: targetEngine,
                        patch_name: "dummy",
                        midi_file: filePath
                    });
                }
            }
            
            // Cartridge Nodes (Algorithms)
            for (const cart of cartridges) {
                const patchName = cart.data.label.replace('Cartridge: ', ''); // fallback
                const pureName = patchName.split('\n')[0].replace('🔌 ', '').replace('Cartridge: ','').trim();
                
                // Track back to find its input if there is one
                const inEdge = edges.find(e => e.target === cart.id);
                let midiFile = "dummy.mid";
                
                if (inEdge) {
                    const srcInput = nodes.find(n => n.id === inEdge.source);
                    if (srcInput && (srcInput.type === 'input' || srcInput.type === 'customInput')) {
                        midiFile = srcInput.data.label.split('\n')[1];
                    }
                }
                
                mappedTracks.push({
                    engine: targetEngine,
                    patch_name: pureName,
                    midi_file: midiFile
                });
            }
            
            payload = {
                duration: globalDuration,
                parameters: currentBlueprint ? currentBlueprint.parameters : {},
                engine: targetEngine,
                tracks: mappedTracks
            };
            msgStr = `Multitrack Mixdown Bus confirmed. Transporting ${mappedTracks.length} channels to Hardware & Render queues...`;
        } else {
            payload = { ...currentBlueprint, duration: globalDuration };
            msgStr = `Blueprint confirmed. Executing single stem payload for ${payload.patch_name}...`;
        }
        
        setIsProcessing(true);
        setMessages(prev => [...prev, {
            role: 'assistant',
            content: msgStr
        }]);

        try {
            const response = await fetch('http://127.0.0.1:8000/api/v1/render', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json', 'Accept': 'application/json' },
                body: JSON.stringify(payload)
            });
            const data = await response.json();

            setMessages(prev => [...prev, {
                role: 'assistant',
                content: `Hardware Render Initiated! Job ID: ${data.job_id}. Polling status...`
            }]);
            
            const poll = setInterval(async () => {
                try {
                    const statusRes = await fetch(`http://127.0.0.1:8000/api/v1/status/${data.job_id}`);
                    const statusData = await statusRes.json();
                    
                    if (statusData.status === 'complete' || statusData.status === 'error') {
                        clearInterval(poll);
                        setIsProcessing(false);
                        setMessages(prev => [...prev, {
                            role: 'assistant',
                            content: statusData.status === 'complete' 
                                ? `Render Complete! Output saved to server.`
                                : `Render Failed: ${statusData.message}`,
                            audioUrl: statusData.status === 'complete' ? statusData.url : null
                        }]);
                    }
                } catch (e) {
                    clearInterval(poll);
                    setIsProcessing(false);
                }
            }, 2500);
        } catch (error) {
            setIsProcessing(false);
            setMessages(prev => [...prev, {
                role: 'assistant',
                content: `API Connection Error: ${error.message}`
            }]);
        }
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        if (!inputValue.trim() || isProcessing) return;
        
        setMessages(prev => [...prev, { role: 'user', content: inputValue }]);
        const currentCommand = inputValue;
        setInputValue('');
        setIsProcessing(true);

        try {
            setMessages(prev => [...prev, {
                role: 'assistant',
                content: `Analyzing intent: "${currentCommand}"...`
            }]);
            
            const chatRes = await fetch('http://127.0.0.1:8000/api/v1/chat', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ message: currentCommand })
            });
            const chatData = await chatRes.json();
            
            if (!chatData.success) {
                setMessages(prev => [...prev, { role: 'assistant', content: `Agent Error: ${chatData.reply}` }]);
                setIsProcessing(false);
                return;
            }
            
            const payload = chatData.payload;
            setCurrentBlueprint(payload);
            
            // DRAW THE NODES DYNAMICALLY
            const newNodes = [
                { 
                    id: '1', 
                    position: { x: 50, y: 150 }, 
                    data: { 
                        label: payload.midi_file ? `MIDI File:\n${payload.midi_file}` : 'Procedural Algorithm',
                        style: { background: '#1e1b4b', border: '1px solid #6366f1', color: 'white', padding: '10px', borderRadius: '8px', cursor: 'pointer', position: 'relative' } 
                    }, 
                    type: 'customInput'
                },
                { 
                    id: '2', 
                    position: { x: 300, y: 150 }, 
                    type: 'cartridgeNode',
                    data: { 
                        label: `Cartridge: ${payload.patch_name}`,
                        paramObj: payload.parameters 
                    }
                },
                { 
                    id: '3', 
                    position: { x: 650, y: 150 }, 
                    data: { 
                        label: `Audio Engine:\n${payload.engine}`,
                        style: { background: '#14532d', border: '1px solid #22c55e', color: 'white', padding: '10px', borderRadius: '8px', cursor: 'pointer', position: 'relative' } 
                    }, 
                    type: 'customOutput'
                },
            ];
            setNodes(newNodes);
            setEdges([
                { id: 'e1-2', source: '1', target: '2', animated: true, style: { stroke: '#06b6d4' } },
                { id: 'e2-3', source: '2', target: '3', animated: true, style: { stroke: '#22c55e' } }
            ]);

            setMessages(prev => [...prev, {
                role: 'assistant',
                content: `Graph Constructed. Please review the parameters on the canvas and press Execute when ready.`
            }]);
            
            setIsProcessing(false);

        } catch (error) {
            setIsProcessing(false);
            setMessages(prev => [...prev, {
                role: 'assistant',
                content: `API Connection Error: ${error.message}`
            }]);
        }
    };

    const nodeTypes = React.useMemo(() => ({
      customInput: ({ id, data }) => {
          const { setNodes, setEdges } = useReactFlow();
          const onDelete = () => {
              setNodes(nds => nds.filter(n => n.id !== id));
              setEdges(eds => eds.filter(e => e.source !== id && e.target !== id));
          };
          return (
              <div style={data.style}>
                  <button onClick={onDelete} className="absolute -top-2 -right-2 bg-red-600 rounded-full w-5 h-5 flex items-center justify-center text-white text-[10px] font-bold border border-[#09090c] hover:bg-red-500 z-50">✕</button>
                  <Handle type="source" position={Position.Bottom} style={{ background: '#6366f1', width: '12px', height: '12px' }} />
                  <div style={{ whiteSpace: 'pre-wrap', textAlign: 'center', fontSize: '11px', fontFamily: 'monospace' }}>{data.label}</div>
              </div>
          );
      },
      customOutput: ({ id, data }) => {
          const { setNodes, setEdges } = useReactFlow();
          const onDelete = () => {
              setNodes(nds => nds.filter(n => n.id !== id));
              setEdges(eds => eds.filter(e => e.source !== id && e.target !== id));
          };
          return (
              <div style={data.style}>
                  <button onClick={onDelete} className="absolute -top-2 -right-2 bg-red-600 rounded-full w-5 h-5 flex items-center justify-center text-white text-[10px] font-bold border border-[#09090c] hover:bg-red-500 z-50">✕</button>
                  <Handle type="target" position={Position.Top} style={{ background: '#22c55e', width: '12px', height: '12px' }} />
                  <div style={{ whiteSpace: 'pre-wrap', textAlign: 'center', fontSize: '11px', fontFamily: 'monospace' }}>{data.label}</div>
              </div>
          );
      },
      cartridgeNode: ({ id, data }) => {
          const { setNodes, setEdges } = useReactFlow();
          const onDelete = () => {
              setNodes(nds => nds.filter(n => n.id !== id));
              setEdges(eds => eds.filter(e => e.source !== id && e.target !== id));
          };
          return (
              <div style={{ background: '#083344', border: '1px solid #06b6d4', color: 'white', padding: '15px', borderRadius: '8px', minWidth: '220px', position: 'relative' }}>
                  <button onClick={onDelete} className="absolute -top-2 -right-2 bg-red-600 rounded-full w-5 h-5 flex items-center justify-center text-white text-[10px] font-bold border border-[#09090c] hover:bg-red-500 z-50">✕</button>
                  <Handle type="target" position={Position.Top} style={{ background: '#06b6d4', width: '12px', height: '12px' }} />
                  <div style={{ fontWeight: 'bold', marginBottom: '10px', fontSize: '14px', borderBottom: '1px solid #06b6d4', paddingBottom: '5px' }}>
                      {data.label}
                  </div>
                  {data.paramObj && Object.keys(data.paramObj).map(key => (
                      <div key={key} style={{ marginBottom: '12px' }}>
                          <label style={{ display: 'flex', justifyContent: 'space-between', fontSize: '10px', color: '#67e8f9', fontFamily: 'monospace', marginBottom: '4px' }}>
                              <span>{key.replace('afo:', '')}</span>
                              <span>{data.paramObj[key].toFixed(2)}</span>
                          </label>
                          <input 
                              type="range" 
                              min="0" 
                              max="1" 
                              step="0.01" 
                              value={data.paramObj[key]}
                              onChange={(e) => handleSliderChange(key, e.target.value)}
                              className="w-full h-1 bg-cyan-900 rounded-lg appearance-none cursor-pointer"
                          />
                      </div>
                  ))}
                  <Handle type="source" position={Position.Bottom} style={{ background: '#22c55e', width: '12px', height: '12px' }} />
              </div>
          );
      },
      mixdownNode: ({ id, data }) => {
          const currentNodes = useNodes();
          const currentEdges = useEdges();
          const { setNodes, setEdges } = useReactFlow();
          const onDelete = () => {
              setNodes(nds => nds.filter(n => n.id !== id));
              setEdges(eds => eds.filter(e => e.source !== id && e.target !== id));
          };

          // Unconnected Inputs (e.g. Direct WAVs)
          const inputs = currentNodes.filter(n => n.type === 'input' || n.type === 'customInput');
          const cartridges = currentNodes.filter(n => n.type === 'cartridgeNode');
          
          let visualTracks = [];
          
          for (const input of inputs) {
              const filePath = input.data.label.split('\n')[1];
              const outEdge = currentEdges.find(e => e.source === input.id);
              if (!outEdge && filePath?.toLowerCase().endsWith('.wav')) {
                  visualTracks.push({
                      type: 'audio',
                      name: filePath,
                      color: ['#4c1d95', '#8b5cf6'], // Purple
                      border: '#c084fc'
                  });
              }
          }
          
          for (const cart of cartridges) {
              const patchName = cart.data.label.replace('Cartridge: ', ''); // fallback
              const pureName = patchName.split('\n')[0].replace('🔌 ', '').replace('Cartridge: ','').trim();
              visualTracks.push({
                  type: 'synth',
                  name: pureName,
                  color: ['#083344', '#06b6d4'], // Cyan
                  border: '#67e8f9'
              });
          }

          if (visualTracks.length === 0) {
              visualTracks.push({
                  type: 'dummy',
                  name: 'Connect Algorithms / Audio',
                  color: ['#1e1b4b', '#1e1b4b'],
                  border: '#4c1d95'
              });
          }

          return (
              <div style={{ background: '#0f172a', border: '1px solid #c084fc', color: 'white', padding: '12px', borderRadius: '12px', width: '380px', position: 'relative', boxShadow: '0 8px 32px rgba(192, 132, 252, 0.1)' }}>
                  <button onClick={onDelete} className="absolute -top-2 -right-2 bg-red-600 rounded-full w-5 h-5 flex items-center justify-center text-white text-[10px] font-bold border border-[#09090c] hover:bg-red-500 z-50">✕</button>
                  <Handle type="target" position={Position.Top} style={{ background: '#c084fc', width: '20px', height: '8px', borderRadius: '4px' }} />
                  
                  <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', borderBottom: '1px solid rgba(192, 132, 252, 0.3)', paddingBottom: '8px', marginBottom: '12px' }}>
                      <span style={{ fontWeight: 'bold', fontSize: '12px', letterSpacing: '2px', color: '#e9d5ff' }}>{data.label || 'MASTER MIXDOWN'}</span>
                      <span style={{ fontSize: '10px', color: '#c084fc', fontFamily: 'monospace', background: 'rgba(192, 132, 252, 0.1)', padding: '2px 6px', borderRadius: '4px' }}>LENGTH SYNCS TO GLOBAL</span>
                  </div>

                  {/* Timeline Ruler */}
                  <div style={{ display: 'flex', justifyContent: 'space-between', fontSize: '9px', color: '#a855f7', fontFamily: 'monospace', marginBottom: '8px', padding: '0 4px' }}>
                      <span>0s</span><span>25%</span><span>50%</span><span>75%</span><span>100%</span>
                  </div>

                  {/* Tracks Container */}
                  <div style={{ background: 'rgba(0,0,0,0.6)', borderRadius: '8px', padding: '10px', display: 'flex', flexDirection: 'column', gap: '10px', border: '1px inset rgba(255, 255, 255, 0.05)' }}>
                      
                      {visualTracks.map((t, idx) => (
                          <div key={idx} style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
                              <span style={{ fontSize: '9px', color: '#94a3b8', width: '50px', overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>T{idx+1}: {t.type}</span>
                              <div style={{ flex: 1, height: '24px', background: 'rgba(255,255,255,0.02)', borderRadius: '12px', position: 'relative', border: '1px dashed rgba(255,255,255,0.1)' }}>
                                    <div style={{ position: 'absolute', left: '0%', width: '100%', height: '100%', background: `linear-gradient(90deg, ${t.color[0]} 0%, ${t.color[1]} 100%)`, borderRadius: '12px', border: `1px solid ${t.border}`, cursor: 'ew-resize', display: 'flex', alignItems: 'center', padding: '0 10px', fontSize: '9px', fontWeight: 'bold', color: '#f3e8ff', boxShadow: '0 2px 10px rgba(0,0,0,0.3)' }}>
                                        <div style={{ position: 'absolute', left: '-2px', top: '50%', transform: 'translateY(-50%)', width: '4px', height: '12px', background: t.border, borderRadius: '4px' }}></div>
                                        <span style={{flex: 1, textAlign: 'center'}}>{t.name}</span>
                                        <div style={{ position: 'absolute', right: '-2px', top: '50%', transform: 'translateY(-50%)', width: '4px', height: '12px', background: t.border, borderRadius: '4px' }}></div>
                                    </div>
                              </div>
                          </div>
                      ))}

                  </div>

                  <Handle type="source" position={Position.Bottom} style={{ background: '#22c55e', width: '20px', height: '8px', borderRadius: '4px' }} />
              </div>
          );
      }
    }), [currentBlueprint]);

    const onDragStart = (event, nodeType, fileName) => {
        event.dataTransfer.setData('application/reactflow', nodeType);
        event.dataTransfer.setData('fileName', fileName);
        event.dataTransfer.effectAllowed = 'move';
    };

    const onDragOver = useCallback((event) => {
        event.preventDefault();
        event.dataTransfer.dropEffect = 'move';
    }, []);

    const onDrop = useCallback(
        (event) => {
            event.preventDefault();

            const type = event.dataTransfer.getData('application/reactflow');
            const dataVal = event.dataTransfer.getData('fileName');
            
            if (typeof type === 'undefined' || !type) return;

            // Naive coordinate mapping for MVP (compensating for 400px left bar + 64px header)
            const position = {
                x: event.clientX - 450, 
                y: event.clientY - 100,
            };
            
            let newNode = null;

            if (type === 'input') {
                newNode = {
                    id: `dnd_in_${Date.now()}`,
                    type: 'customInput',
                    position,
                    data: { 
                        label: dataVal.endsWith('.wav') ? `WAV Audio:\n${dataVal}` : `MIDI File:\n${dataVal}`,
                        style: { background: dataVal.endsWith('.wav') ? '#4c1d95' : '#1e1b4b', border: dataVal.endsWith('.wav') ? '1px solid #c084fc' : '1px solid #6366f1', color: 'white', padding: '10px', borderRadius: '8px', cursor: 'pointer', position: 'relative' }
                    }
                };
            } else if (type === 'cartridgeNode') {
                newNode = {
                    id: `dnd_cart_${Date.now()}`,
                    type: 'cartridgeNode',
                    position,
                    data: { 
                        label: `Cartridge: ${dataVal}`,
                        paramObj: { "afo:Loudness": 0.8, "afo:SpectralCentroid": 0.5, "afo:RoomSize": 0.2 } // Default params
                    }
                };
            } else if (type === 'output') {
                newNode = {
                    id: `dnd_out_${Date.now()}`,
                    type: 'customOutput',
                    position,
                    data: { 
                        label: `Audio Engine:\n${dataVal}`,
                        style: { background: '#14532d', border: '1px solid #22c55e', color: 'white', padding: '10px', borderRadius: '8px', cursor: 'pointer', position: 'relative' }
                    }
                };
            } else if (type === 'mixdownNode') {
                newNode = {
                    id: `dnd_mix_${Date.now()}`,
                    type: 'mixdownNode',
                    position,
                    data: { label: `DAW MIXDOWN: ${dataVal}` }
                };
            }

            if (newNode) setNodes((nds) => nds.concat(newNode));
            
            // If we have an active blueprint, update its data source
            if (currentBlueprint) {
                if (type === 'input') {
                    setCurrentBlueprint(prev => ({...prev, midi_file: dataVal}));
                    setMessages(prev => [...prev, {
                        role: 'assistant',
                        content: `System update: Re-routed input data source to ${dataVal}.`
                    }]);
                } else if (type === 'cartridgeNode') {
                    setCurrentBlueprint(prev => ({...prev, patch_name: dataVal}));
                    setMessages(prev => [...prev, {
                        role: 'assistant',
                        content: `System update: Re-routed algorithm to ${dataVal}.`
                    }]);
                } else if (type === 'output') {
                    setCurrentBlueprint(prev => ({...prev, engine: dataVal}));
                    setMessages(prev => [...prev, {
                        role: 'assistant',
                        content: `System update: Re-routed target audio engine to ${dataVal}.`
                    }]);
                } else if (type === 'mixdownNode') {
                    setMessages(prev => [...prev, {
                        role: 'assistant',
                        content: `System update: Connected Multitrack Mixdown Bus.`
                    }]);
                }
            } else {
                // If the user drops an item on a blank canvas, create a default blueprint wrapper
                    let bp = {
                    engine: "S1",
                    patch_name: "init_clean_keys",
                    duration: globalDuration,
                    midi_file: null,
                    parameters: {}
                };
                
                if (type === 'input') bp.midi_file = dataVal;
                if (type === 'cartridgeNode') bp.patch_name = dataVal;
                if (type === 'output') bp.engine = dataVal;
                
                setCurrentBlueprint(bp);
                setMessages(prev => [...prev, {
                    role: 'assistant',
                    content: `System update: Initialized direct pipeline for ${dataVal}. Ready to execute.`
                }]);
            }
        },
        [setNodes, currentBlueprint]
    );

    return (
        <div className="flex h-screen w-full bg-[#050508] text-slate-200 font-sans overflow-hidden">
            
            {/* LEFT PANE: Chat Interface (Semantic Audio Engineer) */}
            <div className="w-[400px] border-r border-white/5 bg-[#0a0a0e] flex flex-col relative z-20 shadow-xl">
                <div className="h-16 flex items-center px-6 border-b border-white/5 bg-[#0c0c11]">
                    <div className="flex items-center gap-3">
                        <div className="w-2 h-2 rounded-full bg-cyan-400 animate-pulse shadow-[0_0_10px_#22d3ee]"></div>
                        <h1 className="font-mono text-sm tracking-widest font-bold text-cyan-400">SEMANTIC AUDIO ENGINEER</h1>
                    </div>
                </div>

                <div className="flex-1 overflow-y-auto p-4 space-y-6 custom-scrollbar">
                    {messages.map((msg, idx) => (
                        <div key={idx} className={`flex gap-3 ${msg.role === 'user' ? 'justify-end' : 'justify-start'}`}>
                            {msg.role === 'assistant' && (
                                <div className="w-8 h-8 rounded bg-cyan-900/40 border border-cyan-500/30 flex items-center justify-center text-cyan-400 shrink-0">
                                    <Bot size={16} />
                                </div>
                            )}
                            <div className={`max-w-[85%] rounded-lg p-3 text-sm leading-relaxed ${
                                msg.role === 'user' 
                                    ? 'bg-purple-600/20 border border-purple-500/30 text-purple-100' 
                                    : 'bg-white/5 border border-white/10 text-slate-300'
                            }`} style={{ fontFamily: msg.role === 'assistant' ? '"JetBrains Mono", monospace' : 'inherit' }}>
                                {msg.content}
                                {msg.audioUrl && (
                                    <div className="mt-3">
                                        <audio controls src={msg.audioUrl} className="w-full h-8" />
                                    </div>
                                )}
                            </div>
                            {msg.role === 'user' && (
                                <div className="w-8 h-8 rounded bg-purple-900/40 border border-purple-500/30 flex items-center justify-center text-purple-400 shrink-0">
                                    <User size={16} />
                                </div>
                            )}
                        </div>
                    ))}
                    {isProcessing && (
                        <div className="flex gap-3 justify-start">
                            <div className="w-8 h-8 rounded bg-cyan-900/40 border border-cyan-500/30 flex items-center justify-center text-cyan-400 shrink-0">
                                <Bot size={16} />
                            </div>
                            <div className="max-w-[85%] rounded-lg p-3 text-xs bg-white/5 border border-white/10 text-slate-400 font-mono italic">
                                Interfacing with visual logic canvas...
                            </div>
                        </div>
                    )}
                    <div ref={messagesEndRef} />
                </div>

                <div className="p-4 bg-[#0a0a0e] border-t border-white/5">
                    <form onSubmit={handleSubmit} className="relative flex items-center">
                        <input 
                            type="text" 
                            value={inputValue}
                            onChange={(e) => setInputValue(e.target.value)}
                            placeholder="Direct graph construction..."
                            className="w-full bg-black/40 border border-white/10 rounded-lg py-3 pl-4 pr-12 text-sm text-white placeholder-slate-600 focus:outline-none focus:border-cyan-500/50 focus:ring-1 focus:ring-cyan-500/50 transition-all font-mono"
                        />
                        <button 
                            type="submit" 
                            disabled={!inputValue.trim()}
                            className="absolute right-2 p-2 rounded text-cyan-500/50 hover:text-cyan-400 hover:bg-cyan-900/20 disabled:opacity-50 transition-colors"
                        >
                            <Send size={18} />
                        </button>
                    </form>
                </div>
            </div>

            {/* RIGHT PANE: React Flow Canvas */}
            <div className="flex-1 bg-[#09090c] relative flex flex-col items-stretch overflow-hidden">
                <div className="h-16 flex items-center justify-between px-8 border-b border-white/5 z-10 bg-gradient-to-b from-[#09090c] to-transparent pointer-events-none absolute top-0 left-0 right-0">
                    <h2 className="font-mono text-xs text-white/40 tracking-widest flex items-center gap-2">
                        <Settings2 size={14} />
                        WILLICKR BLOCKS CANVAS
                    </h2>
                    <div className="flex items-center gap-2 font-mono text-xs text-slate-500 bg-[#09090c]/80 px-2 py-1 rounded pointer-events-auto">
                        <span>API: http://localhost:8000/render</span>
                        <span className="w-2 h-2 rounded-full bg-cyan-500/50 ml-2 animate-pulse"></span>
                        <span>IDLE</span>
                    </div>
                </div>

                {/* FLOATING ASSET LIBRARY */}
                <div className="absolute top-24 right-8 z-50 bg-[#0c0c11]/90 border border-cyan-500/20 rounded-xl shadow-2xl w-80 backdrop-blur-sm overflow-hidden flex flex-col pointer-events-auto">
                    <div className="p-3 border-b border-white/10 bg-black/20 font-mono text-[10px] text-cyan-400 font-bold tracking-widest flex items-center justify-between">
                        <span>ASSET LIBRARY</span>
                        <div className="flex items-center gap-2">
                            <span className="text-white/40">GLOBAL LENGTH:</span>
                            <select 
                                value={globalDuration} 
                                onChange={e => setGlobalDuration(parseFloat(e.target.value))}
                                className="bg-black border border-white/20 rounded px-1 text-cyan-300 focus:outline-none"
                            >
                                <option value="5.0">5.0s</option>
                                <option value="10.0">10.0s</option>
                                <option value="30.0">30.0s</option>
                                <option value="60.0">60.0s</option>
                            </select>
                        </div>
                    </div>
                    <div className="p-3 flex flex-col gap-4 max-h-[500px] overflow-y-auto custom-scrollbar">
                        
                        {/* INPUT BLOCK */}
                        <div className="flex flex-col gap-2">
                            <div className="text-[10px] text-indigo-400 font-mono tracking-widest border-b border-indigo-500/20 pb-1 flex justify-between">
                                <span>STEP 1. DATA SOURCES</span>
                                <span className="bg-indigo-500/20 px-1 rounded text-indigo-300">{assets.inputs?.length || 0}</span>
                            </div>
                            <input 
                                type="text"
                                placeholder="Search inputs..."
                                value={searchTerms.inputs}
                                onChange={e => setSearchTerms(prev => ({...prev, inputs: e.target.value}))}
                                className="w-full bg-black/50 border border-indigo-500/30 rounded py-1 px-2 text-xs text-indigo-200 focus:outline-none focus:border-cyan-500/50"
                            />
                            <div className="max-h-32 overflow-y-auto pr-1 flex flex-col gap-1 custom-scrollbar">
                                {(assets.inputs || []).filter(i => i.label.toLowerCase().includes(searchTerms.inputs.toLowerCase())).map(item => (
                                    <div 
                                        key={item.path}
                                        className="p-2 rounded bg-indigo-950/40 border border-indigo-500/40 cursor-grab hover:bg-indigo-900/60 transition-colors group"
                                        onDragStart={(event) => onDragStart(event, 'input', item.path)}
                                        draggable
                                    >
                                        <div className="font-mono text-[10px] text-indigo-300 truncate">{item.label}</div>
                                        <div className="text-[9px] text-slate-400 mt-0.5 truncate">{item.desc}</div>
                                    </div>
                                ))}
                            </div>
                        </div>

                        {/* ALGORITHM BLOCK */}
                        <div className="flex flex-col gap-2">
                            <div className="text-[10px] text-cyan-400 font-mono tracking-widest border-b border-cyan-500/20 pb-1 flex justify-between">
                                <span>STEP 2. ALGORITHMS</span>
                                <span className="bg-cyan-500/20 px-1 rounded text-cyan-300">{assets.algorithms?.length || 0}</span>
                            </div>
                            <input 
                                type="text"
                                placeholder="Search patches..."
                                value={searchTerms.algorithms}
                                onChange={e => setSearchTerms(prev => ({...prev, algorithms: e.target.value}))}
                                className="w-full bg-black/50 border border-cyan-500/30 rounded py-1 px-2 text-xs text-cyan-200 focus:outline-none focus:border-cyan-500/50"
                            />
                            <div className="max-h-48 overflow-y-auto pr-1 flex flex-col gap-1 custom-scrollbar">
                                {(assets.algorithms || []).filter(a => a.label.toLowerCase().includes(searchTerms.algorithms.toLowerCase())).map(item => (
                                    <div 
                                        key={item.path}
                                        className="p-2 rounded bg-cyan-950/40 border border-cyan-500/40 cursor-grab hover:bg-cyan-900/60 transition-colors group"
                                        onDragStart={(event) => onDragStart(event, 'cartridgeNode', item.path)}
                                        draggable
                                    >
                                        <div className="font-mono text-[10px] text-cyan-300 truncate">{item.label}</div>
                                        <div className="text-[9px] text-slate-400 mt-0.5 whitespace-normal leading-tight">{item.desc}</div>
                                    </div>
                                ))}
                            </div>
                        </div>

                        {/* MIXDOWN TIMELINE BLOCK */}
                        <div className="flex flex-col gap-2">
                            <div className="text-[10px] text-fuchsia-400 font-mono tracking-widest border-b border-fuchsia-500/20 pb-1 flex justify-between whitespace-nowrap">
                                <span>STEP 3. MASTER BUS</span>
                            </div>
                            <div 
                                className="p-2 rounded bg-fuchsia-950/40 border border-fuchsia-500/40 cursor-grab hover:bg-fuchsia-900/60 transition-colors group"
                                onDragStart={(event) => onDragStart(event, 'mixdownNode', '10.0s Timeline')}
                                draggable
                            >
                                <div className="font-mono text-[11px] text-fuchsia-300">🎛️ Multitrack Timeline</div>
                                <div className="text-[9px] text-slate-400 mt-1">DAW alignment & mixdown</div>
                            </div>
                        </div>

                        {/* OUTPUT BLOCK */}
                        <div className="flex flex-col gap-2">
                            <div className="text-[10px] text-green-400 font-mono tracking-widest border-b border-green-500/20 pb-1 flex justify-between">
                                STEP 4. ENGINES [OUTPUT]
                            </div>
                            <div className="max-h-24 overflow-y-auto pr-1 flex flex-col gap-1 custom-scrollbar mt-1">
                                {(assets.engines || []).map(item => (
                                    <div 
                                        key={item.path}
                                        className="p-2 rounded bg-green-950/40 border border-green-500/40 cursor-grab hover:bg-green-900/60 transition-colors group"
                                        onDragStart={(event) => onDragStart(event, 'output', item.path)}
                                        draggable
                                    >
                                        <div className="font-mono text-[10px] text-green-300 truncate">{item.label}</div>
                                        <div className="text-[9px] text-slate-400 mt-0.5 truncate">{item.desc}</div>
                                    </div>
                                ))}
                            </div>
                        </div>

                    </div>
                </div>
                
                {/* FLOATING EXECUTE BUTTON overlay */}
                {currentBlueprint && (
                    <div className="absolute bottom-8 right-8 z-50">
                        <button 
                            onClick={executeBlueprint}
                            disabled={isProcessing}
                            className="px-8 py-4 bg-cyan-600 hover:bg-cyan-500 text-white font-bold rounded-xl shadow-[0_0_20px_rgba(34,211,238,0.4)] transition-all flex items-center gap-2 disabled:opacity-50"
                        >
                            {isProcessing ? 'EXECUTING...' : 'EXECUTE PIPELINE NOW'}
                        </button>
                    </div>
                )}

                <div className="flex-1 relative w-full h-full">
                    <ReactFlow
                        nodes={nodes}
                        edges={edges}
                        nodeTypes={nodeTypes}
                        onNodesChange={onNodesChange}
                        onEdgesChange={onEdgesChange}
                        onNodesDelete={onNodesDelete}
                        onConnect={onConnect}
                        onDrop={onDrop}
                        onDragOver={onDragOver}
                        colorMode="dark"
                        fitView
                        className="bg-[#09090c]"
                    >
                        <Background color="#fff" style={{ opacity: 0.05 }} gap={16} />
                        <Controls className="bg-white/5 border-white/10 text-white fill-white" />
                    </ReactFlow>
                </div>
            </div>
        </div>
    );
}
