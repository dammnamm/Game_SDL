#include <bits/stdc++.h>
using namespace std;

void rotate_to_left(vector<int> &a){
    int n = a.size();
    int temp = a[0];
    for(int i=0; i<n-1; i++){
        a[i] = a[i+1];
    }
    a[n-1] = temp;
}

void printVector(vector<int> a){
    for(int i=0; i<a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n; cin >> n ;
    vector<int> a;
    for(int i=1; i<=n; i++){
        a.push_back(i);    
    }
    for(int i=0; i<n; i++){
        printVector(a);
        rotate_to_left(a);
    }
    return 0;
}