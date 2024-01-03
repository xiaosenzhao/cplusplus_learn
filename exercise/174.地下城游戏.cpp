/*
 * @lc app=leetcode.cn id=174 lang=cpp
 *
 * [174] 地下城游戏
 */

// @lc code=start
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        size_t m = dungeon.size();
        size_t n = dungeon[0].size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, std::numeric_limits<int>::max()));
        dp[m - 1][n] = dp[m][n - 1] = 1;
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int minn = std::min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = std::max(minn - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};
// @lc code=end

