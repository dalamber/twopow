# twopow for .NET

A C# binding for `twopow` via P/Invoke over the shared `libtwopow_ffi` library.
Published to GitHub Packages (NuGet) as `Dalamber.Twopow`.

## Install

```bash
dotnet add package Dalamber.Twopow --source https://nuget.pkg.github.com/dalamber/index.json
```

The native `twopow_ffi` library must be resolvable at runtime (bundled in the
package under `runtimes/<rid>/native/`).

## Use

```csharp
using Dalamber.Twopow;

ulong v = TwoPow.Compute(10);   // 1024
int max = TwoPow.MaxExponent;   // 63
TwoPow.Compute(64);             // throws OverflowException
```

## Build locally

```bash
# build the native FFI library first
cmake -S ../.. -B ../../build -DTWOPOW_BUILD_FFI=ON
cmake --build ../../build --target twopow_ffi
# make it discoverable, then:
dotnet test
```
