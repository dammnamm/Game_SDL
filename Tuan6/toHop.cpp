#include <bits/stdc++.h>
using namespace std;

int toHop(int n, int k)
{
    if( k == 0 || n==k)
    {
        return 1;
    }
    return toHop(n-1, k) + toHop(n-1, k-1);
}

int main()
{
    int n; int k;
    cin >> n >> k;
    cout << toHop(n , k );
    return 0;
}