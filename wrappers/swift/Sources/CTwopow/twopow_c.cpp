#include "twopow/twopow_c.h"

#include <cstdint>

#include "twopow/twopow.hpp"

extern "C" twopow_status twopow_two_pow(unsigned n, std::uint64_t* out) {
    if (out == nullptr) {
        return TWOPOW_ERR_NULL;
    }
    try {
        *out = twopow::two_pow(n);
        return TWOPOW_OK;
    } catch (const twopow::overflow_error&) {
        return TWOPOW_ERR_OVERFLOW;
    }
}

extern "C" unsigned twopow_max_exponent(void) {
    return twopow::kMaxExponent;
}
