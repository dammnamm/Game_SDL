#include <bits/stdc++.h>
using namespace std;

int _sum(int n)
{
    if( n == 1) return 1;
    return n + _sum(n-1);
}

int main()
{
    int n; cin >> n;
    cout << _sum(n) << endl;
    return 0;
}