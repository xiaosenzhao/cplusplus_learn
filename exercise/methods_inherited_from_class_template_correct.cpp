// 有三种方法解决调用模板基类函数编译失败问题
#include <iostream>

template <typename T>
class Base {
 public:
  void func1() const {
    std::cout << "func1()" << std::endl;
  }

  void func2() const {
    std::cout << "func2()" << std::endl;
  }

  void func3() const {
    std::cout << "func3()" << std::endl;
  }
};

template <typename T>
class Derived : public Base<T> {
 public:
  using Base<T>::func2; // 解决方法一
  void CallBaseFun() {
    this->func1(); // 解决方法二
    func2();
    Base<T>::func3(); // 解决方法三
  }
};

int main(void) {
  std::cout << std::endl;

  Derived<int> derived;
  derived.CallBaseFun();

  std::cout << std::endl;
}
