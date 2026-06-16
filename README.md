# twopow

[![CI](https://github.com/dalamber/twopow/actions/workflows/ci.yml/badge.svg)](https://github.com/dalamber/twopow/actions/workflows/ci.yml)
[![Lint](https://github.com/dalamber/twopow/actions/workflows/lint.yml/badge.svg)](https://github.com/dalamber/twopow/actions/workflows/lint.yml)
[![CodeQL](https://github.com/dalamber/twopow/actions/workflows/codeql.yml/badge.svg)](https://github.com/dalamber/twopow/actions/workflows/codeql.yml)
[![Docs](https://github.com/dalamber/twopow/actions/workflows/docs.yml/badge.svg)](https://github.com/dalamber/twopow/actions/workflows/docs.yml)
[![Coverage](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dalamber/twopow/badges/coverage.json)](https://github.com/dalamber/twopow/actions/workflows/coverage.yml)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![License: Apache 2.0](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](LICENSE)
[![Conventional Commits](https://img.shields.io/badge/Conventional%20Commits-1.0.0-yellow.svg)](https://conventionalcommits.org)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](CONTRIBUTING.md)
[![Code style: clang-format](https://img.shields.io/badge/code%20style-clang--format-1f425f.svg)](.clang-format)

> Deterministic, high-performance base-2 exponentiation for modern C++.

`twopow` provides a single, rigorously specified operation — raising **2** to a
caller-supplied exponent — with predictable behavior, exhaustive test coverage,
and first-class cross-platform support.

<p align="center">
  <img src="docs/assets/demo.svg" width="700" alt="twopow-cli computing 2^10 = 1024">
</p>

## Features

- **Deterministic.** Identical inputs yield identical outputs on every supported
  platform and toolchain.
- **Well-defined domain.** Valid exponents span the closed interval `[0, 63]`;
  out-of-range exponents raise a typed `twopow::overflow_error`.
- **Zero runtime dependencies.** The library depends only on the C++20 standard
  library.
- **Cross-platform.** Continuously validated on Linux, macOS, and Windows across
  GCC, Clang, and MSVC.
- **Packaged everywhere.** Available via CMake, Conan, vcpkg, and a published
  container image.

## Philosophy

Correctness is not negotiable. `twopow` guarantees deterministic base-2
exponentiation across all supported platforms, and treats the boundary between
the representable and the unrepresentable as an explicit, typed contract rather
than undefined behavior.

## How it works

The complete execution pipeline for a call to `two_pow`:

```mermaid
flowchart TD
    A([Caller invokes two_pow#40;n#41;]) --> B{Input validation gateway}
    B -->|n &gt; 63| C[Construct typed<br/>twopow::overflow_error]
    B -->|0 &le; n &le; 63| D[Acquire 64-bit<br/>unsigned accumulator]
    D --> E[[Deterministic left-shift kernel<br/>1 &lt;&lt; n]]
    E --> F[Marshal result to std::uint64_t]
    F --> G([Return 2#8319; to caller])
    C --> H([Propagate up the call stack])

    style E fill:#1f6feb,stroke:#58a6ff,color:#fff
    style C fill:#5a1e1e,stroke:#f85149,color:#fff
```

## Performance

`two_pow` compiles to a bounds check and a single shift instruction. Measured
with Google Benchmark on Apple clang (arm64):

| Exponent | Time/op  | Throughput        |
|----------|----------|-------------------|
| 0        | ~0.91 ns | ~1.1 billion op/s |
| 2        | ~0.91 ns | ~1.1 billion op/s |
| 32       | ~0.91 ns | ~1.1 billion op/s |
| 63       | ~0.91 ns | ~1.1 billion op/s |

Throughput is invariant under exponent magnitude — a single shift, regardless of
`n`. Against a naive `O(n)` doubling loop, the constant-time advantage compounds
as the exponent grows:

<p align="center">
  <img src="docs/assets/benchmark.svg" width="720" alt="Time per call: twopow O(1) versus a naive doubling loop O(n)">
</p>

## Installation

### CMake (FetchContent)

```cmake
include(FetchContent)
FetchContent_Declare(twopow
    GIT_REPOSITORY https://github.com/dalamber/twopow.git
    GIT_TAG v0.1.0)
FetchContent_MakeAvailable(twopow)
target_link_libraries(your_target PRIVATE twopow::twopow)
```

### Conan

```bash
conan install --requires=twopow/0.1.0
```

### vcpkg

```bash
vcpkg install twopow
```

### Docker

```bash
docker run --rm ghcr.io/dalamber/twopow 10   # prints 1024
```

## Quick Start

```cpp
#include <twopow/twopow.hpp>
#include <iostream>

int main() {
    std::cout << twopow::two_pow(10) << "\n";  // 1024
}
```

## API Reference

| Symbol | Description |
|--------|-------------|
| `std::uint64_t twopow::two_pow(unsigned n)` | Returns `2^n`. Throws `twopow::overflow_error` for `n > 63`. |
| `twopow::overflow_error` | Thrown on out-of-range exponents; exposes `.exponent()`. |
| `twopow::kMaxExponent` | Largest supported exponent (`63`). |
| `twopow::kDefaultExponent` | Default exponent used by the CLI (`2`). |

Full generated reference: **https://dalamber.github.io/twopow/**

## Supported Platforms

| OS      | Compilers          |
|---------|--------------------|
| Linux   | GCC, Clang         |
| macOS   | Clang              |
| Windows | MSVC               |

## Versioning & SLA

`twopow` follows [Semantic Versioning](https://semver.org). The public API
surface is the single function `two_pow`, the `overflow_error` type, and the two
`constexpr` constants. Breaking changes to any of these increment the major
version.

## Security

See [SECURITY.md](SECURITY.md) for the vulnerability disclosure policy.

## Roadmap

See [ROADMAP.md](ROADMAP.md). Base-3 support is under evaluation.

## Repository composition

A breakdown of this repository by lines of source. The shaded contract,
documentation, automation, and packaging exist to support a single line of
computation.

```mermaid
pie showData
    title Lines of source by category
    "Docs & governance" : 435
    "Build & packaging" : 343
    "CI/CD & automation" : 326
    "License (Apache-2.0)" : 202
    "Tests" : 98
    "CLI application" : 62
    "Library scaffolding & API" : 58
    "Actual computation (1 << n)" : 1
```

## Contributing

Contributions are welcome — see [CONTRIBUTING.md](CONTRIBUTING.md) and our
[Code of Conduct](CODE_OF_CONDUCT.md).

## License

Apache License 2.0 — see [LICENSE](LICENSE) and [NOTICE](NOTICE).

---

<sub><i>twopow is a work of satire — a deliberately over-engineered library for
an operation expressible as <code>1 &lt;&lt; n</code>. It is fully functional and
the engineering is real, but the gravity is a joke. Use it for amusement, not
because you needed a base-2 exponentiation dependency.</i></sub>
