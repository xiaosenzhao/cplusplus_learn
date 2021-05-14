#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubble_sort(int arr[], int len) {
    if (len <= 0 || arr == nullptr) {
        return;
    }
    for (int i = 0; i < len - 1; i++){
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selection_sort(int arr[], int len) {
    if (len <= 0 || arr == nullptr) {
        return;
    }
    int min = 0;
    int index = -1;
    for (int i = 0; i < len - 1; i++) {
        min = arr[i];
        index = i;
        for (int j = i + 1; j < len - 1; j++) {
            if (arr[j] < min) {
                min = arr[j];
                index = j;
            }
        }
        swap(arr[i], arr[index]);
    }
}

void insert_sort(int arr[], int len) {
    if (arr == nullptr || len <= 0) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && (key < arr[j])) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

void shell_sort(int arr[], int len) {
    if (arr == nullptr || len <= 0) {
        return;
    }

    int gap = 0;
    while (gap < len / 3) {
        gap = gap * 3 + 1;
    }

    while (gap >= 1) {
        for (int i = gap; i < len; i++) {
            for (int j = i; j >= gap && arr[j] < arr[j - gap]; j -= gap) {
                swap(arr[j], arr[j - gap]);
            }
        }
        gap = gap / 3;
    }
}

//快速排序
int partition(int arr[], int low, int high) {
    if (arr == nullptr || low >= high) {
        return -1;
    }
    int pivot = arr[low];
    while (low < high) {
        while (low < high && arr[high] >= pivot) {
            high -= 1;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot) {
            low += 1;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void quick_sort(int arr[], int low, int high) {
    if (low >= high || arr == nullptr) {
        return;
    }

    int pivot = partition(arr, low, high);
    quick_sort(arr, low, pivot - 1);
    quick_sort(arr, pivot + 1, high);
}
//

int main(void) {
    //rand nums
    unsigned int seed = time(0);
    srand(seed);
    int nums[15];
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;

    //bubble sort 冒泡排序
    bubble_sort(nums, 15);
    cout << "bubble: ";
    for (int i = 0; i < 15; i++){
        cout << nums[i] << ' ';
    }
    cout << endl;
    cout << "==================================" << endl;
        
    //rand nums
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;
    //selection sort 选择排序
    selection_sort(nums, 15);
    cout << "selection: ";
    for (int i = 0; i < 15; i++) {
        cout << nums[i] << ' ';
    }
    cout <<endl;
    cout << "==================================" << endl;

    //rand nums
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;
    //insert sort 插入排序
    insert_sort(nums, 15);
    cout << "insert: ";
    for (int i = 0; i < 15; i++) {
        cout << nums[i] << ' ';
    }
    cout <<endl;
    cout << "==================================" << endl;

    //rand nums
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;
    //shell sort希尔排序
    insert_sort(nums, 15);
    cout << "shell: ";
    for (int i = 0; i < 15; i++) {
        cout << nums[i] << ' ';
    }
    cout <<endl;
    cout << "==================================" << endl;

    //rand nums
    cout << "==================================" << endl;
    cout << "origin: ";
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;
    //快速排序
    quick_sort(nums, 0, 14);
    cout << "quick sort: ";
    for (int i = 0; i < 15; i++) {
        cout << nums[i] << ' ';
    }
    cout << endl;
    cout << "==================================" << endl;

    return 0;
}

