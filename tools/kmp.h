#include <string>
#include <vector>

using namespace std;

vector<int> generate_next(const string& p) {
    if (p.size() == 0) {
        return vector<int>();
    }
    vector<int> next(p.size() + 1, 0);

    int k = -1;
    int i = 0;
    next[0] = -1;
    while (i < p.size() - 1) {
        if (k == -1 || p[k] == p[i]) {
            i += 1;
            k += 1;
            next[i] = k;
        } else {
            k = next[k];
        }
    }
    return next;
}
    
bool search(const string& s, const string& p) {
    int n = s.size();
    int m = p.size();
    vector<int> next = generate_next(p);
    if (next.size() == 0) {
        return false;
    }

    int i = 0;
    int j = -1;
    while (i < n && j < m) {
        if (j == -1 || s[i] == p[j]) {
            i += 1;
            j += 1;
        } else {
            j = next[j];
        }
    }
    if (j >= m) {
        return true;
    }
    return false;
}

