#include <bits/stdc++.h>
using namespace std;

bool eq(int a[], int b[], int n) {
    for(int i= 0; i<n; i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

int main()
{
    int a[] = {1,2,3,4,5,6,7,8,9};
    int b[] = {1,2,3,4,5,6,7,8,9};
    cout << eq(a, b , 9);
    return 0;
}