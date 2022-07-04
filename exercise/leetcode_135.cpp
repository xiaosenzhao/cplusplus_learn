#include <vector>

int Process(std::vector<int>& children) {
  if (children.size() < 2) {
    return children.size();
  }

  std::vector<int> candy(children.size(), 1);
  for (size_t i = 1; i < children.size(); ++i) {
    if (children[i] > children[i - 1]) {
      candy[i] = candy[i - 1] + 1;
    }
  }
  for (size_t j = children.size() - 1; j > 0; --j) {
    if (children[j] < children[j - 1]) {
      candy[j - 1] = std::max(candy[j] + 1, candy[j - 1]);
    }
  }
  return std::accumulate(candy.begin(), candy.end(), 0);
}

