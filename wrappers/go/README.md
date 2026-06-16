# twopow for Go

A cgo wrapper around the `twopow` C++ core (compiled from vendored source — no
prebuilt binary needed). Requires cgo (`CGO_ENABLED=1`) and a C++ toolchain.

## Install

```bash
go get github.com/dalamber/twopow/wrappers/go/twopow
```

Released as a nested module; versions are tagged `wrappers/go/vX.Y.Z`.

## Use

```go
import "github.com/dalamber/twopow/wrappers/go/twopow"

v, err := twopow.TwoPow(10) // 1024, nil
_, err = twopow.TwoPow(64)  // 0, error (overflow)
```

## Test locally

```bash
cd wrappers/go && go test ./...
```
