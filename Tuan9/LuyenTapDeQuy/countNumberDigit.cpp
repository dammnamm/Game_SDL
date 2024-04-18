#include <bits/stdc++.h>
using namespace std;

int digits(int n)
{
    if(n < 0) return digits(-n);
    else if( n < 10) return 1;
    else return digits(n/10) + 1;
}

int main()
{
    int n; cin >> n;
    cout << digits(n) << endl;
    return 0;
}