#include <benchmark/benchmark.h>
#include <vector>
#include <string>

/*
 * 2024-05-05T15:57:48+08:00
Running ./test
Run on (20 X 2808 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 256 KiB (x10)
  L3 Unified 20480 KiB (x1)
Load Average: 0.04, 0.05, 0.01
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
BM_func1          449 ns          449 ns      1574350
BM_func2          104 ns          104 ns      6686420
*/

void func1() {
  const std::vector<std::string> prefix_vec = {"/bin/admerger?", "/bin/lba?", "/bin/sp?",
    "/bin/admerger", "/bin/sp", "/bin/lba"};

  std::string s;
  for (const auto& word : prefix_vec) {
    s += word;
  }
}

static void BM_func1(benchmark::State& state) {
  for (auto _ : state) {
    func1();
  }
}
BENCHMARK(BM_func1);

void func2() {
  static const std::vector<std::string> prefix_vec = {"/bin/admerger?", "/bin/lba?", "/bin/sp?",
    "/bin/admerger", "/bin/sp", "/bin/lba"};

  std::string s;
  for (const auto& word : prefix_vec) {
    s += word;
  }
}

static void BM_func2(benchmark::State& state) {
  for (auto _ : state) {
    func2();
  }
}
BENCHMARK(BM_func2);

BENCHMARK_MAIN();



