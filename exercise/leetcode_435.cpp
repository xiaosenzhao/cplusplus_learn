#include <vector>

int process(std::vector<std::vector<int>>& intervals) {
  if (intervals.empty()) {
    return 0;
  }

  std::sort(intervals.begin(), intervals.end(),
            [](std::vector<int>& a, std::vector<int>& b) {
              return a[1] < b[1];
            });
  int remove = 0;
  int prev = intervals[0][1];
  for (size_t i = 1; i < intervals.size(); ++i) {
    if (intervals[i][0] < prev) {
      remove += 1;
    } else {
      prev = intervals[i][1];
    }
  }
  return remove;
}

