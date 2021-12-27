#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

struct Item {
  int id;
  int score;
  Item(int id_, int score_) {
    id = id_;
    score = score_;
  }
};

void add(std::vector<Item>* item_vec, std::unordered_map<int, Item*>* item_map) {
  int id = rand();
  int score = rand();

  item_vec->emplace_back(id, score);
  item_map->emplace(id, (item_vec->data() + item_vec->size() - 1)); //因为empalce_back, 可能导致元素移动，所以指针会失效
}

void print(std::vector<Item>* item_vec, std::unordered_map<int, Item *>* item_map) {
  std::stringstream ss;
  for (const auto& item : *item_vec) {
    ss << item.id << ":" << item.score << " ";
  }
  std::cout << ss.str() << std::endl;

  std::stringstream ss_1;
  for (const auto [id, pitem] : *item_map) {
    ss_1 << pitem->id << ":" << pitem->score <<" ";
  }
  std::cout << ss_1.str() << std::endl;
}

int main(void) {
  srand(time(0));
  std::vector<Item> item_vec;
  //item_vec.reserve(1000); //预分配空间会避免指针失效·
  std::unordered_map<int, Item*> item_map;
  for (int i = 0; i < 10; i++) {
    add(&item_vec, &item_map);
  }
  print(&item_vec, &item_map);
  return 0;
}



