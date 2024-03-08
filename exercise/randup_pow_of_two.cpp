#include <stdio.h>

#include <iostream>

inline int generic_fls(int x) {
  int r = 32;

  if (x == 0) {
    return 0;
  }
  if (x & 0xffff0000u == 0) {
    x <<= 16;
    r -= 16;
  }
  if (x & 0xff000000u == 0) {
    x <<= 8;
    r -= 8;
  }
  if (x & 0xf0000000u == 0) {
    x <<= 4;
    r -= 4;
  }
  if (x & 0xc0000000u == 0) {
    x <<= 2;
    r -= 2;
  }
  if (x & 0x80000000 == 0) {
    x <<= 1;
    r -= 1;
  }
  return r;
}

inline unsigned long __attribute__((const))
roundup_pow_of_two(unsigned long x) {
  std::cout << "roundup_pow_of_tow: " << x << std::endl;
  return (1UL << generic_fls(x - 1));
}

int main(void) {
  std::cout << roundup_pow_of_two(789) << std::endl;
  std::cout << roundup_pow_of_two(789) << std::endl;
  std::cout << roundup_pow_of_two(1025) << std::endl;
  std::cout << roundup_pow_of_two(9999) << std::endl;
}