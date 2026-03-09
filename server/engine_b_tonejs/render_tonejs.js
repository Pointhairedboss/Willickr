const puppeteer = require('puppeteer');
const fs = require('fs');
const path = require('path');

async function render(midiFilePath, patchName, durationSeconds, outputWavPath) {
    console.log(`[Tone.js Engine] Launching headless render for ${patchName}...`);
    
    // Read MIDI file as base64 to pass it to the browser memory without CORS issues
    let midiBase64 = '';
    try {
        const midiBuffer = fs.readFileSync(midiFilePath);
        midiBase64 = midiBuffer.toString('base64');
    } catch(err) {
        console.error("Could not read MIDI file:", err);
        process.exit(1);
    }

    const browser = await puppeteer.launch({ 
        headless: "new",
        args: ['--autoplay-policy=no-user-gesture-required', '--allow-file-access-from-files']
    });
    const page = await browser.newPage();
    
    // Redirect browser console logs to node terminal so we can debug Tone.js exceptions
    page.on('console', msg => {
        const text = msg.text();
        if (text.startsWith("Error:") || msg.type() === "error") {
            console.error("[Browser Error]", text);
        } else {
            console.log("[Browser]", text);
        }
    });

    const htmlPath = `file://${path.resolve(__dirname, 'renderer.html')}`;
    await page.goto(htmlPath);
    await page.waitForFunction('typeof Tone !== "undefined" && typeof window.Midi !== "undefined"');

    const wavDataURI = await page.evaluate(async (midiData, patch, duration) => {
        console.log("Decoding MIDI array...");
        let bytes;
        try {
            const binaryString = window.atob(midiData);
            const len = binaryString.length;
            bytes = new Uint8Array(len);
            for (let i = 0; i < len; i++) {
                bytes[i] = binaryString.charCodeAt(i);
            }
        } catch (e) {
            throw new Error("Failed to decode base64 MIDI: " + e.message);
        }
        
        let midi;
        try {
            midi = new window.Midi(bytes);
        } catch (e) {
            throw new Error("Failed to parse MIDI binary: " + e.message);
        }
        
        console.log(`Rendering ${duration} seconds of ${patch} offline...`);
        const buffer = await Tone.Offline(({ transport }) => {
            if (typeof window.patches[patch] !== 'function') {
                throw new Error(`Patch ${patch} not found! Check HTML includes.`);
            }
            window.patches[patch](midi, Tone, duration);
            transport.start();
        }, duration);

        console.log("Encoding AudioBuffer to WAV array...");
        function encodeWAV(audioBuffer) {
            const numChannels = audioBuffer.numberOfChannels;
            const sampleRate = audioBuffer.sampleRate;
            function writeString(view, offset, string) {
                for(let i=0; i<string.length; i++) {
                    view.setUint8(offset + i, string.charCodeAt(i));
                }
            }
            
            const channelData = [];
            for (let i = 0; i < numChannels; i++) {
                channelData.push(audioBuffer.getChannelData(i));
            }
            
            let interleaved;
            if (numChannels === 2) {
                const len = channelData[0].length;
                interleaved = new Float32Array(len * 2);
                let inputL = channelData[0];
                let inputR = channelData[1];
                let ix = 0;
                for(let i=0; i<len; i++) {
                    interleaved[ix++] = inputL[i];
                    interleaved[ix++] = inputR[i];
                }
            } else {
                interleaved = channelData[0];
            }
            
            const buffer = new ArrayBuffer(44 + interleaved.length * 2);
            const view = new DataView(buffer);
            writeString(view, 0, 'RIFF');
            view.setUint32(4, 36 + interleaved.length * 2, true);
            writeString(view, 8, 'WAVE');
            writeString(view, 12, 'fmt ');
            view.setUint32(16, 16, true);
            view.setUint16(20, 1, true);
            view.setUint16(22, numChannels, true);
            view.setUint32(24, sampleRate, true);
            view.setUint32(28, sampleRate * numChannels * 2, true);
            view.setUint16(32, numChannels * 2, true);
            view.setUint16(34, 16, true);
            writeString(view, 36, 'data');
            view.setUint32(40, interleaved.length * 2, true);
            
            let offset = 44;
            for (let i = 0; i < interleaved.length; i++) {
                let s = Math.max(-1, Math.min(1, interleaved[i]));
                view.setInt16(offset, s < 0 ? s * 0x8000 : s * 0x7FFF, true);
                offset += 2;
            }
            return buffer;
        }

        const wavBuffer = encodeWAV(buffer);
        const bytesWav = new Uint8Array(wavBuffer);
        let binaryWav = '';
        for (let i = 0; i < bytesWav.byteLength; i++) {
            binaryWav += String.fromCharCode(bytesWav[i]);
        }
        return `data:audio/wav;base64,${window.btoa(binaryWav)}`;
    }, midiBase64, patchName, parseFloat(durationSeconds));
    
    const base64Data = wavDataURI.replace(/^data:audio\/wav;base64,/, "");
    fs.writeFileSync(outputWavPath, base64Data, 'base64');
    
    await browser.close();
    console.log(`[Tone.js Engine] Render complete. Saved ${outputWavPath}`);
}

const args = process.argv.slice(2);
if (args.length < 4) {
    console.log("Usage: node render_tonejs.js <mid> <patch> <dur> <out.wav>");
    process.exit(1);
}
render(args[0], args[1], args[2], args[3]).catch(err => {
    console.error("Puppeteer Render Crash:", err);
    process.exit(1);
});
