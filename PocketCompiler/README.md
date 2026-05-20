# Pocket Compiler v0.23 Phase 11 Controls + DOM Events + Web Audio

Pocket Compiler is a Nintendo 3DS homebrew HTML/CSS/JavaScript playground and lightweight browser/compiler engine.

This phase adds:

- keyboard/mouse/touch DOM event dispatch
- no pointer lock approximation
- 3DS control mapping for the compiler/code area
- visible circle-pad mouse cursor dot
- A-button click/edit behavior for code lines
- B undo
- X save with mini file explorer/dialog
- Y load with mini file explorer/dialog
- START run/compile
- SELECT controls menu
- Web Audio subset

## 3DS controls

- D-Pad: arrow up/down/left/right in the code area
- Circle Pad: mouse cursor movement
- A: mouse click
  - if over code area, opens 3DS keyboard to edit clicked line
- B: undo
- X: save code/project
- Y: load code/project
- START: run/compile code
- SELECT: controls menu

## Project files

Projects are saved to:

```text
sdmc:/3ds/PocketCompiler/projects
```

## Web Audio subset

- AudioContext-like runtime
- OscillatorNode-like tone playback
- GainNode-like volume
- start/stop style helpers
- NDSP-backed tone output with safe failure behavior

## Build

```bash
make clean
make
```

Output:

```text
PocketCompiler.3dsx
```
