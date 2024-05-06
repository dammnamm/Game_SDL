#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, b , c;
    cin >> a >> b >> c;
    cout << boolalpha << !(a + b == c || a == b + c || b == a + c) << endl;
    return 0;
}