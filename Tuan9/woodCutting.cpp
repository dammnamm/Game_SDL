#include <bits/stdc++.h>
using namespace std;

int cuttingWood(int n, int a[])
{
    if( n == 0)
    {
        return 0;
    }

    int max_ = INT_MIN;
    for(int i=0; i < n; i++)
    {
        max_ = max(max_, a[i] + cuttingWood(n - i - 1, a));
    }
    return max_;
}

int main()
{
    int n; cin >> n;
    int a[n];
    for(int i=0; i<n; i++)
    {
        cin >> a[i];
    }
    cout << cuttingWood(n, a);
    return 0;
}