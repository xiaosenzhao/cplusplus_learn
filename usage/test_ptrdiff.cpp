#include <cstddef>
#include <iostream>

int main(void) {
  const std::size_t N = 10;
  int* a = new int[N];
  int* end = a + N;
  for (std::ptrdiff_t i = N; i > 0; --i) {
    *(end - i) = i;
  }
  for (std::size_t i = 0; i < N; i++) {
    std::cout << a[i] << std::endl;
  }
  delete a;
}
