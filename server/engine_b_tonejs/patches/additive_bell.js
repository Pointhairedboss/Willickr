window.patches['additive_bell'] = function(midi, Tone, renderDuration) {
    // Additive Bell implementation (loosely matching Pure Data structure)
    // MIDI note dictates fundamental freq. Velocity dictates amplitude.
    
    // Fallback if midi has no tracks
    if (midi.tracks.length === 0) return;
    
    // In our multitrack flow, there's usually a tempo track and a data track. Let's just merge all notes.
    const allNotes = [];
    midi.tracks.forEach(track => {
        track.notes.forEach(note => {
            // Memory optimization: drop notes that will not be rendered
            if (renderDuration && note.time > renderDuration) return;
            allNotes.push(note);
        });
    });

    allNotes.forEach(note => {
        const time = note.time;
        const dur = note.duration;
        const vel = note.velocity;
        
        const f0 = Tone.Frequency(note.name).toFrequency();
        
        // Define partial ratios for a strict additive bell
        const partials = [
            { ratio: 0.5, amp: 0.2 * vel, rel: dur * 4.0 }, // Sub/Hum
            { ratio: 1.0, amp: 0.5 * vel, rel: dur * 3.0 }, // Prime
            { ratio: 1.2, amp: 0.3 * vel, rel: dur * 2.0 }, // Tierce 
            { ratio: 1.5, amp: 0.2 * vel, rel: dur * 1.5 }, // Quint
            { ratio: 2.0, amp: 0.4 * vel, rel: dur * 1.0 }, // Nominal
            { ratio: 2.6, amp: 0.1 * vel, rel: dur * 0.8 },
            { ratio: 3.0, amp: 0.1 * vel, rel: dur * 0.5 },
            { ratio: 4.2, amp: 0.05 * vel,rel: dur * 0.2 }, // Strike transient
            { ratio: 5.5, amp: 0.05 * vel,rel: dur * 0.1 }
        ];
        
        partials.forEach(p => {
            const osc = new Tone.Oscillator(f0 * p.ratio, "sine").start(time);
            const env = new Tone.Envelope({
                attack: 0.005,
                decay: p.rel,
                sustain: 0,
                release: 0.1
            });
            const gain = new Tone.Gain(0).toDestination();
            
            // The max gain should be proportional to the amplitude
            const ampGain = new Tone.Gain(p.amp).connect(gain);
            
            osc.connect(ampGain);
            env.connect(gain.gain);
            
            env.triggerAttack(time);
            osc.stop(time + p.rel + 0.1);
        });
    });
};
