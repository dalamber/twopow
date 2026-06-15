# Changelog

All notable changes to this project are documented here. The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/) and this project
adheres to [Semantic Versioning](https://semver.org).

## [Unreleased]

## [0.1.0] - 2026-06-15

### Added
- `twopow::two_pow(unsigned)` returning `2^n` for `n` in `[0, 63]`.
- `twopow::overflow_error` for out-of-range exponents.
- `twopow-cli` command-line interface.
- Cross-platform CI matrix, benchmarks, packaging, and generated docs.
