#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n;
    int temp; int k  = n;

    vector<int> a;

    while(k--) {
        cin >> temp;
        a.push_back(temp);
    }

    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n - i -1; j++) {
            if(a[j] > a[j+1]) {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    for(int i=0; i<n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}