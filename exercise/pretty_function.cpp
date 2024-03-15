#include <iostream>

template <typename T>
void func(T c) {
  std::cout << "__PRETTY_FUNCTION__ value: {" << __PRETTY_FUNCTION__
            << "}, __PRETTY_FUNCTION__ address: ";
  std::cout.operator<<(__PRETTY_FUNCTION__) << std::endl;
  std::cout << "__FUNCTION__ value: {" << __FUNCTION__
            << "} __FUNCTION__ address: ";
  std::cout.operator<<(__FUNCTION__) << std::endl;
}

int main(void) {
  func<int>(1);
  func<char>(1);

  return 0;
}