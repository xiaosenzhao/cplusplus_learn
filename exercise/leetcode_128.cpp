#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int result = 0;
        unordered_set<int> set;

        for (const auto& num : nums) {
            set.insert(num);
        }

        while (!set.empty()) {
            auto iter = set.begin();
            int next = *iter + 1;
            int prev = *iter - 1;
            set.erase(*iter);

            while (set.count(next)) {
                set.erase(next);
                next += 1;
            }
            while (set.count(prev)) {
                set.erase(prev);
                prev -= 1;
            }

            result = max(result, next - prev - 1);
        }

        return result;
    }
};

int main(void) {
    vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
    Solution sol;
    cout << sol.longestConsecutive(nums) << endl;

    return 0;
}
