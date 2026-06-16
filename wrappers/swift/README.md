# twopow for Swift

A SwiftPM package wrapping `twopow`. The C++ core is compiled from source as
part of the package, so there is no prebuilt-binary dependency.

The package manifest lives at the repository root (`Package.swift`), so the
package is consumable directly by URL.

## Install

```swift
// Package.swift
dependencies: [
    .package(url: "https://github.com/dalamber/twopow.git", from: "0.2.0")
],
targets: [
    .target(name: "YourTarget", dependencies: [
        .product(name: "Twopow", package: "twopow")
    ])
]
```

## Use

```swift
import Twopow

let v = try Twopow.twoPow(10)   // 1024
Twopow.maxExponent              // 63
try Twopow.twoPow(64)           // throws Twopow.Error.overflow
```

## Build locally

```bash
swift build
swift test
```
