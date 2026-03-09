import re

with open("web/src/App.jsx", "r", encoding="utf-8") as f:
    orig = f.read()

# Replace workflowStep with activePanel
code = orig.replace(
    "const [workflowStep, setWorkflowStep] = useState(1); // 1: Data, 2: Mixer, 3: Output",
    "const [activePanel, setActivePanel] = useState(null);"
)

# Replace Stepper UI with Panel Toggles
stepper_start = code.find('        {/* STEPPER UI */}')
stepper_end = code.find('        <div className="flex items-center gap-6">')
new_stepper = """        {/* PANEL TOGGLES */}
        <div className="flex-1 flex justify-center items-center gap-4 px-4 bg-black/20 py-2 rounded-lg border border-white/5 mx-4">
          {[
            { id: 'data', label: '1. DATA SOURCE' },
            { id: 'params', label: '2. PARAMETERS' },
            { id: 'routing', label: '3. ROUTING' },
            { id: 'activity', label: 'AGENT ACTIVITY' }
          ].map(btn => (
            <button
              key={btn.id}
              onClick={() => setActivePanel(activePanel === btn.id ? null : btn.id)}
              className={`px-6 py-2 rounded text-xs font-mono tracking-widest transition-all border ${activePanel === btn.id ? 'bg-cyan-500/20 border-cyan-400 text-cyan-300 shadow-[0_0_15px_rgba(34,211,238,0.4)]' : 'bg-transparent border-white/10 text-white/50 hover:bg-white/5 hover:text-white'}`}
            >
              {btn.label}
            </button>
          ))}
        </div>

"""
code = code[:stepper_start] + new_stepper + code[stepper_end:]

# Now we need to extract the raw component blocks safely.
# Look for <PipelineNode ...> down to the end of the DYNAMIC TIMELINE VISUALIZER div block.
pipe_start = code.find('<div style={{ position: \'relative\', zIndex: 1 }}>')
pipe_end = code.find('</div>\n            </div>\n\n          {/* Activity Log */}')
if pipe_end == -1: pipe_end = code.find('{/* Activity Log */}') - 40 # approx
data_block = code[pipe_start:pipe_end]
if "<PipelineNode " not in data_block: print("ERROR EXTRACTING DATA BLOCK")

log_start = code.find('<ActivityLog entries={activityLog} />')
log_end = log_start + len('<ActivityLog entries={activityLog} />')
# We just need the component call itself really, or the wrap.
log_block = '<ActivityLog entries={activityLog} />'

param_start = code.find('<EphemeralSlider')
# find end of the EphemeralSlider block (around the showSpawnedControl)
param_end = code.find('</div>\n          </div>\n\n          {/* XY Pad */}') 
if param_end == -1: param_end = code.find('{/* XY Pad */}') - 40
param_block = '<div className="space-y-6 max-w-sm mx-auto">' + code[param_start:param_end] + '</div>'

xy_start = code.find('<EphemeralXYPad')
xy_end = code.find('</div>\n\n          </div>\n\n          <div className="flex justify-between items-center bg-black/20')
xy_block = '<div className="max-w-md mx-auto">' + code[xy_start:xy_end] + "</div>"

out_start = code.find('{/* MIDI Output Controls */}')
out_end = code.find('</div>\n          </div>\n\n          <div className="flex justify-between items-center bg-black/20 p-4 rounded-lg')
out_block = '<div className="max-w-2xl mx-auto space-y-8">' + code[out_start:out_end] + "</div>"


# The Loom logic is standard, so we can hardcode the clean wrapper.
new_main_content = f"""
      {{/* Main View - Just The Loom */}}
      <div className="w-full relative flex flex-col items-center justify-center p-4" style={{ height: 'calc(100vh - 120px)' }}>
        <div className="w-full max-w-6xl h-full relative rounded-lg border border-white/10 shadow-2xl overflow-hidden bg-black/40 backdrop-blur-md">
          <TheLoom
            engineState={{engineState}}
            capabilities={{capabilities}}
            onUpdateTrack={{(track, param, value) => {{
              if (param === 'generator') {{
                const currentTrack = engineState.tracks[track];
                sendCommand({{
                  action: "assign_track",
                  track,
                  generator: value,
                  channel: currentTrack ? currentTrack.channel : 0
                }});
              }} else {{
                sendCommand({{ action: "update_track", track, param, value }});
              }}
            }}}}
            onOpenSoundModal={{(track) => setSoundModalTrack(track)}}
          />
          {{ghostHands.map(hand => (
            <GhostHand key={{hand.id}} x={{hand.x}} y={{hand.y}} label={{hand.label}} intensity={{0.8}} />
          ))}}
          {{[...Array(5)].map((_, i) => (
            <DataSpark key={{i}} startX={{scanProgress * 100}} startY={{50}} endX={{100}} endY={{20 + i * 15}} delay={{i * 400}} />
          ))}}
        </div>
      </div>

      {{/* MODAL RENDER SYSTEM */}}
      {{activePanel && (
         <div className="fixed inset-0 z-[60] flex items-center justify-center p-8 backdrop-blur-sm bg-black/80">
           <div className="bg-[#0f0f15] border border-white/10 rounded-xl w-full max-w-4xl max-h-[85vh] flex flex-col shadow-2xl overflow-hidden relative animate-in fade-in zoom-in-95 duration-200">
             
             <button onClick={{() => setActivePanel(null)}} className="absolute top-4 right-4 text-white/40 hover:text-white transition-colors z-[70] p-2 text-xl font-bold">✕</button>
             
             <div className="p-6 border-b border-white/10 bg-[#13131a]">
               <h2 className="text-xl font-bold tracking-tight text-white uppercase" style={{ fontFamily: '"Space Grotesk", sans-serif' }}>
                 {{activePanel === 'data' && '1. DATA SOURCE & ANALYSIS'}}
                 {{activePanel === 'params' && '2. GENERATIVE PARAMETERS & HARMONY'}}
                 {{activePanel === 'routing' && '3. TARGET ROUTING & OUTPUT'}}
                 {{activePanel === 'activity' && 'AGENT EVENT LOG'}}
               </h2>
             </div>
             
             <div className="flex-1 overflow-y-auto custom-scrollbar p-6 bg-[#0a0a0f]">
               
               {{activePanel === 'data' && (
                 <div className="w-full max-w-3xl mx-auto">
                    {data_block}
                 </div>
               )}}

               {{activePanel === 'params' && (
                 <div className="grid grid-cols-2 gap-12 w-full max-w-4xl mx-auto p-4">
                    <div className="bg-white/5 p-6 rounded-lg border border-white/10">
                        {param_block}
                    </div>
                    <div className="bg-white/5 p-6 rounded-lg border border-white/10 flex items-center justify-center">
                        {xy_block}
                    </div>
                 </div>
               )}}

               {{activePanel === 'routing' && (
                 <div className="bg-white/5 p-8 rounded-lg border border-white/10">
                    {out_block}
                 </div>
               )}}

               {{activePanel === 'activity' && (
                 <div className="w-full bg-[#13131a] p-4 rounded-lg border border-white/10 h-full max-h-[60vh] overflow-y-auto custom-scrollbar">
                    {log_block}
                 </div>
               )}}

             </div>
             
             <div className="p-4 bg-[#13131a] border-t border-white/10 flex justify-end">
               <button 
                  onClick={{() => setActivePanel(null)}}
                  className="px-8 py-2 bg-white/10 hover:bg-white/20 text-white text-xs font-mono rounded tracking-widest transition-all"
               >
                 CLOSE PANEL
               </button>
             </div>
           </div>
         </div>
      )}}
"""

grid_start = code.find('{/* Main Grid -> Wizard Flow */}')
grid_end = code.find('{/* Help Modal */}')

if grid_start == -1 or grid_end == -1:
    print("ERROR FINDING GRID BOUNDS")

final_code = code[:grid_start] + new_main_content + '\n      ' + code[grid_end:]

with open("web/src/App.jsx", "w", encoding="utf-8") as f:
    f.write(final_code)

print("App.jsx Modal Refactoring complete.")
