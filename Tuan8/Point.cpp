#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x;
    int y;
};

int main()
{
    Point point;
    point.x = 0;
    point.y = 0;
    cout << &point << " " << &point.x << " " << &point.y << endl;
    return 0;
}