#include <benchmark/benchmark.h>
#include <string>

// clang++ -Wall -std=c++17 string_optimize.cpp -I /usr/local/include -L /usr/local/lib -L /usr/lib -pthread -lbenchmark
// -o test
/*
Run on (12 X 2600 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB
  L1 Instruction 32 KiB
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB
Load Average: 3.92, 5.49, 5.57
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_remove_1                 35819 ns        35585 ns        19007
BM_remove_2                 35752 ns        35685 ns        19759
BM_remove_3                  4956 ns         4945 ns       141312
BM_remove_4                  4830 ns         4824 ns       145724
BM_remove_5                  5372 ns         5364 ns       127238
BM_remove_6                  1885 ns         1881 ns       373122
BM_remove_6_no_reserve       1907 ns         1904 ns       370953
BM_remove_7                  3568 ns         3562 ns       196025
BM_remove_inplace            3120 ns         3116 ns       223393
*/

// std::string s = "BBHFGDHGFDTREHBGFYRTAGFYGIWERWQAGFJNBVNRETWEAHGFFFUJHRWEAGHDFG";
#define BENCHMARKFUNC(func)                                                                                          \
  static void BM_##func(benchmark::State& state) {                                                                   \
    for (auto _ : state) {                                                                                           \
      std::string s =                                                                                                \
          "BBBBBBBBBBBBBBBBBBBBBHDSKLFJSDLKFJNLSDKAUFOWEIQNFGDSALJGF LKSDAJFLSDAKFJDSLAKFHJSDHFASLJFLSADJF OWEQIUE " \
          "RTW;ZFJHDS";                                                                                              \
      func(s);                                                                                                       \
    }                                                                                                                \
  }                                                                                                                  \
  BENCHMARK(BM_##func);

std::string remove_1(std::string s) {
  std::string result;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] != 'A') {
      result = result + s[i];
    }
  }
  return result;
}
BENCHMARKFUNC(remove_1);

// std::string::length() 返回值是 size_t
std::string remove_2(std::string s) {
  std::string result;
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] != 'A') {
      result = result + s[i];
    }
  }
  return result;
}
BENCHMARKFUNC(remove_2);

// 复合赋值操作替换拼接操作，避免临时字符串
std::string remove_3(std::string s) {
  std::string result;
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] != 'A') {
      result += s[i];
    }
  }
  return result;
}
BENCHMARKFUNC(remove_3);

// 预留存储空间减少内存重新分配
std::string remove_4(std::string s) {
  std::string result;
  result.reserve(s.length());
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] != 'A') {
      result += s[i];
    }
  }
  return result;
}
BENCHMARKFUNC(remove_4);

// 参数引用
std::string remove_5(const std::string& s) {
  std::string result;
  result.reserve(s.length());
  for (size_t i = 0; i < s.length(); ++i) {
    if (s[i] != 'A') {
      result += s[i];
    }
  }
  return result;
}
BENCHMARKFUNC(remove_5);

// 使用迭代器消除指针解引
// 初始化时调用end，缓存，避免后续重复计算
std::string remove_6(const std::string& s) {
  std::string result;
  result.reserve(s.length());
  for (auto it = s.begin(), end = s.end(); it != end; ++it) {
    if (*it != 'A') {
      result += *it;
    }
  }
  return result;
}
BENCHMARKFUNC(remove_6);
std::string remove_6_no_reserve(const std::string& s) {
  std::string result;
  result.reserve(s.length());
  for (auto it = s.begin(), end = s.end(); it != end; ++it) {
    if (*it != 'A') {
      result += *it;
    }
  }
  return result;
}
BENCHMARKFUNC(remove_6_no_reserve);

// 使用更好的算法
std::string remove_7(const std::string& s) {
  std::string result;
  result.reserve(s.length());
  for (size_t b = 0, i = b; b < s.length(); b = i + 1) {
    for (i = b; i < s.length(); ++i) {
      if (s[i] == 'A') {
        break;
      }
    }
    result.append(s, b, i - b);
  }
  return result;
}
BENCHMARKFUNC(remove_7);

// 删除修改
std::string remove_inplace(std::string s) {
  for (size_t i = 0; i < s.length();) {
    if (s[i] == 'A') {
      s.erase(i, 1);
    } else {
      ++i;
    }
  }
  return s;
}
BENCHMARKFUNC(remove_inplace);

BENCHMARK_MAIN();
