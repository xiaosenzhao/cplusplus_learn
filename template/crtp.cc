#include <iostream>

template <typename D>
class Base {
 public:
  template <typename T>
  void UseDerived(const T&& arg) {
    D* ptr = static_cast<D*>(this);
    ptr->Impl(std::forward<const T>(arg));
  }
};

class Derived: public Base<Derived> {
 public:
  template <typename T>
  void Impl(const T&& arg) {
    std::cout << "derived class " << arg << std::endl;
  }
};

int main(void) {
  Derived a;
  a.UseDerived(1);
  return 0;
}
