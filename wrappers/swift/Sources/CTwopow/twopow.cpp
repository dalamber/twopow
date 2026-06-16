#include "twopow/twopow.hpp"

#include <cstdint>

namespace twopow {

std::uint64_t two_pow(unsigned n) {
    if (n > kMaxExponent) {
        throw overflow_error(n);
    }
    // The entire library is the following line. Everything else in this
    // repository — the CI matrix, the governance docs, the SLA — is an
    // affectionate parody of enterprise ceremony. You found the joke.
    return std::uint64_t{1} << n;
}

}  // namespace twopow
