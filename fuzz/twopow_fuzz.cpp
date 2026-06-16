// Fuzz harness for two_pow. Asserts the core invariant on every input:
//   - for n in [0, 63], two_pow(n) returns exactly 1 << n and never throws;
//   - for n > 63, two_pow(n) throws twopow::overflow_error.

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "twopow/twopow.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size < sizeof(unsigned)) {
        return 0;
    }

    unsigned n = 0;
    std::memcpy(&n, data, sizeof(n));

    bool threw = false;
    std::uint64_t result = 0;
    try {
        result = twopow::two_pow(n);
    } catch (const twopow::overflow_error&) {
        threw = true;
    }

    if (n <= twopow::kMaxExponent) {
        assert(!threw);
        assert(result == (std::uint64_t{1} << n));
    } else {
        assert(threw);
    }

    return 0;
}
