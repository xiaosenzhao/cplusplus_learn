#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
int main(void) {
    std::multiset<int> nums;
    std::multiset<int, less<int>> nums1;
    std::multiset<int, greater<int>> nums2;

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int rand_result = rand() % 100;
        nums.insert(rand_result);
        nums1.insert(rand_result);
        nums2.insert(rand_result);
        cout << rand_result << ' ';
    }
    cout << endl;

    cout << "nums: ";
    for (auto& num : nums) {
        cout << num << ' ';
    }
    cout << endl;
    cout << "nums1: ";
    for (auto& num : nums1) {
        cout << num << ' ';
    }
    cout << endl;
    cout << "nums2: ";
    for (auto& num : nums2) {
        cout << num << ' ';
    }
    cout << endl;

    return 0;
}

    
