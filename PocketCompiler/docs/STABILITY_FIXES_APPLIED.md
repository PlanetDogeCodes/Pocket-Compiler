# Stability Fixes Applied in v0.10

This full project reconstructs v0.9 and applies the requested non-feature-changing fixes.

## Applied

- Added `#include <stdint.h>` in `source/net_fetch.c`
- Preserved CA bundle verification
- Preserved mbedTLS strict verification
- Preserved wolfSSL strict verification
- Added retry-safe mbedTLS read/write handling
- Added retry-safe wolfSSL read/write handling
- Preserved binary-safe resource caching
- Preserved 1 MB resource cap
- Preserved 5 redirect cap
- Preserved chunked transfer decoding
- Preserved HTTP/HTTPS fetching behavior
- Preserved Citro2D UI and browser-engine features

## Not changed

No features were intentionally added beyond stability corrections.
