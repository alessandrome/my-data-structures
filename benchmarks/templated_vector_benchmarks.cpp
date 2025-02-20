#include <benchmark/benchmark.h>
#include "../templated/Linear/Vector.h"

using myds::Vector;


static void BM_VectorAppend(benchmark::State& state) {
    const size_t initial_size = state.range(0);
    Vector<int> startingVec(initial_size * 2);
    for (size_t i = 0; i < initial_size; ++i) {
        startingVec.append(i); // Populate vec with n elements
    }

    for (auto _ : state) {
        // Reset benchmark condition pausing counting time
        state.PauseTiming();;
        // Vector<int> vec(initial_size*3);
        auto vec = startingVec;
        state.ResumeTiming();

        // Execute append
        vec.append(55);
        benchmark::DoNotOptimize(vec); // Avoid optimization for vec
    }
    state.SetComplexityN(state.range(0));
}

// Registra il benchmark e specifica i range di input
BENCHMARK(BM_VectorAppend)
    ->RangeMultiplier(2)  // Aumenta il numero di input moltiplicandolo per 2
    ->Range(1 << 8, 1 << 20)  // From 256 (2^8) to 1.048.576 (2^20)
    ->Complexity();  // Stima la complessità (es. O(n))

BENCHMARK_MAIN();
