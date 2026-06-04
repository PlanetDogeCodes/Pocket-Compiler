
# PocketCompiler

**PocketCompiler** is an experimental Nintendo 3DS HTML/JS/CSS compiler and code  editor


---

## LLM Usage Disclaimer

In accordance with Universal-DB's LLM usage policy guidelines (https://db.universal-team.net/llm-policy), this project is classified as having **Minor LLM Usage** (meaningful portions of the code, documentation, release notes, etc. may have been generated with AI, but the overall project is still being largely human-managed). For more information on the usage of generative AI for this project, please navigate to the **Credits** section of the README.

---

## What It Does

PocketCompiler is designed to let you:

- Write HTML/JS/CSS on the 3DS, allowing for easy development
- You can:
   - edit code on the bottom screen
   - preview output/status on the top screen
   - save/load projects from the SD card

The default project path is:

```text
sdmc:/3ds/PocketCompiler/projects
```

---

### Controls

| Input | Action |
|---|---|
| D-Pad | Arrow key movement |
| Circle Pad | Move mouse cursor (it's just a dot) |
| A | Click / edit code line |
| B | Undo |
| X | Save project |
| Y | Load project |
| START | Run / compile |
| SELECT | Show controls menu |

---

## Features

So far, PocketCompiler includes:

- basic HTML parsing
- simple CSS
- basic JavaScript runtime capabilities
- DOM-like elements
- keyboard/mouse/touch events
- nearly complete iframe support
- `document.write()`
- Limited API and link fetching
- IndexedDB-adjacent SD-card storage
- custom Canvas rendering
- custom WebGL rendering
- image loading
- web audio support


---

## Canvas / WebGL

PocketCompiler has rendering systems for:

- canvas command buffers
- rectangles, lines, text, placeholders
- `getContext("webgl")` detection
- buffers
- shaders/programs
- uniforms/attributes
- textures
- draw calls
- viewport/depth/blend/scissor state
- Citro3D backend scaffolding

This is **not yet full WebGL**.

---

## Storage

PocketCompiler includes SD-card-backed storage systems:

```text
sdmc:/3ds/PocketCompiler/idb/
sdmc:/3ds/PocketCompiler/cache_api/
sdmc:/3ds/PocketCompiler/resource_cache/
```

Supported or scaffolded:

- IndexedDB-style databases/object stores
- `put`, `get`, `delete`, `clear`, `count`
- localStorage-style storage
- sessionStorage-style storage
- Cache API-style storage
- binary-safe values
- 1 MB per-value/resource cap

---

## Audio

PocketCompiler includes a small Web Audio-style system:

- AudioContext-like runtime
- OscillatorNode-like node
- GainNode-like node
- sine/square/triangle/sawtooth tones
- NDSP-backed output when available
- safe fallback if audio fails

---

## Important Limitations

PocketCompiler is still in early development.

It does **not** yet fully support:

- complete HTML parsing
- full CSS layout/cascade
- full modern JavaScript/browser behavior
- complete Promise/event-loop behavior
- full WebGL 1.0
- real GLSL shader translation
- full Canvas 2D API
- full Web Audio API
- full IndexedDB compatibility
- complete iframe isolation
- pointer lock


The 3DS also has very limited RAM, CPU, GPU power, and screen space, so PocketCompiler uses strict safety limits (1 MB per resource/value/cache entry, bounded event queues, bounded command buffers, bounded editor/runtime structures)

---

## Credits

PocketCompiler project and idea by PlanetDogeCodes (me).
Some browser runtime features, custom Canvas/WebGL Integration, and 3DS Optimizations were all made with help from GPT-5.5 xhigh.
Some UI elements and DOM-style event handling were made with help from Claude Sonnet 4.6


Built with:

- Visual Studio Code
- devkitPro
- devkitARM
- libctru
- Citro2D
- Citro3D
