#include <bits/stdc++.h>
using namespace std;    

int main()
{
    int n; cin >> n ;
    int pre = INT_MAX;
    for(int i=0; i<n; i++)
    {
        int temp; cin >> temp;
        if(temp != pre){
            cout << temp << " ";
            pre = temp;
        }
    }
    
    return 0;
}