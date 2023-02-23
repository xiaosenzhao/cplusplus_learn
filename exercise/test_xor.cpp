#include <iostream>

int main(void) {
  int64_t gid = 340483190093254657;
  std::cout << (gid ^ 0x0000000000000000) << std::endl;
  int a = (gid ^ 0);
  std::cout << a << std::endl;
  gid = 2910986982983212065;
  std::cout << (gid ^ 0) << std::endl;
  gid = 0;
  std::cout << (gid ^ 0) << std::endl;

  return 0;
}

