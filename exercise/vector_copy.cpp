#include <benchmark/benchmark.h>
#include <string>
#include <vector>

/*
2023-09-01T16:40:48+08:00
Running ./test
Run on (12 X 2600 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB
  L1 Instruction 32 KiB
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB
Load Average: 4.31, 3.09, 2.75
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
BM_func_for               1604 ns         1603 ns       431186
BM_func_operator          1192 ns         1192 ns       586206
BM_func_constructor       1150 ns         1149 ns       610607
BM_func_copy              3885 ns         3881 ns       180618
BM_func_assign            1298 ns         1298 ns       541993
BM_func_insert            1456 ns         1455 ns       489186
*/

#define BENCHMARKFUNC(func)                                                                            \
  static void BM_##func(benchmark::State& state) {                                                     \
    for (auto _ : state) {                                                                             \
      std::vector<std::string> strs = {"AAA", "BBB", "CCC", "DDD", "EEE", "FFF", "GGG", "HHH", "III"}; \
      func(strs);                                                                                      \
    }                                                                                                  \
  }                                                                                                    \
  BENCHMARK(BM_##func);

void func_for(const std::vector<std::string>& strs) {
  std::vector<std::string> tmp;
  tmp.reserve(strs.size());
  for (size_t i = 0; i < strs.size(); ++i) {
    tmp.emplace_back(strs[i]);
  }
}
BENCHMARKFUNC(func_for);

void func_operator(const std::vector<std::string>& strs) {
  std::vector<std::string> tmp;
  tmp = strs;
}
BENCHMARKFUNC(func_operator);

void func_constructor(const std::vector<std::string>& strs) { std::vector<std::string> tmp(strs); }
BENCHMARKFUNC(func_constructor);

void func_copy(const std::vector<std::string>& strs) {
  std::vector<std::string> tmp;
  std::copy(strs.begin(), strs.end(), std::back_inserter(tmp));
}
BENCHMARKFUNC(func_copy);

void func_assign(const std::vector<std::string>& strs) {
  std::vector<std::string> tmp;
  tmp.assign(strs.begin(), strs.end());
}
BENCHMARKFUNC(func_assign);

void func_insert(const std::vector<std::string>& strs) {
  std::vector<std::string> tmp;
  tmp.insert(tmp.begin(), strs.begin(), strs.end());
}
BENCHMARKFUNC(func_insert);

BENCHMARK_MAIN();
