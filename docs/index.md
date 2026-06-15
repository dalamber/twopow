# twopow

Deterministic, high-performance base-2 exponentiation for modern C++.

`twopow::two_pow(n)` returns 2 raised to the power `n` as an unsigned 64-bit
integer, for `n` in the closed interval `[0, 63]`. Exponents beyond the
supported range raise `twopow::overflow_error`.

See the [API reference](annotated.html) for full details.
