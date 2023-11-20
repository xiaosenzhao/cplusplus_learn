#include <iostream>
#include <string>

// const std::string& 字符串常量
// 实际上是拷贝
void func1(const std::string& str) {
  const char* ptr = str.data();
  std::cout << str.data() << std::endl;
  std::cout << (void*)ptr << std::endl;
}

void func2(const std::string& str) {
  const char* ptr = str.data();
  std::cout << str.data() << std::endl;
  std::cout << (void*)ptr << std::endl;
}

int main(void) {
  func1("hello world");
  func2("hello world");
  return 0;
}

