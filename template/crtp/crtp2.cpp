#include <iostream>

// 记录实例化对象个数
template <typename T>
class Base {
 public:
  static int getObjCnt() { return cnt; }

 protected:
  static int cnt;
};
template <typename T>
int Base<T>::cnt = 0;

class Derived1 : public Base<Derived1> {
 public:
  Derived1() { cnt += 1; }
};

class Derived2 : public Base<Derived2> {
 public:
  Derived2() { cnt += 1; }
};

int main(void) {
  Derived1 d11, d12, d13;
  Derived2 d21, d22;

  std::cout << "Derived1::getObjCnt() = " << Derived1::getObjCnt() << std::endl;
  std::cout << "Derived2::getObjCnt() = " << Derived2::getObjCnt() << std::endl;

  return 0;
}