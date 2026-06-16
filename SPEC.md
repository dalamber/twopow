# The twopow Specification

- **Version:** 1.0.0
- **Status:** Normative
- **Date:** 2026-06-16

## 1. Terminology

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD",
"SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be
interpreted as described in [RFC 2119](https://www.rfc-editor.org/rfc/rfc2119)
and [RFC 8174](https://www.rfc-editor.org/rfc/rfc8174) when, and only when, they
appear in all capitals, as shown here.

In this document:

- **Exponent** refers to the non-negative integer operand `n`.
- **The Base** refers to the integer `2`. The Base is fixed.
- **A Conforming Implementation** is any implementation that satisfies every
  normative requirement in Section 3.

## 2. Scope

This specification defines the observable behavior of a single operation: the
exponentiation of the Base by an Exponent. It does not mandate any particular
internal representation, instruction selection, or micro-architectural strategy,
provided the normative requirements are met.

## 3. Normative Requirements

### 3.1 Domain

- **R1.** A Conforming Implementation **MUST** accept any Exponent `n` in the
  closed interval `[0, 63]`.
- **R2.** A Conforming Implementation **MUST NOT** accept an Exponent outside
  the interval defined in R1 as a successful computation.

### 3.2 Result

- **R3.** For any Exponent `n` satisfying R1, the implementation **MUST** return
  the value `2^n` exactly, as an unsigned 64-bit integer.
- **R4.** The returned value **MUST** be identical across all supported
  platforms, compilers, and optimization levels (determinism).

### 3.3 Overflow

- **R5.** For any Exponent `n > 63`, the implementation **MUST** raise a typed
  error (`twopow::overflow_error`) and **MUST NOT** return a value.
- **R6.** The raised error **SHOULD** expose the offending Exponent for
  diagnostic purposes.

### 3.4 The Base

- **R7.** The Base **SHALL** be `2`. A Conforming Implementation **MUST NOT**
  provide, imply, or default to any other Base.
- **R8.** Proposals to vary the Base **MUST** be processed through the project's
  RFC procedure and are, as of this version, **NOT RECOMMENDED**.

## 4. Conformance

An implementation is a Conforming Implementation if and only if it satisfies R1
through R7. R6 and R8 are advisory. Conformance is verified continuously by the
project's test suite, property-based tests, and fuzzing harness.

## 5. Versioning

This specification follows [Semantic Versioning](https://semver.org). Any change
that narrows the domain (R1), alters a returned value (R3), or relaxes the Base
constraint (R7) constitutes a breaking change and **MUST** increment the major
version.

## 6. References

- RFC 2119 — Key words for use in RFCs to Indicate Requirement Levels.
- RFC 8174 — Ambiguity of Uppercase vs Lowercase in RFC 2119 Key Words.
- `PROOF.md` — A Proof of Correctness for `two_pow`.
