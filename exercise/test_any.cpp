#include <any>
#include <iostream>

int main(void) {
  std::any a = 1;
  std::cout << a.type().name() << ": " << std::any_cast<int>(a) << std::endl;
  a = 3.14;
  std::cout << a.type().name() << ": " << std::any_cast<double>(a) << std::endl;
  a = true;
  std::cout << std::boolalpha;
  std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << std::endl;

  try {
    a = 1;
    std::cout << std::any_cast<float>(a) << std::endl;
  } catch (std::bad_any_cast& e) {
    std::cout << e.what() << std::endl;
  }

  a = 1;
  if (a.has_value()) {
    std::cout << a.type().name() << std::endl;
  }

  a.reset();
  if (!a.has_value()) {
    std::cout << "no value" << std::endl;
  }

  a = 1;
  int* i = std::any_cast<int>(&a);
  std::cout << *i << std::endl;

  return 0;
}
