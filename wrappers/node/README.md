# twopow for Node.js

A native N-API addon wrapping the `twopow` C++ core (compiled from vendored
source on install). Published to GitHub Packages (npm).

## Install

```bash
npm install @dalamber/twopow --registry=https://npm.pkg.github.com
```

Building the addon requires a C++ toolchain (node-gyp prerequisites).

## Use

```js
const twopow = require('@dalamber/twopow');

twopow.twoPow(10);      // 1024n  (BigInt — exact 64-bit)
twopow.MAX_EXPONENT;    // 63
twopow.twoPow(64);      // throws RangeError
```

Results are returned as `BigInt` to preserve exact 64-bit values.

## Test locally

```bash
cd wrappers/node && npm install && npm test
```
