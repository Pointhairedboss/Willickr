# Multi-Track Audio Loopback Experiment

**Purpose:**
This directory contains experimental scripts aimed at building a lightweight Python Digital Audio Workstation (DAW). The goal is to bypass the Roland S-1's monotimbral (4-voice, 1-patch) limitation by synchronously recording USB audio out while sending MIDI data in. 

This allows us to "build a song" by tracking the bassline to a `.wav` file, saving the file, flipping the S-1 patch, and then recording the melody on top.

**Requirements:**
Running these scripts will require system-level audio capture capabilities. 
*   `pip install sounddevice`
*   `pip install soundfile`
*   `pip install numpy`

**Warning:**
Audio buffering and MIDI clock synchronization are complex on consumer operating systems. Expect latency, jitter, and debugging!
