#include <iostream>
class A;
class B;

void f(A* a) {
  std::cout << "A" << std::endl;
}

void f(void* c) {
  std::cout << "void" << std::endl;
}

int main(void) {
  B* x = nullptr;
  f(x);
  return 0;
}
