#include <bits/stdc++.h>
using namespace std;
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int a[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j< n - i - 1; j++) {
            if(a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
            }
        }
    }
}
void printArray(int a[], int n) {
    for(int i=0; i<n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int array[30] = {99, 56, 33, 20, 87, 76, 91, 68, 5, 3, 80, 90, 1, 77, 84, 97, 63, 92, 8, 71, 26, 37, 40, 70, 16, 55, 60, 17, 54, 11};
    BubbleSort(array, 30);
    printArray(array, 30);
    return 0;
}