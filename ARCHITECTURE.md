# Architecture

twopow is intentionally minimal.

## Components

- **`include/twopow/twopow.hpp`** — the public interface: `two_pow`, the
  `overflow_error` type, and two `constexpr` constants.
- **`src/twopow.cpp`** — the implementation: a domain check followed by a single
  left shift.
- **`app/main.cpp`** — `twopow-cli`, a thin command-line wrapper.

## Data flow

The caller supplies an exponent `n`. The library validates `n <= 63`, then
computes `1 << n` in 64-bit unsigned arithmetic and returns it. Out-of-domain
exponents short-circuit to a typed exception before any shift occurs.

## Design constraints

The return type is fixed at `std::uint64_t`, which bounds the valid exponent
domain at `[0, 63]`. This boundary is the central design contract and is covered
explicitly by the test suite.
