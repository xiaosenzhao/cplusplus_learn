#include <vector>

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> flag;
        flag.resize(board.size());
        for (int i = 0; i <board.size(); i++) {
            flag[i].resize(board[i].size());
            for (int j = 0; j < board[i].size(); j++) {
                flag[i][j] = false;
            }
        }
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j <board[0].size(); j++) {
                if (dfs(board, flag, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(const vector<vector<char>>& board, vector<vector<bool>>& flag,
            const string word, int i, int j, int k) {
        if (i >= board.size() || i < 0 ||
                j >= board[0].size() || j < 0) {
            return false;
        }
        if (flag[i][j]) {
            return false;
        }
        if (board[i][j] != word[k]) {
            return false;
        }
        if (k == word.size() - 1) {
            return true;
        }

        flag[i][j] = true;
        bool res = dfs(board, flag, word, i - 1, j, k + 1) ||
            dfs(board, flag, word, i + 1, j, k + 1) ||
            dfs(board, flag, word, i, j - 1, k + 1) ||
            dfs(board, flag, word, i, j + 1, k + 1);
        flag[i][j] = false;
        return res;
    }
};
