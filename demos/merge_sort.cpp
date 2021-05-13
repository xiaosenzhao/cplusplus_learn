#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;
//递归合并排序
void merge(vector<int>& array, int front, int mid, int end) {
    vector<int> left_sub_array(array.begin() + front, array.begin() + mid + 1);
    vector<int> right_sub_array(array.begin() + mid + 1, array.begin() + end + 1);
    int idxleft = 0, idxright = 0;
    left_sub_array.insert(left_sub_array.end(), numeric_limits<int>::max());
    right_sub_array.insert(right_sub_array.end(), numeric_limits<int>::max());
    for (int i = front; i <= end; i++) {
        if (left_sub_array[idxleft] < right_sub_array[idxright]) {
            array[i] = left_sub_array[idxleft];
            idxleft++;
        } else {
            array[i] = right_sub_array[idxright];
            idxright++;
        }
    }
}

void merge_sort_1(vector<int>& array, int front, int end) {
    if (front >= end) {
        return;
    }

    int mid = (front + end) / 2;
    merge_sort_1(array, front, mid);
    merge_sort_1(array, mid + 1, end);
    merge(array, front, mid, end);
}

//迭代归并排序
void merge_sort_2(int arr[], int len) {
    if (len <= 0 || arr == nullptr) {
        return;
    }

    int* a = arr;
    int* b = new int[len];

    for (int seg = 1; seg < len; seg += seg) {
        for (int start = 0; start < len; start += seg + seg) {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2) {
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            }
            while (start1 < end1) {
                b[k++] = a[start1++];
            }
            while (start2 < end2) {
                b[k++] = a[start2++];
            }
        }

        int* tmp = a;
        a = b;
        b = tmp;
    }
    if (a != arr){
        for (int i = 0; i < len; i++) {
            b[i] = a[i];
        }
        b = a;
    }
    delete []b;
}

int main(void) {
    vector<int> nums;
    //rand nums
    unsigned int seed = time(0);
    srand(seed);
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        nums.push_back(rand() % 100);
        cout << nums[i] << ' ';
    }
    cout << endl;
    //递归归并排序
    merge_sort_1(nums, 0, 14);
    cout << "merge_1: ";
    for (int i = 0; i < 15; i++){
        cout << nums[i] << ' ';
    }
    cout << endl;
    cout << "==================================" << endl;
    //迭代归并排序 
    int arr[15];
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << ' ';
    }
    cout << endl;
    merge_sort_2(arr, 15);
    cout << "merge_2: ";
    for (int i = 0; i < 15; i++){
        cout << arr[i] << ' ';
    }
    cout << endl;
    cout << "==================================" << endl;

    return 0;
}

