#include <iostream>
#include <type_traits>

class Base {};
class Derived : public Base {};

int main(void) {
  // 让输出流将bool解析成true或false
  // 执行下面语句后，输出流中的bool值都转成字符串"true"或"false"
  // 执行 std::cout << std::noboolalpha; 输出流中bool值恢复为0或1
  std::cout << std::boolalpha << std::endl;

  std::cout << "std::is_base_of<Base, Derived>::value: "
            << std::is_base_of<Base, Derived>::value << std::endl;
  std::cout << "std::is_base_of<Derived, Base>::value: "
            << std::is_base_of<Derived, Base>::value << std::endl;
  std::cout << "std::is_base_of<Derived, Derived>::value: "
            << std::is_base_of<Derived, Derived>::value << std::endl;

  std::cout << std::endl;

  std::cout << "std::is_convertible<Base*, Derived*>::value: "
            << std::is_convertible<Base*, Derived*>::value << std::endl;
  std::cout << "std::is_convertible<Derived*, Base*>::value: "
            << std::is_convertible<Derived*, Base*>::value << std::endl;
  std::cout << "std::is_convertible<Derived*, Derived*>::value: "
            << std::is_convertible<Derived*, Derived*>::value << std::endl;

  std::cout << std::endl;

  std::cout << "std::is_same<int, int32_t>::value: "
            << std::is_same<int, int32_t>::value << std::endl;
  std::cout << "std::is_same<int, int64_t>::value: "
            << std::is_same<int, int64_t>::value << std::endl;
  std::cout << "std::is_same<long int, int64_t>::value: "
            << std::is_same<long int, int64_t>::value << std::endl;
  std::cout << "std::is_same<long int, uint32_t>::value: "
            << std::is_same<long int, uint32_t>::value << std::endl;
  std::cout << "std::is_same<long long, int64_t>::value: "
            << std::is_same<long long, int64_t>::value << std::endl;
  return 0;
}
