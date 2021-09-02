#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        if (points.size() == 0) {
            return 0;
        }

        unordered_map<double, int> map; //斜率, 个数
        int result = 1;
        for (int i = 0; i < points.size() - 1; i++) {
            map.clear();
            int same = 1;
            int same_y = 1;
            for (int j = i + 1; j < points.size(); j++) {
                if (points[i][1] == points[j][1]) {
                    same_y += 1;
                    if (points[i][0] == points[j][0]) {
                        same += 1;
                    }
                } else {
                    int dx = points[j][0] - points[i][0];
                    int dy = points[j][1] - points[i][1];
                    double k = (double)dx / (double)dy;
                    if (map.find(k) == map.end()) {
                        map[k] = 1;
                    } else {
                        map[k] = map[k] + 1;
                    }
                }
            }
            result = max(result, same_y);
            for (const auto elem : map) {
                result = max(result, same + elem.second);
            }
        }
        return result;
    }
};

int main(void) {
    vector<vector<int>> points = {{1,1}, {3,2},{5,3},{4,1},{2,3},{1,4}};
    Solution solu;
    cout << solu.maxPoints(points) << endl;
    return 0;
}
