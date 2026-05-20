# Pocket Compiler

Pocket Compiler is a Nintendo 3DS homebrew HTML/CSS/JavaScript playground and lightweight browser/compiler engine.

Some advanced features include:

- gzip/deflate decompression support through zlib
- lightweight JavaScript execution
- image metadata decoding and image placeholder rendering
- existing dark Citro2D UI architecture
- editor/save/load scaffolding
- resource discovery/cache architecture
- 1 MB per-resource safety cap
- HTTPS/TLS build-mode hooks and embedded CA bundle

## Important JavaScript note

This build includes a small safe JavaScript execution layer suitable for 3DS memory limits. It supports:

```js
console.log("text");
document.write("text");
var msg = "text";
let msg = "text";
const msg = "text";
document.write(msg);
```

Full ECMAScript support still requires adding a full VM such as MuJS, Duktape, or QuickJS. 

## Image support

This build decodes image metadata for:

- PNG
- JPEG
- GIF
- BMP

It renders image placeholders in the layout/preview path and records detected image type/dimensions where possible. Full pixel decoding/rendering is prepared as the next renderer step.

## Build Instructions

```bash
make clean
make TLS_BACKEND=mbedtls
```

Alternative:

```bash
make TLS_BACKEND=wolfssl
```

No-TLS debug:

```bash
make TLS_BACKEND=none
```

## Output

```text
PocketCompiler.3dsx
```

Copy to:

```text
sdmc:/3ds/PocketCompiler/PocketCompiler.3dsx
```
