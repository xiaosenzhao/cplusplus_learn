#include <iostream>

namespace ver1 {
class A {
 public:
  void func1() {
    std::cout << "A::func1()::ver1" << std::endl;
  }
};
}//ver1

namespace ver1 {
class B {
 public:
  void func2() {
    std::cout << "B::func2()::ver1" << std::endl;
  }
};
class C {
 public:
  void func3() {
    std::cout << "C::func3()::ver1" << std::endl;
  }
};
}

inline namespace ver2 {
class A {
 public:
  void func1() {
    std::cout << "A::func1()::ver2" << std::endl;
  }
};
}//ver2

namespace ver2 {
class B {
 public:
  void func2() {
    std::cout << "B::func2()::ver2" << std::endl;
  }
};
class C{
 public:
  void func3() {
    std::cout << "C::func3()::ver2" << std::endl;
  }
};
}//ver2

int main(void) {
  A a;
  B b;
  C c;
  a.func1();
  b.func2();
  c.func3();

  ver1::A a1;
  ver1::B b1;
  ver1::C c1;
  a1.func1();
  b1.func2();
  c1.func3();

  return 0;
}
