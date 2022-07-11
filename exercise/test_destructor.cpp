//基类析构函数是虚函数，派生类不声明成虚函数会怎样？
#include <iostream>

class Base {
 public:
  Base() {
    std::cout << "base Construct" << std::endl;
  }

  virtual ~Base() {
    std::cout << "base Destructor" << std::endl;
  }
};

class Derived : public Base {
 public:
  Derived() {
    std::cout << "derived Construct" << std::endl;
  }

  ~Derived() {
    std::cout << "derived Destructor" << std::endl;
  }
};

int main(void) {
  Base* p = new Derived();
  delete p;
  //
  //Derived* p = new Derived();
  //delete p;

  return 0;
}
