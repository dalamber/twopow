#!/usr/bin/env bash
# Build the JNI native library and place it in the JAR resource tree for the
# current platform. Run before `mvn package`/`mvn test`.
set -euo pipefail

here="$(cd "$(dirname "$0")" && pwd)"
cmake -S "$here/native" -B "$here/native/build" -DCMAKE_BUILD_TYPE=Release
cmake --build "$here/native/build" --config Release

os="$(uname -s)"
arch="$(uname -m)"
case "$os" in
  Darwin) os_dir=darwin ;;
  Linux)  os_dir=linux ;;
  *)      os_dir=windows ;;
esac
case "$arch" in
  arm64|aarch64) arch_dir=aarch64 ;;
  x86_64|amd64)  arch_dir=amd64 ;;
  *)             arch_dir="$arch" ;;
esac

dest="$here/src/main/resources/native/${os_dir}-${arch_dir}"
mkdir -p "$dest"
lib="$(find "$here/native/build" \( -name 'libtwopow_jni.*' -o -name 'twopow_jni.dll' \) -type f | head -1)"
cp "$lib" "$dest/"
echo "native -> ${dest}/$(basename "$lib")"
