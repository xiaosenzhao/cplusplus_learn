// map转vector
#include <iostream>
#include <map>
#include <vector>
#include <utility>

int main(void) {
  std::map<std::string, int> params;
  std::vector<std::pair<std::string, int>> vec;

  params["apple"] = 1;
  params["banana"] = 2;
  params["peach"] = 3;
  params["pear"] = 4;
  params["grape"] = 5;
  params["orange"] = 6;

  // template< class InputIt >
  // vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
  vec = {params.begin(), params.end()};

  for (const auto& pair : params) {
    std::cout << pair.first << " : " << pair.second << std::endl;
  }

  for (const auto& elem : vec) {
    std::cout << elem.first << " : " << elem.second << std::endl;
  }

  return 0;
}
