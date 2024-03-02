#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
};

void print(Point a) {
    cout << a.x << " " << a.y << endl;
}

int main() {
    Point point;
    point.x = 10;
    point.y = 12;
    print(point);
    return 0;
}