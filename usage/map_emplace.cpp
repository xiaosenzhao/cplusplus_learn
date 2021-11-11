#include <map>
#include <string>
#include <iostream>

struct DocInfo {
  std::string a;
  std::string b;
};

struct Elem {
  std::string id;
  double score;
  DocInfo doc_info;
  Elem(std::string a, double b) :
      id(a),
      score(b) {}
  std::string to_string() {
    return id + std::to_string(score);
  }
};

int main(void) {
  std::map<std::string, Elem> map;
  map.emplace("a", Elem("aa", 0.1));
  Elem elem("bb", 1.1);
  map.emplace("b", std::move(elem));

  for (auto [key, value] : map) {
    std::cout << key << " " << value.to_string() << std::endl;
  }
  return 0;
}
