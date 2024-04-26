#include <iostream>
using namespace std;

int mpower(int a, int b , int n)
{
    if( b == 0) return 1;
    else if( b%2 == 0)
    {
        return (mpower(a, b/2, n)*mpower(a, b/2, n))%n;
    }else {
        return (((mpower(a, b/2, n)*mpower(a, b/2, n))%n)*(a%n))%n;
    }
}
//Calculate a^b mod n;
int main()
{
    int a, b , n;
    cin >> a >> b >> n;

    cout << mpower(a, b, n);
    return 0;
}