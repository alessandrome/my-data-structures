#include <benchmark/benchmark.h>
#include "../../templated/Linear/Vector.h"

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

static void BM_VectorPrepend(benchmark::State& state) {
    const size_t initial_size = state.range(0);
    Vector<int> startingVec(initial_size + 2);
    for (size_t i = 0; i < initial_size; ++i) {
        startingVec.append(i); // Populate vec with n elements
    }
    for (auto _ : state) {state.PauseTiming();
        // Pause to reset vector in a starting condition
        state.PauseTiming();
        Vector<int> vec = startingVec;
        state.ResumeTiming();

        vec.prepend(std::rand());
        benchmark::DoNotOptimize(vec);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_VectorInsert(benchmark::State& state) {
    const size_t initial_size = state.range(0);
    Vector<int> startingVec(initial_size + 2);
    for (size_t i = 0; i < initial_size; ++i) {
        startingVec.append(i); // Populate vec with n elements
    }
    for (auto _ : state) {
        // Pause n Reset
        state.PauseTiming();
        Vector<int> vec = startingVec;
        state.ResumeTiming();

        vec.insert(42, 1);
        benchmark::DoNotOptimize(vec);
    }
    state.SetComplexityN(state.range(0));
}

// Registra il benchmark e specifica i range di input
BENCHMARK(BM_VectorAppend)
    ->RangeMultiplier(2)  // Aumenta il numero di input moltiplicandolo per 2
    ->Range(1 << 8, 1 << 20)  // From 256 (2^8) to 1.048.576 (2^20)
    ->Complexity();  // Stima la complessità (es. O(n))

BENCHMARK(BM_VectorPrepend)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 20)
    ->Complexity();

BENCHMARK(BM_VectorInsert)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 20)
    ->Complexity();

BENCHMARK_MAIN();
