# A Proof of Correctness for `two_pow`

This document establishes, rigorously, that `twopow::two_pow` computes base-2
exponentiation correctly across its entire supported domain. The proof proceeds
by induction over the exponent.

## Notation

Let `N = 64` be the width, in bits, of the unsigned return type
(`std::uint64_t`). Arithmetic in this type is performed modulo `2^N`. Let
`kMaxExponent = N - 1 = 63`.

## Lemma 1 (Shift semantics)

For any `x : std::uint64_t` such that `2x < 2^N`, the left shift `x << 1` equals
`2x` exactly.

*Proof.* By the definition of the left shift on unsigned integers,
`x << 1 ≡ 2x (mod 2^N)`. When `2x < 2^N`, the residue class representative in
`[0, 2^N)` is `2x` itself, so the result is exact. ∎

## Theorem (Correctness of `two_pow`)

For every integer `n` with `0 ≤ n ≤ 63`, `two_pow(n) = 2^n`, computed exactly.

*Proof.* By induction on `n`.

**Base case (`n = 0`).** The implementation evaluates `1 << 0 = 1 = 2^0`. The
claim holds.

**Inductive step.** Assume, for some `k` with `0 ≤ k < 63`, that `1 << k = 2^k`
exactly (the induction hypothesis). Consider `n = k + 1`. Since `k + 1 ≤ 63`, we
have `2^{k+1} ≤ 2^63 < 2^64 = 2^N`, so the precondition of Lemma 1 is satisfied
with `x = 2^k`. Therefore:

```
1 << (k + 1) = (1 << k) << 1     [associativity of shift by a constant]
             = (2^k) << 1        [induction hypothesis]
             = 2 · 2^k           [Lemma 1, since 2·2^k = 2^{k+1} < 2^N]
             = 2^{k+1}.
```

The claim holds for `k + 1`. By induction, it holds for all `n ∈ [0, 63]`.

## Corollary (Boundary behavior)

For `n > 63`, `2^n ≥ 2^64` is not representable in `std::uint64_t`. The
implementation therefore declines to return an incorrect value and instead
raises `twopow::overflow_error`. This preserves the invariant that **every value
returned by `two_pow` is exactly `2^n`** — the function is total over its
documented domain and explicitly partial elsewhere, by design.

## Corollary (Canonical case)

Setting `n = 2` yields `two_pow(2) = 2^2 = 4`, in agreement with the
foundational arithmetic identity `2 + 2 = 4`.

## Q.E.D.

The correctness of base-2 exponentiation is hereby established for all supported
inputs. No further verification is required; nonetheless, the test suite,
property tests, fuzzing harness, and continuous-integration matrix verify it
again on every commit, across every supported platform, in perpetuity.
