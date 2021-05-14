#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void heap_sort(int[], int);
void max_heapify(int[], int, int);

void heap_sort(int arr[], int len) {
    if (arr == nullptr || len <= 0) {
        return;
    }
    for (int i = len / 2 - 1; i >= 0; i--) {
        max_heapify(arr, i, len - 1);
    }
    for (int i = len - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}

void max_heapify(int arr[], int start, int end) {
    if (arr == nullptr || start > end) {
        return;
    }

    int dad = start;
    int son = dad *2 + 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1]) { //判断左右子树大小
            son += 1;
        }

        if (arr[dad] > arr[son]) {
            return;
        } else {
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

int main(void) {
    srand(time(0));
    int nums[15];
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;

    heap_sort(nums, 15);

    for (int i = 0; i < 15; i++) {
        cout << nums[i] <<' ';
    }
    cout << endl;

    return 0;
}
