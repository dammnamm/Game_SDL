#include <bits/stdc++.h>
using namespace std;

int sumArray(int a[], int n)
{
    if(n == 1) return a[0];
    return a[n-1] + sumArray(a, n-1);
}

int main()
{
    int n; cin >> n;
    int a[n]; for(int i=0; i<n; i++) cin >> a[i];
    cout << sumArray(a, n);
    return 0;
}