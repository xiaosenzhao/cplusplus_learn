#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
//基数排序 
int maxbit(int data[], int n); // 求数据的最夽�数j
void radixsort(int data[], int n); //基数排序

int maxbit(int data[], int n) {
    int maxData = data[0];
    for (int i = 1; i < n; i++) {
        maxData = max(maxData, data[i]);
    }

    int count = 1;
    while (maxData >= 10) {
        maxData /= 10;
        count += 1;
    }

    return count;
}

void radixsort(int data[], int n) {
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10];
    int radix = 1;
    for (int i = 1; i <= d; i++) {
        for (int j = 0; j < 10; j++) {
           count[j] = 0;
        }
        for (int j = 0; j < n; j++) {
            count[data[j] / radix % 10] += 1;
        }
        for (int j = 1; j <10; j++) {
            count[j] = count[j - 1] + count[j];
        }
        for (int j = n - 1; j >=0; j--) {
            int k = data[j] / radix % 10;
            tmp[count[k] - 1] = data[j];
            count[k] -= 1;
        }
        for (int j = 0; j < n; j++) {
            data[j] = tmp[j];
        }
        radix = radix * 10;
    }

    delete []tmp;
    delete []count;
}

int main(void) {
    srand(time(0));
    int nums[15];
    for (int i = 0; i < 15; i++) {
        nums[i] = rand() % 100;
        cout << nums[i] << ' ';
    }
    cout << endl;

    radixsort(nums, 15);

    for (int i = 0; i < 15; i++) {
        cout << nums[i] << ' ';
    }
    cout <<endl;
    return 0;
}



