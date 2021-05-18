#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
void print_ivec(const vector<int>& vector) {
    for (auto& num : vector) {
        cout << num << '\t';
    }
    cout << endl;

}

int main(void) {
    int a[] = {1, 12, 15, 20, 30};
    vector<int> ivec(a, a + sizeof(a) / sizeof(a[0]));
    print_ivec(ivec);
    cout << (is_heap(ivec.begin(), ivec.end()) ? "is_heap" : "is_not_heap") << endl;

    make_heap(ivec.begin(), ivec.end());
    print_ivec(ivec);
    cout << (is_heap(ivec.begin(), ivec.end()) ? "is_heap" : "is_not_heap") << endl;

    pop_heap(ivec.begin(), ivec.end());
    print_ivec(ivec);
    ivec.pop_back();
    print_ivec(ivec);
    cout << (is_heap(ivec.begin(), ivec.end()) ? "is_heap" : "is_not_heap") << endl;

    ivec.push_back(99);
    print_ivec(ivec);
    push_heap(ivec.begin(), ivec.end());
    print_ivec(ivec);
    cout << (is_heap(ivec.begin(), ivec.end()) ? "is_heap" : "is_not_heap") << endl;

    sort_heap(ivec.begin(), ivec.end());
    print_ivec(ivec);
    cout << (is_heap(ivec.begin(), ivec.end()) ? "is_heap" : "is_not_heap") << endl;

    return 0;
}
