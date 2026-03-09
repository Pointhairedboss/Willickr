# Willickr Project Rules

**Reference for Agent & User**

These rules are the primary directives for the Willickr project. They prioritize stability, visibility, and risk management.

## 1. Foundations First
*   Establish toolsets, libraries, plugins, reference implementations, and architectural design **early** in the project.
*   Do not write "application code" until the "infrastructure code" (MCP structure, message passing) is defined.

## 2. Risk-First Development (SWEBOK)
*   De-risk the project by tackling the most uncertain elements first.
*   *Current Risks*: Real-time Python MIDI timing latency, WebSocket throughput for visualizations, seamless MCP tool execution handling.

## 3. Standalone Prototyping
*   Prototype when needed to validate a specific mechanism.
*   Prototypes must be **standalone** (located in `prototypes/`), not intermingled with production source.
*   Once validated, the pattern—not the prototype integration code—is ported to the main codebase.

## 4. Total Instrumentation
*   Instrument everything so you (The Agent) and the User can review system state in as close to real time as possible.
*   **Logs**: Structured logging (JSON) for all MCP tools.
*   **Visuals**: The Web UI should reflect internal state (buffers, current notes, errors).

## 5. Documentation of Instructions
*   This file (`PROJECT_RULES.md`) and `Prespec-Willickr.md` serve as the source of truth.
*   Always check these files before proposed major architectural changes.
