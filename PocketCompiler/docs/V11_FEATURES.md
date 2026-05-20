# Pocket Compiler v0.11 Feature Additions

## Added

1. gzip/deflate decompression support
   - `include/content_decode.h`
   - `source/content_decode.c`
   - zlib linked with `-lz`

2. Lightweight JavaScript execution
   - `include/js_engine.h`
   - `source/js_engine.c`
   - supports `console.log`, `document.write`, and simple string variables

3. Image metadata decoding and placeholder rendering
   - `include/image_decoder.h`
   - `source/image_decoder.c`
   - supports PNG, JPEG, GIF, BMP metadata
   - renders `[image]` placeholders in the layout

## Preserved safety limits

- 1 MB per-resource cap
- 5 redirect cap interface
- binary-safe resource cache writes
