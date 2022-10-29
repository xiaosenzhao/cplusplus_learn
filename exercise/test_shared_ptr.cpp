#include <iostream>
#include <future>
#include <thread>
#include <memory>

using namespace std;
class Person {
public:
    Person(int v) {
        value = v;
        std::cout << "Cons" << value << std::endl;
    }
    ~Person() {
        std::cout << "Des" << value << std::endl;
    }

    int value;
};

int main() {
    std::shared_ptr<Person> p1(new Person(1)); //Person1的引用计数为1
    std::shared_ptr<Person> p2 = std::make_shared<Person> (2);
    p1.reset(new Person(3)); // 首先生成新对象，然后旧对象引用计数减1，引用计数为0，故析构Person1
                             // 然后将新对象的指针交给智能指针
    std::shared_ptr<Person> p3 = p1; //复制构造函数，p1和p3同时指向Person3
                                     // 最好不要这样做，容易二次析构
    p1.reset(); 
    p3.reset();
    return 0;
}