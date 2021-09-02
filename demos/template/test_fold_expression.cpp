/* 变长参数模板 */
#include <iostream>

// 递归模板参数
template <typename T0>
void printf1(T0 value) {
    std::cout << value << std::endl;
}
template <typename T, typename... Ts>
void printf1(T value, Ts... args) {
    std::cout << value << std::endl;
    printf1(args...);
}

// 折叠表达式 c++17
// sizeof 参数个数
template <typename ...T>
auto average(T... args) {
    return (args + ...) / sizeof...(args);
}

int main() {
    std::cout << average(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    return 0;
}
