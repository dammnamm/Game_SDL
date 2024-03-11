#include <bits/stdc++.h>
using namespace std;

void leftRotation(int a[], int n, int d) {
    while(d--) {
        int temp = a[0];
        for(int i=0; i<n-1; i++) {
            a[i] = a[i+1];
        }
        a[n-1] = temp;
    }
    for(int i=0; i<n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int n; cin >> n;
    int a[100];
    for(int i=0; i<n; i++) cin >> a[i];

    int d; cin >> d;

    leftRotation(a, n,  d);
}