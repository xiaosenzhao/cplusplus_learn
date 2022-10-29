#include <iostream>
#include <vector>
#include <limits>

using namespace std;
class Solution {
public:
    int strangePrinter(string s) {
        if (s.size() == 0) {
            return 0;
        }
        size_t n = s.size();
        vector<vector<int>> d(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--) {
            d[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    d[i][j] = d[i][j - 1];
                } else {
                    int minn = std::numeric_limits<int>::max();
                    for (int k = i; k < j; k++) {
                        minn = min(d[i][k] + d[k + 1][j], minn);
                    }
                    d[i][j] = minn;
                }
            }
        }
        return d[0][n - 1];
    }
};

int main(void) {
    Solution solution;
    string s("aba");
    cout << solution.strangePrinter(s) << endl;
    return 0;
}
