#include <iostream>

// 基类指针，调用基类的成员函数，访问成员变量，访问的是基类的成员变量
class Base {
 public:
  void Print() { std::cout << name_ << std::endl; }

 private:
  std::string name_ = "Base";
};

class Derived : public Base {
 private:
  std::string name_ = "Derived";
};

int main(void) {
  Base* ptr = new Derived();
  ptr->Print();

  return 0;
}
