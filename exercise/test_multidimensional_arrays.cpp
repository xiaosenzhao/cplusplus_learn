// clang++ test_multidimensional_arrays.cpp -o test --std=c++2b
#include <array>
#include <iostream>

template <typename T, size_t R, size_t C>
struct matrix {
  T& operator[](const size_t r, const size_t c) noexcept { return data_[r * C + c]; }
  const T& operator[](const size_t r, const size_t c) const noexcept { return data_[r * C + c]; }

 private:
  std::array<T, R * C> data_;
};

int main(void) {
  matrix<int, 2, 2> m;
  m[0, 0] = 0;
  m[0, 1] = 1;
  m[1, 0] = 2;
  m[1, 1] = 3;

  for (auto i = 0; i < 2; ++i) {
    for (auto j = 0; j < 2; ++j) {
      std::cout << m[i, j] << ' ';
    }
    std::cout << std::endl;
  }
  return 0;
}
