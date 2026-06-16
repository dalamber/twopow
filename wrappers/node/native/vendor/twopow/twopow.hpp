#ifndef TWOPOW_TWOPOW_HPP
#define TWOPOW_TWOPOW_HPP

#include <cstdint>
#include <stdexcept>
#include <string>

/// twopow — deterministic base-2 exponentiation for modern C++.
namespace twopow {

/// The largest exponent representable in the unsigned 64-bit return type.
inline constexpr unsigned kMaxExponent = 63;

/// Default exponent used when none is supplied (yields 2^2 = 4).
inline constexpr unsigned kDefaultExponent = 2;

/// Thrown when the requested exponent exceeds kMaxExponent.
class overflow_error : public std::overflow_error {
public:
    explicit overflow_error(unsigned exponent)
        : std::overflow_error("twopow: exponent " + std::to_string(exponent) +
                              " exceeds maximum supported value " +
                              std::to_string(kMaxExponent)),
          exponent_(exponent) {}

    /// The offending exponent that triggered the overflow.
    [[nodiscard]] unsigned exponent() const noexcept { return exponent_; }

private:
    unsigned exponent_;
};

/// Raises 2 to the given exponent.
///
/// @param n Exponent in the closed interval [0, kMaxExponent].
/// @return 2 raised to the power n, as an unsigned 64-bit integer.
/// @throws twopow::overflow_error when n > kMaxExponent.
[[nodiscard]] std::uint64_t two_pow(unsigned n);

}  // namespace twopow

#endif  // TWOPOW_TWOPOW_HPP
