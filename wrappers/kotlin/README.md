# twopow for Kotlin

An idiomatic Kotlin JNI binding for `twopow`. Published to GitHub Packages
(Maven) as `io.github.dalamber:twopow-kotlin`.

## Install (Gradle)

```kotlin
repositories {
    maven("https://maven.pkg.github.com/dalamber/twopow")
}
dependencies {
    implementation("io.github.dalamber:twopow-kotlin:0.1.0")
}
```

## Use

```kotlin
import io.github.dalamber.twopow.Twopow

Twopow.twoPow(10)      // 1024
Twopow.MAX_EXPONENT    // 63
Twopow.twoPow(64)      // throws ArithmeticException
```

`twoPow(63)` returns `2^63` as `Long.MIN_VALUE` (no unsigned long on the JVM);
use `java.lang.Long.toUnsignedString(...)`.

## Build locally

```bash
./build-native.sh   # builds libtwopow_jni into resources
gradle test
```
