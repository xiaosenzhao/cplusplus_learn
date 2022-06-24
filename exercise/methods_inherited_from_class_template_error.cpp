#include <iostream>

template <typename T>
class Base {
 public:
  void func() {
    std::cout << "func" << std::endl;
  }
};

template <typename T>
class Derived : public Base<T> {
 public:
  void CallBase() {
    // there are no arguments to 'func' that depend on a template parameter, so a declaration of 'func' must be available [-fpermissive]
    func();
  }
};

int main() {
  std::cout << std::endl;

  Derived<int> derived;
  derived.CallBase();

  std::cout << std::endl;
  return 0;
}
