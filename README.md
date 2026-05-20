# Pocket Compiler

Self-contained Nintendo 3DS homebrew HTML editor + lightweight browser-engine foundation.

This version reconstructs the v0.9 TLS/CA-bundle project and applies non-feature-changing stability fixes directly.

## Included features

- dual-screen 3DS homebrew app
- Citro2D/Citro3D dark UI
- white panel outlines
- bottom-screen editor
- line-numbered, syntax-colored editor lines
- top-screen layout preview
- simple HTML parser
- inline CSS capture
- simple layout boxes
- external CSS/JS/image resource discovery
- SD cache directory
- 1 MB per-resource cap
- binary-safe cache writes
- HTTP socket fetching
- redirects
- chunked-transfer decoding
- HTTPS/TLS through mbedTLS or wolfSSL
- embedded Mozilla/certifi CA bundle
- certificate verification enabled
- stability fixes for TLS read/write retry behavior

## Build

```bash
make clean
make TLS_BACKEND=mbedtls
```

Alternative:

```bash
make clean
make TLS_BACKEND=wolfssl
```

No-TLS debug build:

```bash
make clean
make TLS_BACKEND=none
```

## Notes

- HTTPS certificate validation requires the 3DS date/time to be reasonably correct.
- gzip/deflate decompression is not implemented yet.
- JavaScript is cached but not executed yet.
- Images are cached but not decoded/rendered yet.


## Rebrand

This project has been renamed to **Pocket Compiler**. The build target remains `PocketCompiler` to avoid spaces in generated filenames.
