#include <chrono>
#include <iostream>
#include <thread>

struct S {
  long long a;
  long long b;
};

struct S2 {
  long long a;
  long long nonp[8];  // 占位，a、b 加载到不同的缓存行
  long long b;
};

int main() {
  S s1;
  auto start = std::chrono::steady_clock::now();
  std::thread t1([&]() {
    for (int i = 0; i < 100000000; i++) {
      s1.a++;
    }
  });
  std::thread t2([&]() {
    for (int i = 0; i < 100000000; i++) {
      s1.b++;
    }
  });
  t1.join();
  t2.join();
  auto end = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << std::endl;

  S2 s2;
  auto start2 = std::chrono::steady_clock::now();
  std::thread t3([&]() {
    for (int i = 0; i < 100000000; i++) {
      s2.a++;
    }
  });
  std::thread t4([&]() {
    for (int i = 0; i < 100000000; i++) {
      s2.b++;
    }
  });
  t3.join();
  t4.join();
  auto end2 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()
            << std::endl;

  return 0;
}
