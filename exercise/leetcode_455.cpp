#include <vector>

int findContentChildren(std::vector<int>& children, std::vector<int>& cookies) {
  std::sort(children.begin(), children.end());
  std::sort(cookies.begin(), cookies.end());
  int child = 0;
  int cookie = 0;
  while (child < children.size() && cookie < cookies.size()) {
    if (child <= cookie) {
      child += 1;
      cookie += 1;
    } else {
      cookie += 1;
    }
  }
  return child;
}


