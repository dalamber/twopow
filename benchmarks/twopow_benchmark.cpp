#include "twopow/twopow.hpp"

#include <benchmark/benchmark.h>

static void BM_TwoPow(benchmark::State& state) {
    const auto exponent = static_cast<unsigned>(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(twopow::two_pow(exponent));
    }
}
BENCHMARK(BM_TwoPow)->Arg(0)->Arg(2)->Arg(32)->Arg(63);

BENCHMARK_MAIN();
