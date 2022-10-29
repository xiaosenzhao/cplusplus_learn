#include <iostream>
#include <chrono>
#include <cstdlib>

void division() {
  for (int i = 0; i < 1000000; i++) {
    7654321 % 1024;
  }
}

void bitop() {
  for (int i = 0; i < 1000000; i++) {
    7654321 & 0x1FF;
  }
}

int main(void) {
  auto start = std::chrono::steady_clock::now();
  division();
  auto end = std::chrono::steady_clock::now();
  bitop();
  auto end_1 = std::chrono::steady_clock::now();

  std::chrono::duration<double> divison_cost = end - start;
  std::chrono::duration<double> bitop_cost = end_1 - end;

  std::cout << "elapsed time: " << std::endl;
  std::cout << "division: "<< divison_cost.count() << std::endl;
  std::cout << "bitop: " << bitop_cost.count() << std::endl;

  return 0;
}
