#include "twopow/twopow.hpp"

#include <cstdint>

#include <gtest/gtest.h>

TEST(TwoPow, ZeroExponentIsOne) {
    EXPECT_EQ(twopow::two_pow(0), std::uint64_t{1});
}

TEST(TwoPow, DefaultExponentYieldsFour) {
    EXPECT_EQ(twopow::two_pow(twopow::kDefaultExponent), std::uint64_t{4});
}

TEST(TwoPow, MidRangeValue) {
    EXPECT_EQ(twopow::two_pow(10), std::uint64_t{1024});
}

TEST(TwoPow, UpperBoundaryValue) {
    EXPECT_EQ(twopow::two_pow(twopow::kMaxExponent),
              std::uint64_t{9223372036854775808ULL});
}

TEST(TwoPow, AboveBoundaryThrows) {
    EXPECT_THROW(twopow::two_pow(64), twopow::overflow_error);
}

TEST(TwoPow, OverflowErrorCarriesExponent) {
    try {
        twopow::two_pow(100);
        FAIL() << "expected twopow::overflow_error";
    } catch (const twopow::overflow_error& e) {
        EXPECT_EQ(e.exponent(), 100u);
    }
}
