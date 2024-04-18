#include <bits/stdc++.h>
using namespace std;

void hanoiTower(int n, char a, char b, char c)
{
    if( n == 1 )
    {
        cout << a << " ---> " << c << endl;
        return ;
    }
    else
    {
        hanoiTower(n-1, a, c, b); //chuyen n-1 dia tu a sang b lay c lam trung gian
        hanoiTower(1, a, b, c); // chuyen 1 dia tu a sang b lay c lam trung gian
        hanoiTower(n-1, b , a , c); // chuyen n-1 dia tu b sang c lay a lam trung gian;
    }
}

int main()
{
    char a = 'A', b = 'B' , c = 'C';
    int n; cin >> n;
    hanoiTower(n, a , b , c); // Chuyen n dia tu cot A sang cot C


    return 0;
}