#include <bits/stdc++.h>
using namespace std;

int n, k, a[100], isFinal;

void init() {
    for(int i = 1; i<=k; i++) {
        a[i] = i;
    }
}

void generate()
{
    int i = k;
    while(i >= 1 && a[i] == n - k + i) {
        --i;
    }
     if(i == 0) {
        isFinal = 1;
    }else {
        a[i] ++;
        for(int j =i+1; j<=k; j++)
        {
            a[j] = a[j-1] + 1;
        }
    }
}


int main()
{
    cin >> n >> k;
    init();
    while(isFinal == 0)
    {
        for(int i=1; i<=k; i++)
        {
            cout << a[i] ;
        }cout << endl;
        generate();
    }
    return 0;
}