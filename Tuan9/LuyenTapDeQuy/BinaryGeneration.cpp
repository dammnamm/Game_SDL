#include <bits/stdc++.h>
using namespace std;


int n, a[100], isFinal;

void init()
{
    for(int i=1; i<=n; i++)
    {
        a[i] = 0;
    }
}

void generate()
{
    int i = n;
    while( i >= 1 && a[i] == 1)
    {
        a[i] = 0;
        i--;
    }
    if( i == 0)
    {
        isFinal = 1; 
    }else
    {
        a[i] = 1;
    }
}

int main()
{
    cin >> n;
    isFinal = 0;
    while(isFinal == 0)
    {
        for(int i=1; i<=n; i++)
        {
            cout << a[i];
        }cout << endl;
        generate();
    }
    return 0;
}