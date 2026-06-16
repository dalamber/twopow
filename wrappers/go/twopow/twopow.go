// Package twopow provides deterministic base-2 exponentiation, backed by the
// twopow C++ core compiled in via cgo.
package twopow

/*
#cgo CPPFLAGS: -I${SRCDIR}/vendor
#cgo CXXFLAGS: -std=c++20
#cgo darwin LDFLAGS: -lc++
#cgo linux LDFLAGS: -lstdc++
#include <stdint.h>
#include "twopow/twopow_c.h"
*/
import "C"

import "fmt"

// MaxExponent is the largest supported exponent.
const MaxExponent = 63

// TwoPow returns 2**n for n in the closed interval [0, 63]. It returns an error
// when n exceeds MaxExponent.
func TwoPow(n uint) (uint64, error) {
	var out C.uint64_t
	if status := C.twopow_two_pow(C.uint(n), &out); status != C.TWOPOW_OK {
		return 0, fmt.Errorf("twopow: exponent %d exceeds maximum %d", n, MaxExponent)
	}
	return uint64(out), nil
}
