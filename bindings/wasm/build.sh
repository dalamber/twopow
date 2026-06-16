#!/usr/bin/env bash
# Build the twopow WebAssembly module. Requires the Emscripten SDK (emcc) on PATH.
#
#   ./build.sh            # emits dist/twopow.js + dist/twopow.wasm
#
set -euo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/../.." && pwd)"
out="$here/dist"
mkdir -p "$out"

emcc \
    "$here/twopow_wasm.cpp" \
    "$root/src/twopow.cpp" \
    -I"$root/include" \
    -std=c++20 \
    -O3 \
    -fexceptions \
    -lembind \
    -s MODULARIZE=1 \
    -s EXPORT_NAME=createTwopow \
    -s EXPORT_ES6=0 \
    -s DISABLE_EXCEPTION_CATCHING=0 \
    -o "$out/twopow.js"

echo "Built: $out/twopow.js and $out/twopow.wasm"
