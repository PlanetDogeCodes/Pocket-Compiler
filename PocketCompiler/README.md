# Pocket Compiler v0.24 Debug-Fixed Full Source

This version reconstructs the latest v0.23 project and applies non-feature-changing debug/stability fixes.

## Preserved features

* Code editor
* D-Pad arrow navigation
* Circle Pad mouse cursor
* visible cursor dot
* A = click / edit clicked code line
* B = undo
* X = save project
* Y = load project
* START = run/compile
* SELECT = controls menu
* Mini save/load file dialog
* Keyboard/mouse/touch DOM event queue
* Web Audio subset with NDSP-safe fallback
* Dark Citro2D UI
* SD project storage

## Debug fixes applied

* Added missing Citro2D/Citro3D includes where needed
* Fixed `CODE\_AREA\_\*` dependency by moving constants into `app.h`
* Fixed `BOT\_W/BOT\_H` visibility in controls module
* Added missing `stdio.h` in audio runtime
* Made audio init failure non-fatal
* Made save/load path creation safer
* Made line editing bounds safer
* Made undo snapshot behavior safer
* Kept feature behavior intact

## Build

```bash
make clean
make
```

Output:

```text
PocketCompiler.3dsx
```

