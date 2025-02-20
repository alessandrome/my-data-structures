#include <vector>
#include <benchmark/benchmark.h>

static void BM_StdVectorAppend(benchmark::State& state) {
    const size_t initial_size = state.range(0);
    std::vector<int> startingVec(initial_size * 2);
    for (size_t i = 0; i < initial_size; ++i) {
        startingVec.push_back(i); // Populate vec with n elements
    }

    for (auto _ : state) {
        // Reset benchmark condition pausing counting time
        state.PauseTiming();;
        // Vector<int> vec(initial_size*3);
        std::vector<int> vec(initial_size + 2);
        for (size_t i = 0; i < initial_size; ++i) {
            vec.push_back(i); // Populate vec with n elements
        };
        state.ResumeTiming();

        // Execute append
        vec.push_back(55);
        benchmark::DoNotOptimize(vec); // Avoid optimization for vec
    }
    state.SetComplexityN(state.range(0));
}

static void BM_StdVectorPrepend(benchmark::State& state) {
    const size_t initial_size = state.range(0);
    std::vector<int> startingVec(initial_size + 2);
    for (size_t i = 0; i < initial_size; ++i) {
        startingVec.push_back(i); // Populate vec with n elements
    }
    for (auto _ : state) {state.PauseTiming();
        // Pause to reset vector in a starting condition
        state.PauseTiming();
        auto vec = startingVec;
        state.ResumeTiming();

        vec.insert(vec.begin(), std::rand());
        benchmark::DoNotOptimize(vec);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_StdVectorInsert(benchmark::State& state) {
    const size_t initial_size = state.range(0);
    std::vector<int> startingVec(initial_size + 2);
    for (size_t i = 0; i < initial_size; ++i) {
        startingVec.push_back(i); // Populate vec with n elements
    }
    for (auto _ : state) {
        // Pause n Reset
        state.PauseTiming();
        auto vec = startingVec;
        state.ResumeTiming();

        vec.insert(vec.begin() + 1, 42);
        benchmark::DoNotOptimize(vec);
    }
    state.SetComplexityN(state.range(0));
}

// Registra il benchmark e specifica i range di input
BENCHMARK(BM_StdVectorAppend)
    ->RangeMultiplier(2)  // Aumenta il numero di input moltiplicandolo per 2
    ->Range(1 << 8, 1 << 20)  // From 256 (2^8) to 1.048.576 (2^20)
    ->Complexity();  // Stima la complessità (es. O(n))

BENCHMARK(BM_StdVectorPrepend)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 20)
    ->Complexity();

BENCHMARK(BM_StdVectorInsert)
    ->RangeMultiplier(2)
    ->Range(1 << 8, 1 << 20)
    ->Complexity();

BENCHMARK_MAIN();
