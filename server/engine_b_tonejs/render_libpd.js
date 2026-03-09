const puppeteer = require('puppeteer');
const fs = require('fs');
const http = require('http');
const path = require('path');

const mimeTypes = {
    '.html': 'text/html',
    '.js': 'text/javascript',
    '.wasm': 'application/wasm'
};

const args = process.argv.slice(2);
if (args.length < 4) {
    console.log("Usage: node render_libpd.js <mid> <patch> <dur> <out.wav>");
    process.exit(1);
}

const midiFilePath = args[0];
const patchName = args[1];
const durationSeconds = parseFloat(args[2]);
const outputWavPath = args[3];

// We need a local server to serve the WASM JS loaders to Puppeteer
const server = http.createServer((request, response) => {
    let urlObj;
    try {
        urlObj = new URL(request.url, `http://${request.headers.host}`);
    } catch(e) {
        urlObj = { pathname: request.url };
    }
    
    let filePath = '.' + urlObj.pathname;
    if (filePath == './') filePath = './libpd_renderer.html';
    
    // Serve from the wasm_library directory if looking for patch files
    if (urlObj.pathname.startsWith(`/${patchName}`)) {
        filePath = `./wasm_library/${urlObj.pathname.split('/').pop()}`;
    }

    const extname = String(path.extname(filePath)).toLowerCase();
    const contentType = mimeTypes[extname] || 'application/octet-stream';

    fs.readFile(filePath, function(error, content) {
        if (error) {
            console.log(`[Server 404] Missing file: ${filePath}`);
            response.writeHead(404);
            response.end('Error');
        } else {
            response.writeHead(200, { 'Content-Type': contentType });
            response.end(content, 'utf-8');
        }
    });
});

server.listen(8083);

async function renderWasm() {
    console.log(`[HVCC WASM Engine] Launching headless render for ${patchName}...`);
    
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
    
    page.on('console', msg => {
        const text = msg.text();
        if (text.startsWith("Error:") || msg.type() === "error") {
            console.error("[Browser Error]", text);
        } else {
            console.log("[Browser]", text);
        }
    });

    await page.goto(`http://localhost:8083/libpd_renderer.html?patch=${patchName}`);
    
    // Wait for the dynamic script injection to finish and load the heavy module
    await page.waitForFunction(`typeof window.${patchName}_Module !== "undefined"`, {timeout: 5000});
    
    console.log(`Evaluating WASM Offline Render for ${durationSeconds} seconds...`);
    
    // Actually render the generative audio
    const wavDataURI = await page.evaluate(async (patch, dur, midiData) => {
        return new Promise(async (resolve, reject) => {
            try {
                const sampleRate = 44100;
                const length = sampleRate * dur;
                const offlineCtx = new window.OfflineAudioContext(2, length, sampleRate);

                // Initialize the heavy module
                const heavyModule = await window[`${patch}_Module`]();
                const loader = new heavyModule.AudioLibLoader();
                
                await loader.init({
                    blockSize: 2048,
                    webAudioContext: offlineCtx
                });
                
                loader.start();
                
                // If the patch was purely generative, it starts generating now.
                // If it required MIDI, we could decode Tone.js MIDI here and use 
                // loader.sendMessage() to trigger PureData float receives!
                
                console.log("Processing C-Physics Offline...");
                const renderedBuffer = await offlineCtx.startRendering();
                console.log("C-Physics Array Generated. Encoding to WAV...");
                
                // Function to encode Float32 into WAV bytes
                function encodeWAV(audioBuffer) {
                    const numChannels = audioBuffer.numberOfChannels;
                    const sampleRate = audioBuffer.sampleRate;
                    const channelData = [];
                    for (let i = 0; i < numChannels; i++) channelData.push(audioBuffer.getChannelData(i));
                    
                    let interleaved;
                    if (numChannels === 2) {
                        interleaved = new Float32Array(channelData[0].length * 2);
                        let ix = 0;
                        for(let i=0; i<channelData[0].length; i++) {
                            interleaved[ix++] = channelData[0][i];
                            interleaved[ix++] = channelData[1][i];
                        }
                    } else {
                        interleaved = channelData[0];
                    }
                    
                    const buffer = new ArrayBuffer(44 + interleaved.length * 2);
                    const view = new DataView(buffer);
                    const writeString = (view, offset, string) => { for(let i=0; i<string.length; i++) view.setUint8(offset + i, string.charCodeAt(i)); };
                    
                    writeString(view, 0, 'RIFF');
                    view.setUint32(4, 36 + interleaved.length * 2, true);
                    writeString(view, 8, 'WAVE');
                    writeString(view, 12, 'fmt ');
                    view.setUint32(16, 16, true); view.setUint16(20, 1, true); view.setUint16(22, numChannels, true);
                    view.setUint32(24, sampleRate, true); view.setUint32(28, sampleRate * numChannels * 2, true);
                    view.setUint16(32, numChannels * 2, true); view.setUint16(34, 16, true);
                    writeString(view, 36, 'data'); view.setUint32(40, interleaved.length * 2, true);
                    
                    let offset = 44;
                    for (let i = 0; i < interleaved.length; i++) {
                        let s = Math.max(-1, Math.min(1, interleaved[i]));
                        view.setInt16(offset, s < 0 ? s * 0x8000 : s * 0x7FFF, true);
                        offset += 2;
                    }
                    return buffer;
                }

                const wavBuffer = encodeWAV(renderedBuffer);
                const bytesWav = new Uint8Array(wavBuffer);
                let binaryWav = '';
                for (let i = 0; i < bytesWav.byteLength; i++) {
                    binaryWav += String.fromCharCode(bytesWav[i]);
                }
                resolve(`data:audio/wav;base64,${window.btoa(binaryWav)}`);
            } catch (err) {
                reject(err.toString());
            }
        });
    }, patchName, durationSeconds, midiBase64);
    
    const base64Data = wavDataURI.replace(/^data:audio\/wav;base64,/, "");
    fs.writeFileSync(outputWavPath, base64Data, 'base64');
    
    await browser.close();
    server.close();
    console.log(`[HVCC WASM Engine] Render complete. Saved ${outputWavPath}`);
}

renderWasm().catch(err => {
    console.error("Puppeteer Render Crash:", err);
    server.close();
    process.exit(1);
});
