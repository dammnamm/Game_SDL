#include <bits/stdc++.h>
using namespace std;

string dectobin(int n)
{
    if(n == 0) return "0";
    else if(n == 1) return "1";
    else return dectobin(n/2) + to_string(n%2);
}

int main()
{
    int n; cin >> n;
    n = abs(n);
    cout << dectobin(n) << endl;
}