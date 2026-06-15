# Security Policy

## Supported Versions

| Version | Supported |
|---------|-----------|
| 0.1.x   | ✅        |

## Reporting a Vulnerability

If you discover a security issue in twopow's base-2 exponentiation — for
example, an exponent that produces an arithmetically incorrect power of two —
please open a private security advisory via GitHub's "Report a vulnerability"
workflow on this repository. We aim to acknowledge reports within 48 hours.

The supported domain is the closed interval `[0, 63]`. Exponents outside this
range raising `twopow::overflow_error` is intended behavior, not a vulnerability.
