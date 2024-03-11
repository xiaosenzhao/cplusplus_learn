#include <benchmark/benchmark.h>

static void func1(benchmark::State& state) {
  for (auto _ : state) {
    int a = 100;
    int b = 0;
    if (a > 50) {
      b = 178989 * 9999 / 234;
    } else {
      b = 1000 * 100 / 55;
    }
    a = 49;
    if (a > 50) {
      b = 178989 * 9999 / 234;
    } else {
      b = 1000 * 100 / 55;
    }
  }
}
BENCHMARK(func1);

static void func2(benchmark::State& state) {
  for (auto _ : state) {
    int a = 100;
    int b = 0;
    b = a > 50 ? 178989 * 9999 / 234 : 1000 * 100 / 55;

    a = 49;
    b = a > 50 ? 178989 * 9999 / 234 : 1000 * 100 / 55;
  }
}
BENCHMARK(func2);

BENCHMARK_MAIN();