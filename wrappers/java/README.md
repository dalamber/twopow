# twopow for Java

JNI binding for `twopow`. Published to GitHub Packages (Maven).

## Install

```xml
<dependency>
  <groupId>io.github.dalamber</groupId>
  <artifactId>twopow</artifactId>
  <version>0.2.0</version>
</dependency>
```

(Consume from the GitHub Packages Maven repository
`https://maven.pkg.github.com/dalamber/twopow`.)

## Use

```java
import io.github.dalamber.twopow.Twopow;

Twopow.twoPow(10);   // 1024
Twopow.MAX_EXPONENT; // 63
Twopow.twoPow(64);   // throws ArithmeticException
```

Java has no unsigned 64-bit type, so `twoPow(63)` returns `2^63` as the
two's-complement bit pattern (`Long.MIN_VALUE`); use
`Long.toUnsignedString(...)` to render values `>= 2^63`.

## Build locally

```bash
./build-native.sh   # builds libtwopow_jni for this platform into resources
mvn test
```
