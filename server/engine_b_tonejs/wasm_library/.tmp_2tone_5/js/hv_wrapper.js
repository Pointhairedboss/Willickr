/**
 * Copyright (c) 2026 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

var audioWorkletSupported = (typeof AudioWorklet === 'function');

/*
 * AudioLibLoader - Convenience functions for setting up the web audio context
 * and initialising the AudioLib context
 */

var AudioLibLoader = function() {
  this.isPlaying = false;
  this.webAudioContext = null;
  this.webAudioProcessor = null;
  this.webAudioWorklet = null;
  this.audiolib = null;
}

/*
 * @param (Object) options
 *   @param options.blockSize (Number) number of samples to process in each iteration
 *   @param options.printHook (Function) callback that gets triggered on each print message
 *   @param options.sendHook (Function) callback that gets triggered for messages sent via @hv_param/@hv_event
 */
AudioLibLoader.prototype.init = function(options) {

  // use provided web audio context or create a new one
  this.webAudioContext = options.webAudioContext ||
      (new (window.AudioContext || window.webkitAudioContext || null));

  if (this.webAudioContext) {
    return (async() => {
      var blockSize = options.blockSize || 2048;
      if (audioWorkletSupported) {
        await this.webAudioContext.audioWorklet.addModule("2tone_5_AudioLibWorklet.js");
        this.webAudioWorklet = new AudioWorkletNode(this.webAudioContext, "2tone_5_AudioLibWorklet", {
          outputChannelCount: [2],
          processorOptions: {
            sampleRate: this.webAudioContext.sampleRate,
            blockSize,
          }
        });
        this.webAudioWorklet.port.onmessage = (event) => {
          if (event.data.type === 'printHook' && options.printHook) {
            options.printHook(event.data.payload);
          } else if (event.data.type === 'sendHook' && options.sendHook) {
            options.sendHook(event.data.payload[0], event.data.payload[1]);
          } else if (event.data.type === 'midiOut' && options.sendHook) {
            options.sendHook("midiOutMessage", event.data.payload);
          } else {
            console.log('Unhandled message from 2tone_5_AudioLibWorklet:', event.data);
          }
        };
        this.webAudioWorklet.connect(this.webAudioContext.destination);
      } else {
        console.warn('heavy: AudioWorklet not supported, reverting to ScriptProcessorNode');
        var instance = new 2tone_5_AudioLib({
            sampleRate: this.webAudioContext.sampleRate,
            blockSize: blockSize,
            printHook: options.printHook,
            sendHook: options.sendHook
        });
        this.audiolib = instance;
        this.webAudioProcessor = this.webAudioContext.createScriptProcessor(blockSize, instance.getNumInputChannels(), Math.max(instance.getNumOutputChannels(), 1));
        this.webAudioProcessor.onaudioprocess = (function(e) {
            instance.process(e)
        })
      }
    })();
  } else {
    console.error("heavy: failed to load - WebAudio API not available in this browser")
  }
}

AudioLibLoader.prototype.start = function() {
  if (this.audiolib) {
    this.webAudioProcessor.connect(this.webAudioContext.destination);
  } else {
    this.webAudioContext.resume();
  }
  this.isPlaying = true;
}

AudioLibLoader.prototype.stop = function() {
  if (this.audiolib) {
    this.webAudioProcessor.disconnect(this.webAudioContext.destination);
  } else {
    this.webAudioContext.suspend();
  }
  this.isPlaying = false;
}

AudioLibLoader.prototype.sendFloatParameterToWorklet = function(name, value) {
  if (this.audiolib) {
    this.audiolib.sendEvent(name, value);
  } else {
    this.webAudioWorklet.port.postMessage({
      type:'setFloatParameter',
      name,
      value
    });
  }
}

AudioLibLoader.prototype.sendEvent = function(name, value) {
  if (this.audiolib) {
    this.audiolib.sendEvent(name, value);
  } else {
    this.webAudioWorklet.port.postMessage({
      type:'sendEvent',
      name,
      value
    });
  }
}

AudioLibLoader.prototype.sendMidi = function(message) {
  if (this.audiolib) {
    this.audiolib.sendMidi(message);
  } else {
    this.webAudioWorklet.port.postMessage({
      type:'sendMidi',
      message:message
    });
  }
}

AudioLibLoader.prototype.fillTableWithFloatBuffer = function(name, buffer) {
  if (this.audiolib) {
    this.audiolib.fillTableWithFloatBuffer(name, buffer);
  } else {
    this.webAudioWorklet.port.postMessage({
      type:'fillTableWithFloatBuffer',
      name,
      buffer
    });
  }
}

Module.AudioLibLoader = AudioLibLoader;


/*
 * Heavy Javascript AudioLib - Wraps over the Heavy C API
 */

/*
 * @param (Object) options
 *   @param options.sampleRate (Number) audio sample rate
 *   @param options.blockSize (Number) number of samples to process in each iteration
 *   @param options.printHook (Function) callback that gets triggered on each print message
 *   @param options.sendHook (Function) callback that gets triggered for messages sent via @hv_param/@hv_event
 */
var 2tone_5_AudioLib = function(options) {
  this.sampleRate = options.sampleRate || 44100.0;
  this.blockSize = options.blockSize || 2048;

  // instantiate heavy context
  this.heavyContext = _hv_2tone_5_new_with_options(this.sampleRate, 10, 2, 2);
  this.setPrintHook(options.printHook);
  this.setSendHook(options.sendHook);

  // allocate temporary buffers (pointer size is 4 bytes in javascript)
  var lengthOutSamples = this.blockSize * this.getNumOutputChannels();
  var lengthInSamples = this.blockSize * this.getNumInputChannels();
  
  this.outputBuffer = new Float32Array(
      Module.HEAPF32.buffer,
      Module._malloc(lengthOutSamples * Float32Array.BYTES_PER_ELEMENT),
      lengthOutSamples);
  this.inputBuffer = new Float32Array(
    Module.HEAPF32.buffer,
    Module._malloc(lengthInSamples * Float32Array.BYTES_PER_ELEMENT),
    lengthInSamples);
}

var parameterInHashes = {
};

var parameterOutHashes = {
};

var eventInHashes = {
};

var eventOutHashes = {
};

var tableHashes = {
};

2tone_5_AudioLib.prototype.process = function(event) {
    // Currently only supports one output connection and one input connection on the worklet/scriptprocessor. (unlimited channels though)
    // Note(ZXMushroom63): calling getNumXXXChannels() every iteration of the for loop is slightly less efficient than calling once and storing the result
    var inputChannelCount = this.getNumInputChannels();
    if (inputChannelCount > 0) {
      for (let i = 0; i < inputChannelCount; i++) {
        if ((event.inputBuffer.numberOfChannels - 2) < i) {
          continue;
        }
        this.inputBuffer.set(event.inputBuffer.getChannelData(i), i * this.blockSize);
      }
    } else {
      this.inputBuffer.set(0); //clear buffer when no inputs are connected
    }
    
    _hv_processInline(this.heavyContext, this.inputBuffer.byteOffset, this.outputBuffer.byteOffset, this.blockSize);

    var outputChannelCount = this.getNumOutputChannels();
    for (var i = 0; i < outputChannelCount; ++i) {
      var output = event.outputBuffer.getChannelData(i);

      output.set(this.outputBuffer.subarray(i * this.blockSize, (i + 1) * this.blockSize));
    }
}

2tone_5_AudioLib.prototype.getNumInputChannels = function() {
  return (this.heavyContext) ? _hv_getNumInputChannels(this.heavyContext) : -1;
}

2tone_5_AudioLib.prototype.getNumOutputChannels = function() {
  return (this.heavyContext) ? _hv_getNumOutputChannels(this.heavyContext) : -1;
}

2tone_5_AudioLib.prototype.setPrintHook = function(hook) {
  if (!this.heavyContext) {
    console.error("heavy: Can't set Print Hook, no Heavy Context instantiated");
    return;
  }

  if (hook) {
    // typedef void (HvPrintHook_t) (HeavyContextInterface *context, const char *printName, const char *str, const HvMessage *msg);
    var printHook = addFunction(function(context, printName, str, msg) {
        // Converts Heavy print callback to a printable message
        var timeInSecs =_hv_samplesToMilliseconds(context, _hv_msg_getTimestamp(msg)) / 1000.0;
        var m = UTF8ToString(printName) + " [" + timeInSecs.toFixed(3) + "]: " + UTF8ToString(str);
        hook(m);
      },
      "viiii"
    );
    _hv_setPrintHook(this.heavyContext, printHook);
  }
}

2tone_5_AudioLib.prototype.setSendHook = function(hook) {
  if (!this.heavyContext) {
      console.error("heavy: Can't set Send Hook, no Heavy Context instantiated");
      return;
  }

  if (hook) {
    // typedef void (HvSendHook_t) (HeavyContextInterface *context, const char *sendName, hv_uint32_t sendHash, const HvMessage *msg);
    var sendHook = addFunction(function(context, sendName, sendHash, msg) {
        const midiMessage = sendMidiOut(UTF8ToString(sendName), msg);
        if (midiMessage.length > 0) {
            hook("midiOutMessage", midiMessage);
        } else {
            // Converts sendhook callback to (sendName, float) message
            hook(UTF8ToString(sendName), _hv_msg_getFloat(msg, 0));
        }
      },
      "viiii"
    );
    _hv_setSendHook(this.heavyContext, sendHook);
  }
}

2tone_5_AudioLib.prototype.sendEvent = function(name) {
  if (this.heavyContext) {
    _hv_sendBangToReceiver(this.heavyContext, eventInHashes[name]);
  }
}

2tone_5_AudioLib.prototype.sendMidi = function(message) {
  sendMidiIn(this.heavyContext, message);
}

2tone_5_AudioLib.prototype.setFloatParameter = function(name, floatValue) {
  if (this.heavyContext) {
    _hv_sendFloatToReceiver(this.heavyContext, parameterInHashes[name], parseFloat(floatValue));
  }
}

2tone_5_AudioLib.prototype.sendStringToReceiver = function(name, message) {
  // Note(joe): it's not a good idea to call this frequently it is possible for
  // the stack memory to run out over time.
  if (this.heavyContext) {
    var r = allocate(intArrayFromString(name), 'i8', ALLOC_STACK);
    var m = allocate(intArrayFromString(message), 'i8', ALLOC_STACK);
    _hv_sendSymbolToReceiver(this.heavyContext, _hv_stringToHash(r), m);
  }
}

2tone_5_AudioLib.prototype.fillTableWithFloatBuffer = function(name, buffer) {
  var tableHash = tableHashes[name];
  if (_hv_table_getBuffer(this.heavyContext, tableHash) !== 0) {

    // resize current table to new buffer length
    _hv_table_setLength(this.heavyContext, tableHash, buffer.length);

    // access internal float buffer from table
    tableBuffer = new Float32Array(
      Module.HEAPF32.buffer,
      _hv_table_getBuffer(this.heavyContext, tableHash),
      buffer.length);

    // set the table buffer with the data from the 1st channel (mono)
    tableBuffer.set(buffer);
  } else {
    console.error("heavy: Table '" + name + "' doesn't exist in the patch context.");
  }
}

Module.2tone_5_AudioLib = 2tone_5_AudioLib;



// midi_utils

function sendMidiIn(hv_context, message) {
  if (hv_context) {
      var command = message[0] & 0xF0;
      var channel = message[0] & 0x0F;
      var data1 = message[1];
      var data2 = message[2];

      // all events to [midiin]
      for (var i = 1; i <= 2; i++) {
        _hv_sendMessageToReceiverFF(hv_context, HV_HASH_MIDIIN, 0,
            message[i],
            channel
        );
      }

      // realtime events to [midirealtimein]
      if (MIDI_REALTIME.includes(message[0])) {
        _hv_sendMessageToReceiverFF(hv_context, HV_HASH_MIDIREALTIMEIN, 0,
          message[0]
        );
      }

      switch(command) {
        case 0x80: // note off
          _hv_sendMessageToReceiverFFF(hv_context, HV_HASH_NOTEIN, 0,
            data1,
            0,
            channel);
          break;
        case 0x90: // note on
          _hv_sendMessageToReceiverFFF(hv_context, HV_HASH_NOTEIN, 0,
            data1,
            data2,
            channel);
          break;
        case 0xA0: // polyphonic aftertouch
          _hv_sendMessageToReceiverFFF(hv_context, HV_HASH_POLYTOUCHIN, 0,
            data2, // pressure
            data1, // note
            channel);
          break;
        case 0xB0: // control change
          _hv_sendMessageToReceiverFFF(hv_context, HV_HASH_CTLIN, 0,
            data2, // value
            data1, // cc number
            channel);
          break;
        case 0xC0: // program change
          _hv_sendMessageToReceiverFF(hv_context, HV_HASH_PGMIN, 0,
            data1,
            channel);
          break;
        case 0xD0: // aftertouch
          _hv_sendMessageToReceiverFF(hv_context, HV_HASH_TOUCHIN, 0,
            data1,
            channel);
          break;
        case 0xE0: // pitch bend
          // combine 7bit lsb and msb into 32bit int
          var value = (data2 << 7) | data1;
          _hv_sendMessageToReceiverFF(hv_context, HV_HASH_BENDIN, 0,
            value,
            channel);
          break;
        default:
          // console.error('No handler for midi message: ', message);
      }
    }
  }

function sendMidiOut(sendName, msg) {
  switch (sendName) {
          case "__hv_noteout":
            var note = _hv_msg_getFloat(msg, 0);
            var velocity = _hv_msg_getFloat(msg, 1);
            var channel = _hv_msg_getFloat(msg, 2) % 16; // no pd midi ports
            return [
              ((velocity > 0) ? 144 : 128) | channel,
              note,
              velocity
            ]
          case "__hv_ctlout":
            var value = _hv_msg_getFloat(msg, 0);
            var cc = _hv_msg_getFloat(msg, 1);
            var channel = _hv_msg_getFloat(msg, 2) % 16; // no pd midi ports
            return [
              176 | channel,
              cc,
              value
            ]
          case "__hv_pgmout":
            var program = _hv_msg_getFloat(msg, 0);
            var channel = _hv_msg_getFloat(msg, 1) % 16; // no pd midi ports
            return [
              192 | channel,
              program
            ]
          case "__hv_touchout":
            var pressure = _hv_msg_getFloat(msg, 0);
            var channel = _hv_msg_getFloat(msg, 1) % 16; // no pd midi ports
            return [
              208 | channel,
              pressure,
            ]
          case "__hv_polytouchout":
            var value = _hv_msg_getFloat(msg, 0);
            var note = _hv_msg_getFloat(msg, 1);
            var channel = _hv_msg_getFloat(msg, 2) % 16; // no pd midi ports
            return[
              160 | channel,
              note,
              value
            ]
          case "__hv_bendout":
            var value = _hv_msg_getFloat(msg, 0);
            let lsb = value & 0x7F;
            let msb = (value >> 7) & 0x7F;
            var channel = _hv_msg_getFloat(msg, 1) % 16; // no pd midi ports
            return [
              224 | channel,
              lsb,
              msb
            ]
          case "__hv_midiout":
            let firstByte = _hv_msg_getFloat(msg, 0);
            return (firstByte === 192 || firstByte === 208) ?
              [_hv_msg_getFloat(msg, 0), _hv_msg_getFloat(msg, 1)] :
              [_hv_msg_getFloat(msg, 0), _hv_msg_getFloat(msg, 1), _hv_msg_getFloat(msg, 2)];
          default:
              console.warn(`Unhandled sendName: ${sendName}`);
              return [];
  }
}

/*
* MIDI Constants
*/

const HV_HASH_NOTEIN          = 0x67E37CA3;
const HV_HASH_CTLIN           = 0x41BE0f9C;
const HV_HASH_POLYTOUCHIN     = 0xBC530F59;
const HV_HASH_PGMIN           = 0x2E1EA03D;
const HV_HASH_TOUCHIN         = 0x553925BD;
const HV_HASH_BENDIN          = 0x3083F0F7;
const HV_HASH_MIDIIN          = 0x149631bE;
const HV_HASH_MIDIREALTIMEIN  = 0x6FFF0BCF;

const MIDI_REALTIME =  [0xF8, 0xFA, 0xFB, 0xFC, 0xFE, 0xFF];