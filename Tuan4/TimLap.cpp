#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n; cin >> n;
    bool seen[1000001] = {false};
    bool flag = false;
    for(int i=0; i<n; i++)
    {
        int temp;
        cin >> temp;
        if(seen[temp] == false)
        {
            seen[temp] = true;
        }else {
            flag = true;
            break;
        }
    }
    if(flag) cout << "Yes";
    else cout << "No";
    return 0;
}