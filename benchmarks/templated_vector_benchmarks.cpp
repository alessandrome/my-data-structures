#include <benchmark/benchmark.h>
#include "../templated/Linear/Vector.h"

using myds::Vector;


static void BM_VectorAppend(benchmark::State& state) {
    Vector<int> vec;  // Inizializza un oggetto della classe Vector

    for (auto _ : state) {
        // Reset del benchmark per evitare side effects tra iterazioni
        vec = Vector<int>();

        // Esegui il benchmark con il numero di input specificato in state.range(0)
        for (int i = 0; i < state.range(0); ++i) {
            vec.append(i);  // Append dei valori al vettore
        }
    }

    // Facoltativo: registra la dimensione finale del vettore come una controparte
    state.SetComplexityN(state.range(0));
}

// Registra il benchmark e specifica i range di input
BENCHMARK(BM_VectorAppend)
    ->RangeMultiplier(2)  // Aumenta il numero di input moltiplicandolo per 2
    ->Range(1 << 10, 1 << 20)  // Da 1024 (2^10) a 1.048.576 (2^20)
    ->Complexity();  // Stima la complessità (es. O(n))

BENCHMARK_MAIN();
