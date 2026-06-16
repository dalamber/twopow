# twopow Brand Guidelines

These guidelines govern the correct presentation of the twopow identity. They
exist to protect the integrity and recognizability of a library that performs a
single left shift. Adherence is **NOT RECOMMENDED** to be optional.

## Wordmark

The wordmark is always lowercase: **twopow**. Never "TwoPow", "TWOPOW",
"Two Pow", or "2pow". The wordmark is the brand; the brand is the wordmark.

## Logo

The canonical ASCII logo lives at [`docs/logo.txt`](docs/logo.txt) and is also
emitted by `twopow-cli --logo` (see the CLI). It MUST be reproduced verbatim,
including the tagline "base-2, forever".

## Color Palette

| Token        | Hex       | Usage                              |
|--------------|-----------|------------------------------------|
| Shift Green  | `#3fb950` | Primary. The successful path.      |
| Deep Canvas  | `#0d1117` | Backgrounds.                       |
| Signal Blue  | `#58a6ff` | Accents, cursors, the kernel.      |
| Overflow Red | `#f85149` | Errors and the `n > 63` boundary.  |
| Muted Slate  | `#8b949e` | Secondary text.                    |

## Clearspace & Minimum Size

- Maintain clearspace of at least one character cell around the ASCII logo.
- The logo MUST NOT be rendered below a legibility threshold at which the
  exponent `ⁿ` becomes indistinguishable from noise.

## Misuse

The following are prohibited:

- ❌ Rendering the wordmark in any base other than 2.
- ❌ Skewing, rotating, or applying perspective to the logo such that `1 << n`
  could be misread as `1 >> n`.
- ❌ Implying, through layout or proximity, support for base 3. (See
  `docs/adr/0002-rejecting-base-3.md`.)
- ❌ Recoloring Shift Green to any hue that connotes failure.
- ❌ Using the logo to endorse arithmetic the library does not perform.

## Tone of Voice

Serious. Precise. Unwavering. twopow speaks about base-2 exponentiation the way
other projects speak about distributed consensus. This is intentional.
