# Pocket Compiler v0.23

Pocket Compiler is a Nintendo 3DS homebrew HTML/CSS/JavaScript playground and lightweight browser/compiler engine.

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
