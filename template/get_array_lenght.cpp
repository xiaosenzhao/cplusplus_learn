#include <iostream>

// 使用模板获取数组大小
template <typename T, size_t N>
inline size_t GetArrayLength(const T (&)[N]) {
  return N;
}

int main(void) {
  int a[] = {0, 1, 2, 3, 4};
  std::cout << GetArrayLength(a) << std::endl;
  return 0;
}

