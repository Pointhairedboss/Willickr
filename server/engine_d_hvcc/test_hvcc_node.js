const puppeteer = require('puppeteer');
const fs = require('fs');
const http = require('http');
const path = require('path');

const mimeTypes = {
    '.html': 'text/html',
    '.js': 'text/javascript',
    '.wasm': 'application/wasm'
};

const server = http.createServer((request, response) => {
    let filePath = '.' + request.url;
    if (filePath == './') filePath = './test_hvcc.html';
    
    const extname = String(path.extname(filePath)).toLowerCase();
    const contentType = mimeTypes[extname] || 'application/octet-stream';

    fs.readFile(filePath, function(error, content) {
        if (error) {
            console.log("Missing file:", filePath);
            response.writeHead(404);
            response.end('Error');
        } else {
            response.writeHead(200, { 'Content-Type': contentType });
            response.end(content, 'utf-8');
        }
    });
});

server.listen(8081);

async function testWasm(durationSeconds, outputWavPath) {
    console.log(`[HVCC WASM Engine] Launching headless render...`);
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

    await page.goto('http://localhost:8081/test_hvcc.html');
    await new Promise(r => setTimeout(r, 1000));
    
    console.log("Evaluating WASM Offline Render...");
    const b64 = await page.evaluate(async (dur) => {
        return await window.renderOffline(dur);
    }, parseFloat(durationSeconds));
    
    fs.writeFileSync(outputWavPath, b64, 'base64');
    
    await browser.close();
    server.close();
    console.log(`[HVCC WASM Engine] Render complete. Saved ${outputWavPath}`);
}

testWasm(5.0, "fire_hvcc_output.wav").catch(err => {
    console.error("Puppeteer Render Crash:", err);
    server.close();
    process.exit(1);
});
