#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory_resource>
#include <string>
#include <vector>

int main() {
  auto start = std::chrono::steady_clock::now();
  std::array<std::byte, 2000000> buf;
  std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
  std::pmr::vector<std::pmr::string> coll{&pool};
  coll.reserve(5000);
  for (int i = 0; i < 5000; i++) {
    coll.emplace_back("jst a non-sso string");
  }
  auto end = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << std::endl;

  auto start1 = std::chrono::steady_clock::now();
  std::vector<std::string> coll1;
  for (int i = 0; i < 5000; i++) {
    coll1.emplace_back("jst a non-sso string");
  }
  auto end1 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count()
            << std::endl;

  auto start2 = std::chrono::steady_clock::now();
  std::vector<std::string> coll2;
  coll2.reserve(5000);
  for (int i = 0; i < 5000; i++) {
    coll2.emplace_back("jst a non-sso string");
  }
  auto end2 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()
            << std::endl;

  return 0;
}
