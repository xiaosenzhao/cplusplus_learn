#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include <benchmark/benchmark.h>

void func1() {
  std::string a = "hello";
  std::string b = "world";
  std::string c = "";
  for (int i = 0; i < 10000; i++) {
    c = a + b;
  }
}

void func2() {
  std::string a = "hello";
  std::string b = "world";
  std::string c = "";
  for (int i = 0; i < 10000; i++) {
    c += a;
    c += b;
  }
}

void func3() {
  std::string a = "hello";
  std::string b = "world";
  std::string c = "";
  for (int i = 0; i < 10000; i++) {
    c.append(a);
    c.append(b);
  }
}

void func4() {
  std::stringstream ss;
  std::string a = "hello";
  std::string b = "world";
  for (int i = 0; i < 10000; i++) {
    ss << a;
    ss << b;
  }
}

static void BM_S1(benchmark::State& state) {
  for (auto _ : state) {
    func1();
  }
}
BENCHMARK(BM_S1);

static void BM_S2(benchmark::State& state) {
  for (auto _ : state) {
    func2();
  }
}
BENCHMARK(BM_S2);

static void BM_S3(benchmark::State& state) {
  for (auto _ : state) {
    func3();
  }
}
BENCHMARK(BM_S3);

static void BM_S4(benchmark::State& state) {
  for (auto _ : state) {
    func4();
  }
}
BENCHMARK(BM_S4);

BENCHMARK_MAIN();
