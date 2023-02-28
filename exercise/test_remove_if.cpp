#include <algorithm>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>

// std::remove_if 不适用关联容器
int main() {
  std::vector<int> vec1;
  std::vector<int> vec2;
  std::vector<int> vec3;

  vec1.reserve(65536);
  vec2.reserve(65536);
  vec3.reserve(65536);
  for (int i = 0; i < 65536; i++) {
    vec1.push_back(i);
    vec2.push_back(i);
    vec3.push_back(i);
  }

  auto cond = [](int x) { return (x & 1 == 1); };

  auto start1 = std::chrono::steady_clock::now();
  for (auto iter = vec1.begin(); iter != vec1.end();) {
    if (cond(*iter)) {
      vec1.erase(iter);
    } else {
      ++iter;
    }
  }
  auto end1 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count()
            << std::endl;

  auto start2 = std::chrono::steady_clock::now();
  for (auto iter = vec2.end(); iter != vec2.begin();) {
    --iter;
    if (cond(*iter)) {
      vec2.erase(iter);
    }
  }
  auto end2 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()
            << std::endl;

  auto start3 = std::chrono::steady_clock::now();
  vec3.erase(std::remove_if(vec3.begin(), vec3.end(), cond), vec3.end());
  auto end3 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count()
            << std::endl;

  /*
   * std::remove_if c++20 开始支持
   * 性能上没有优势
  std::unordered_map<std::string, int> map1;
  std::unordered_map<std::string, int> map2;
  std::unordered_map<std::string, int> map3;
  vec1.reserve(65536 * 2);
  vec2.reserve(65536 * 2);
  vec3.reserve(65536 * 2);
  for (int i = 0; i < 65536; i++) {
    map1.emplace(std::to_string(i), i);
    map2.emplace(std::to_string(i), i);
    map3.emplace(std::to_string(i), i);
  }

  start1 = std::chrono::steady_clock::now();
  for (auto iter = map1.begin(); iter != map1.end();) {
    if (cond(iter->second)) {
      iter = map1.erase(iter);
    } else {
      ++iter;
    }
  }
  end1 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count()
            << std::endl;

  auto cond_map = [](const auto& item) {
    auto const& [key, value] = item;
    return (value & 1 == 1);
  };
  start3 = std::chrono::steady_clock::now();
  std::erase_if(map3, cond_map);
  end3 = std::chrono::steady_clock::now();
  std::cout << "time cost(us): " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count()
            << std::endl;
  */

  return 0;
}

