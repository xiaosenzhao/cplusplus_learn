#include <iostream>

using namespace std;
template <typename T>
class Base {
 public:
  void foo() { static_cast<T*>(this)->internal_foo(); }
  void bar() { static_cast<T*>(this)->internal_bar(); }
};

class Derived1 : public Base<Derived1> {
 public:
  void internal_foo() { std::cout << "Derived1 foo" << std::endl; }
  void internal_bar() { std::cout << "Derived1 bar" << std::endl; }
};

class Derived2 : public Base<Derived2> {
 public:
  void internal_foo() { std::cout << "Derived2 foo" << std::endl; }
  void internal_bar() { std::cout << "Derived2 bar" << std::endl; }
};

// 每个子类对象都可以通过调用基类的 foo、bar函数来 redirect
// 到自己的内部实现。还可以增加下面两个 helper function。
template <typename T>
void foo(Base<T>& obj) {
  obj.foo();
}
template <typename T>
void bar(Base<T>& obj) {
  obj.bar();
}

int main(void) {
  Derived1 d1;
  Derived2 d2;

  foo(d1);
  foo(d2);
  bar(d1);
  bar(d2);

  d1.foo();
  d2.foo();
  d1.bar();
  d2.bar();
}