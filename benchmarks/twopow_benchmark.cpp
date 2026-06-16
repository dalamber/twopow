#include <benchmark/benchmark.h>

#include <cmath>
#include <cstdint>

#include "twopow/twopow.hpp"

// The library: a bounds check and a single shift.
static void BM_TwoPow(benchmark::State& state) {
    const auto exponent = static_cast<unsigned>(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(twopow::two_pow(exponent));
    }
}
BENCHMARK(BM_TwoPow)->Arg(0)->Arg(2)->Arg(32)->Arg(63);

// Baseline: the floating-point standard-library route, cast back to integer.
static void BM_StdPow(benchmark::State& state) {
    const auto exponent = static_cast<int>(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(
            static_cast<std::uint64_t>(std::pow(2.0, exponent)));
    }
}
BENCHMARK(BM_StdPow)->Arg(0)->Arg(2)->Arg(32)->Arg(63);

// Baseline: a naive doubling loop, O(n) in the exponent.
static void BM_NaiveLoop(benchmark::State& state) {
    const auto exponent = static_cast<unsigned>(state.range(0));
    for (auto _ : state) {
        std::uint64_t result = 1;
        for (unsigned i = 0; i < exponent; ++i) {
            result <<= 1;
        }
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_NaiveLoop)->Arg(0)->Arg(2)->Arg(32)->Arg(63);

BENCHMARK_MAIN();
