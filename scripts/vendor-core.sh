#!/usr/bin/env bash
# Sync the canonical core sources into every wrapper that compiles from source.
#
# The single source of truth is src/twopow.cpp + the public headers. Wrappers
# that build the core themselves (Swift, Java, Kotlin, Go, Node, Ruby) keep a
# vendored copy so each module is self-contained and independently publishable.
# Run this after changing the core or the C API; CI verifies it is in sync.
set -euo pipefail

root="$(cd "$(dirname "$0")/.." && pwd)"

CORE_CPP="$root/src/twopow.cpp"
CORE_HPP="$root/include/twopow/twopow.hpp"
CAPI_CPP="$root/bindings/c/twopow_c.cpp"
CAPI_H="$root/bindings/c/include/twopow/twopow_c.h"

# destination directories that receive the four core files. Each consumer
# compiles with -I<dir>, so the canonical "twopow/<header>" include layout is
# preserved. (Swift's SwiftPM module map needs a different layout and is
# vendored separately under wrappers/swift.)
DESTS=(
  "$root/wrappers/java/native/vendor"
  "$root/wrappers/kotlin/native/vendor"
  "$root/wrappers/node/native/vendor"
)

for dest in "${DESTS[@]}"; do
  mkdir -p "$dest/twopow"
  cp "$CORE_CPP" "$dest/twopow.cpp"
  cp "$CAPI_CPP" "$dest/twopow_c.cpp"
  cp "$CORE_HPP" "$dest/twopow/twopow.hpp"
  cp "$CAPI_H" "$dest/twopow/twopow_c.h"
  echo "vendored core -> ${dest#"$root"/}"
done

# Go and Ruby compile only sources in the package/ext directory itself, so the
# .cpp files live alongside the wrapper source and headers go in vendor/.
for pkg in "$root/wrappers/go/twopow" "$root/wrappers/ruby/ext/twopow"; do
  mkdir -p "$pkg/vendor/twopow"
  cp "$CORE_CPP" "$pkg/csrc_twopow.cpp"
  cp "$CAPI_CPP" "$pkg/csrc_twopow_c.cpp"
  cp "$CORE_HPP" "$pkg/vendor/twopow/twopow.hpp"
  cp "$CAPI_H" "$pkg/vendor/twopow/twopow_c.h"
  echo "vendored core -> ${pkg#"$root"/} (in-dir layout)"
done

echo "Done. Vendored core into $((${#DESTS[@]} + 2)) wrapper(s)."
