# Changelog

All notable changes to this project are documented here. The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and this project
adheres to [Semantic Versioning](https://semver.org).

## [Unreleased]

## [0.2.0] - 2026-06-16

### Added
- Seven publishable SDK wrappers under `wrappers/`: Java, Kotlin, Swift, C#,
  Go, Node.js, and Ruby — each with its own CI workflow and publish-on-tag step.
- In-tree bindings: C API, Python (pybind11), and WebAssembly (Emscripten).
- `twopow-service`: an HTTP "Exponentiation-as-a-Service" with OpenAPI + Swagger UI.
- `twopow-cli --logo`.
- Fuzzing (libFuzzer), sanitizer matrix (ASan/UBSan/TSan), and static analysis
  (cppcheck, scan-build).
- `PROOF.md` (formal proof of correctness), `SPEC.md` (RFC-2119 specification),
  `BRANDING.md`, and README translations (es, de, zh, ja).
- Benchmark baselines (`std::pow`, naive loop) and README charts.

## [0.1.0] - 2026-06-15

### Added
- `twopow::two_pow(unsigned)` returning `2^n` for `n` in `[0, 63]`.
- `twopow::overflow_error` for out-of-range exponents.
- `twopow-cli` command-line interface.
- Cross-platform CI matrix, benchmarks, packaging, and generated docs.
