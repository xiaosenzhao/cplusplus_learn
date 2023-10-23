#include <iostream>
#include <memory>

class A {
 public:
  ~A() { std::cout << "A" << std::endl; }
};

class B : public A {
 public:
  ~B() { std::cout << "B" << std::endl; }
};

template <typename T, typename U>
class _shared {
 public:
  _shared(U* p) : p_(p) {}
  ~_shared() { delete p_; }

 private:
  U* p_;
};

template <typename T>
class _shared1 {
 public:
  _shared1(T* p) : p_(p) {}
  ~_shared1() { delete p_; }

 private:
  T* p_;
};

int main(void) {
  // std::shared_ptr<A> ptr(new B());  // 调用B, A的析构函数
  // _shared<A, B> ptr(new B()); // 调用 B、A 的析构函数
  // _shared1<A> ptr(new B());  // 调用 A 的析构函数
  return 0;
}

