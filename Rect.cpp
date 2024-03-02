#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
    Point(int _x, int _y) {
        x =_x;
        y =_y;
    }
};

struct Rect {
    int x;
    int y;
    int w;
    int h;
    
    Rect(int _x, int _y, int _w, int _h) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    bool contain(const Point a) {
        if( ( x <= a.x && a.x <= x + w) && (y <= a.y && a.y <= y+h )) {
            return true;
        }
        return false;
    }
};

int main() {
    Rect rect(0,0, 3, 3);
    Point a(1,2);
    cout << rect.contain(a);
    return 0;
}