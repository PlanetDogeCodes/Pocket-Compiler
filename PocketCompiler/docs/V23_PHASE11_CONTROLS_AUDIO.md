# Pocket Compiler v0.23 Phase 11 Controls + DOM Events + Web Audio

## Implemented

### DOM event dispatch

- keydown
- keyup
- mousemove
- mousedown
- mouseup
- click
- touchstart
- touchmove
- touchend

### 3DS controls mapping

- D-Pad: arrow up/down/left/right
- Circle Pad: mouse movement
- visible cursor dot on bottom screen
- A: mouse click
- A over code area: edit clicked line with 3DS keyboard
- B: undo
- X: save project
- Y: load project
- START: run/compile
- SELECT: controls menu

Pointer lock approximation was not added, but is a planned next feature.

### File explorer

- project directory
- save dialog
- load dialog
- file list overlay

### Web Audio subset

- AudioContext-like runtime
- OscillatorNode-like node
- GainNode-like node
- oscillator type/frequency
- gain value
- start/stop
- beep helper
- NDSP-backed safe runtime
