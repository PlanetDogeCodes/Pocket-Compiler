# PocketCompiler

**PocketCompiler** is an experimental Nintendo 3DS HTML/JS/CSS compiler and code editor.


---

## LLM Usage Disclaimer

In accordance with Universal-DB's LLM usage policy guidelines (https://db.universal-team.net/llm-policy), this project is classified as having **Minor LLM Usage** (meaningful portions of the code, documentation, release notes, etc. may have been generated with AI, but the overall project is still being largely human-managed). For more information on the usage of generative AI for this project, please navigate to the **Credits** section of the README.

---

## What It Does

PocketCompiler is designed to let you:

- Write HTML/JS/CSS on the 3DS, allowing for easy development
- Compile and run web pages directly on the top screen with a real DOM-based rendering engine
- Save/load/rename/delete projects from the SD card
- Debug with a live JS console

The default project path is:

```text
sdmc:/3ds/PocketCompiler/projects
```

---

### Controls

#### Edit Mode — Editor Tab

| Input | Action |
|---|---|
| D-Pad ↑↓ | Scroll code vertically |
| D-Pad ←→ | Scroll code horizontally |
| Circle Pad | Move cursor dot |
| Touch | Snap cursor to tap; tap tabs / code lines / file rows |
| A | Edit current line (3DS keyboard; auto-indent if empty) |
| B | Undo (5-step ring) |
| X | Save project (file explorer) |
| Y | Load project (file explorer) |
| L | Toggle JS Console tab |
| R | Open Actions menu (Find, Go-to, Duplicate, Comment, Rename, Delete, Sort, Export log, Recover autosave) |
| START | Compile + run |
| SELECT | Show controls menu (scrollable) |

#### Edit Mode — Console Tab

| Input | Action |
|---|---|
| D-Pad ↑↓ | Scroll console log |
| A | Type & eval JS expression |
| B | Clear console log |
| L | Back to editor tab |

#### Run Mode

| Input | Action |
|---|---|
| D-Pad | Scroll web page (all directions) |
| Circle Pad | Move cursor (never scrolls) |
| A / L | Left-click |
| B / R | Right-click |
| X | Release cursor lock |
| Y | Space key (sent to web content) |
| START | Stop, return to editor |

---

## Features

PocketCompiler includes:

- HTML parsing with DOM tree construction
- CSS engine with cascade, inheritance, specificity, custom properties (`var()`), `calc()`, `@media` skip, `:not()`, `:hover`/`:focus`/`:active`/`:checked`/`:disabled`, `:first-child`/`:last-child`/`:nth-child()`, comma selectors, `!important`, box-sizing, flex/grid layout, transitions, box-shadow, linear-gradient, word-wrap, and 40+ CSS properties
- JavaScript runtime via Duktape (ES5 + subset of ES6)
- DOM manipulation: `getElementById`, `querySelector`/`querySelectorAll`, `createElement`, `appendChild`, `innerHTML`, `textContent`, `classList`, live `style` object (Proxy-backed), `addEventListener`, `onclick`/`onload`/etc. property handlers
- Keyboard, mouse, and touch events with bubbling
- `document.write()` with incremental parsing
- Software keyboard integration for `<input>`/`<textarea>` text entry and `window.prompt()`
- Form submission via click on submit buttons
- `fetch()` / XMLHttpRequest (SD-card backed)
- localStorage / sessionStorage (SD-card persisted)
- IndexedDB (SD-card persisted, simplified sync API)
- Canvas 2D rendering
- WebGL scaffolding (Citro3D backend)
- Image loading (PNG via LodePNG)
- Web Audio (oscillators, gain, WAV playback via NDSP)
- Near-complete iframe support
- Auto-save draft (writes to SD on compile + 10s of idle)
- Crash-recovery: "Recover autosave" action restores unsaved work
- Remembers last-opened file across launches
- File explorer: save, load, rename, delete, sort by name/size/date


---

## Canvas / WebGL

PocketCompiler has rendering systems for:

- Canvas 2D: rectangles, paths, text, images, gradients, transforms, `fillText`/`strokeText`/`measureText`
- WebGL: `getContext("webgl")` detection, buffers, shaders/programs, uniforms/attributes, textures, draw calls, viewport/depth/blend/scissor state, Citro3D backend scaffolding

This is **not yet full WebGL**.

---

## Storage

PocketCompiler includes SD-card-backed storage systems:

```text
sdmc:/3ds/PocketCompiler/
    config.txt        ← last-opened file (auto-managed)
    autosave.html     ← crash-recovery draft (auto-managed)
    console_log.txt   ← exported JS console log (written on demand)
    projects/         ← all .html project files
    storage/
        local_*.json  ← localStorage data
        idb/          ← IndexedDB data
```

Supported:

- IndexedDB-style databases with `put`, `get`, `delete`, `clear`, `close`
- localStorage with SD-card persistence
- sessionStorage (in-memory, per session)
- Cookie-style storage

---

## Audio

PocketCompiler includes a Web Audio-style system:

- AudioContext-like runtime
- OscillatorNode (sine/square/triangle/sawtooth)
- GainNode
- AudioBufferSourceNode with WAV file loading
- NDSP-backed output when available
- Safe fallback if audio fails

---

## Important Limitations

PocketCompiler does **not** yet fully support:

- Full modern CSS (no CSS animations/@keyframes, no `rotate()`/`scale()` transforms, limited `position: fixed`)
- Full modern JavaScript (no ES modules, no `async`/`await`, no `Proxy` traps beyond `get`/`set`)
- Real networking (all `fetch`/XHR URLs resolve to SD-card files)
- Full WebGL 1.0 (no real GLSL shader translation)
- Full Canvas 2D API (no `drawImage` from video, no complex path fills)
- Full Web Audio API (no real-time effects, no offline rendering)
- Complete iframe isolation
- Pointer lock

The 3DS also has very limited RAM, CPU, GPU power, and screen space, so PocketCompiler uses strict safety limits (bounded DOM pool, bounded event queues, bounded command buffers, 4 MB max audio buffer, recursion depth guards).

---

## Credits

PocketCompiler project and idea by PlanetDogeCodes.
Some browser runtime features, custom Canvas/WebGL Integration, and 3DS Optimizations were all made with help from GPT-5.5 (xhigh) and GLM 5.2 (max).
Some UI elements and DOM-style event handling were made with help from Claude Sonnet 5 (high)


Built with:

- Visual Studio Code
- devkitPro
- devkitARM
- libctru
- Citro2D
- Citro3D
