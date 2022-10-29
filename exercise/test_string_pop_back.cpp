#include <iostream>
#include <string>

int main() {
    std::string str("hello world\t");
    std::cout << str << std::endl;
    std::cout << str.size() << std::endl;
    str.pop_back();
    std::cout << str << std::endl;
    std::cout << str.size() << std::endl;
    std::string str1 = "";
    std::cout << str1.size() << std::endl;
    return 0;
}
