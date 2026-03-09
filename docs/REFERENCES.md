# Willickr Knowledge Base & References

This file contains external references, techniques, and inspiration sources for the Willickr project.
The Antigravity Agent should refer to these resources when designing new generative algorithms or translation modes.

**License Note:** Before using code from these sources, verify the license compatibility with the project.

## 1. Sonification Engines
*   **TwoTone** ([github.com/sonifydata/twotone](https://github.com/sonifydata/twotone))
    *   *License*: **MPL-2.0**
    *   *Description*: A web-based tool for sonifying data.
    *   *Relevance*: Reference for mapping linear data sets (CSV/JSON) to musical parameters. Study their approach to "Audio Charts".

## 2. Mathematical Foundations
*   **Music: a Mathematical Offering** (Dave Benson)
    *   *URL*: [https://homepages.abdn.ac.uk/d.j.benson/pages/html/music.pdf](https://homepages.abdn.ac.uk/d.j.benson/pages/html/music.pdf)
    *   *License*: **Copyright (CUP)** - Free to read, Do NOT Redistribute.
    *   *Description*: Comprehensive analysis of waves, proper temperament, and Fourier theory in music.
*   **Musimathics** (Gareth Loy)
    *   *Repo*: [https://github.com/musimat/musimat](https://github.com/musimat/musimat)
    *   *License*: **GPL-3.0**
    *   *Context*: Contains C++ implementations of primitive digital signal processing and musical algorithms (Musimat). Reference for low-level algorithm implementations.

## 3. Community Projects & Implementations
*   **Image2Music**: [https://github.com/brihijoshi/Image2Music](https://github.com/brihijoshi/Image2Music)
    *   *License*: **Unknown** (No license file found).
    *   *Context*: Example of converting Images to Music using SuperCollider/FoxDot.
*   **earthquake-music**: [https://github.com/DevinCLane/earthquake-music](https://github.com/DevinCLane/earthquake-music)
    *   *License*: **Unknown** (No license file found).
    *   *Context*: Sonification of seismic data (one day = one minute).
*   **image-2-melody**: [https://github.com/dbetm/image-2-melody](https://github.com/dbetm/image-2-melody)
    *   *License*: **Unknown** (No license file found).
    *   *Context*: Translate visual data (images) into melodies with aesthetic decision making.
*   **data-audio-workstation**: [https://github.com/victorloux/data-audio-workstation](https://github.com/victorloux/data-audio-workstation)
    *   *License*: **WTFPL**
    *   *Context*: Web-based DAW specifically for data sonification.
*   **SoNSTAR**: [https://github.com/nuson/SoNSTAR](https://github.com/nuson/SoNSTAR)
    *   *License*: **Unknown** (No standard license file found).
    *   *Context*: "Sonification of Networks for SiTuational AwaReness". Real-time monitoring of TCP/IP traffic flags.
    *   *Data*: Uses `pcapy` for sniffing. `examples/logs` contains text-based flow logs (derived from PCAP), not raw PCAPs.
