/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 */

// @lc code=start
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.length() == 0) {
            return word2.length();
        }
        if (word2.length() == 0) {
            return word1.length();
        }
        size_t m = word1.length();
        size_t n = word2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        
        int tmp = 0;
        for (size_t i = 0; i <= m; ++i) {
            for (size_t j = 0; j <= n; ++j) {
                tmp = 0;
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else {
                    tmp = word1[i - 1] == word2[j - 1] ? 0 : 1;
                    dp[i][j] = std::min(dp[i - 1][j - 1] + tmp,
                    std::min(dp[i-1][j] + 1, dp[i][j -1] + 1));
                }
            }
        }
        return dp[m][n];
    }
};
// @lc code=end

