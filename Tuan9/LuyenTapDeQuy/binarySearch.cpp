#include <iostream>
using namespace std;


int a[100001];

int binSearch(int left, int right, int k)
{
    int mid = (left + right)/2;
    if(a[mid] == k) return mid;
    else if( k < a[mid] && left < mid) return binSearch(left, mid-1, k);
    else if( k > a[mid] && right > mid) return binSearch(mid + 1, right, k);
    else return 0;
}

int main()
{
    int n, k;
    cin >> n >> k;
    for(int i = 0; i<n; i++)
    {
        cin >> a[i];
    }
    cout << a[binSearch(0, n-1, k)];
    return 0;
}