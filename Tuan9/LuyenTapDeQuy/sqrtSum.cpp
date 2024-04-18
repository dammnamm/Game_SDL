#include <bits/stdc++.h>
using namespace std;

double sqrtSum(double n)
{
    if(n == 1) return 1;
    return sqrt(n + sqrtSum(n-1));
}


int main()
{
    double n; cin >> n;
    cout << fixed << setprecision(2) << sqrtSum(n) << endl;
    return 0;
}