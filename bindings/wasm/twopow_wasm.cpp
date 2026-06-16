#include <emscripten/bind.h>

#include <cstdint>
#include <string>

#include "twopow/twopow.hpp"

namespace {

// JavaScript numbers are IEEE-754 doubles and cannot represent every value in
// [0, 2^63] exactly, so the result is returned as a decimal string to preserve
// full precision. Out-of-range exponents propagate as a JavaScript exception.
std::string two_pow_string(unsigned n) {
    return std::to_string(twopow::two_pow(n));
}

}  // namespace

EMSCRIPTEN_BINDINGS(twopow_module) {
    emscripten::function("twoPow", &two_pow_string);
    emscripten::constant("MAX_EXPONENT",
                         static_cast<unsigned>(twopow::kMaxExponent));
}
