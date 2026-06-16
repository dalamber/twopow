# twopow Bindings

`twopow` is available beyond C++. Each binding wraps the same `two_pow`
implementation; the base remains 2.

## C API

A C-linkage wrapper with explicit status codes (no exceptions cross the
boundary).

```c
#include <twopow/twopow_c.h>
#include <stdio.h>

int main(void) {
    uint64_t out = 0;
    if (twopow_two_pow(10, &out) == TWOPOW_OK) {
        printf("%llu\n", (unsigned long long)out);  /* 1024 */
    }
}
```

Build with `-DTWOPOW_BUILD_C_API=ON`. Links as `twopow::c`.

## Python

A [pybind11](https://github.com/pybind/pybind11) module named `pytwopow`.

```python
import pytwopow

pytwopow.two_pow(10)        # 1024
pytwopow.MAX_EXPONENT       # 63
pytwopow.two_pow(64)        # raises OverflowError
```

Build with `-DTWOPOW_BUILD_PYTHON=ON`.

## WebAssembly

An [Emscripten](https://emscripten.org) module (embind). Results are returned as
decimal strings to preserve full 64-bit precision in JavaScript.

```bash
cd bindings/wasm
./build.sh                  # requires emcc on PATH; emits dist/twopow.js + .wasm
python3 -m http.server      # then open index.html
```

```js
createTwopow().then((mod) => {
  mod.twoPow(10);           // "1024"
  mod.MAX_EXPONENT;         // 63
});
```

`bindings/wasm/index.html` is a self-contained interactive demo.
