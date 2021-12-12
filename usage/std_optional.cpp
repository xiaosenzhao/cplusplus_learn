#include <iostream>
#include <string>
#include <optional>

struct Item {
  std::string id;
  double score;

  Item(){
    std::cout << "Item()" << std::endl;
  }

  Item(const Item& i) {
    std::cout << "Item(const Item&)" << "key:" << i.id << ", score: " << i.score << std::endl;
    id = i.id;
    score = i.score;
  }

  Item& operator=(const Item& i) {
    std::cout << "Item& operator=" << "key:" << i.id << ", score: " << i.score << std::endl;
    this->id = i.id;
    this->score = i.score;
    return *this;
  }

  Item(const Item&& i) {
    std::cout << "Item(const Item&&)" << "key:" << i.id << ", score: " << i.score << std::endl;
    id = i.id;
    score = i.score;
  }
};

std::optional<Item> GetItem1() {
  Item item;
  item.id = "test1";
  item.score = 0.1;

  return item; //右值移动
}

std::optional<Item> GetItem2() {
  Item item;
  item.id = "test2";
  item.score = 0.2;

  return {item}; //左值拷贝
}

std::optional<Item> GetItem3() {
  std::optional<Item> item = std::make_optional<Item>();
  item->id = "test3";
  item->score = 0.3;

  return item; //无移动拷贝
}

std::optional<Item> GetItem4() {
  return std::nullopt;
}

std::optional<Item> GetItem5() {
  return {}; //同4
}

std::optional<std::string> GetString() {
  return std::nullopt;
}

int main(void) {
  std::optional<Item> item1 = GetItem1();
  std::cout << item1->id << ":" << item1->score << std::endl;

  std::optional<Item> item2 = GetItem2();
  std::cout << item2->id << ":"  << item2->score << std::endl;

  std::optional<Item> item3 = GetItem3();
  std::cout << item3->id << ":" << item3->score << std::endl;

  std::optional<Item> item4 = GetItem4();
  std::cout << (item4.has_value() ? "test4:0.4" : "empty") << std::endl;

  std::optional<Item> item5 = GetItem5();
  std::cout << (item5.has_value() ? "test5:0.5" : "empty") << std::endl;

  std::cout << (GetString().value_or("no vlue")) << std::endl;

  return 0;
}
