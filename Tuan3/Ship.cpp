#include <bits/stdc++.h>
using namespace std;

struct Rect {
     int x,y;
     int w,h;
};

struct Ship {
    Rect rec;
    string id;
    int dx, dy;
    void move() {
        rec.x += dx;
        rec.y += dy;
    }
};

void display(const Ship& ship) {
    Rect rec = ship.rec;
    cout << rec.x << " " << rec.y << " " << ship.id;
}

int main()
{
    Ship ship;
    Rect rec = ship.rec;
    cin >> rec.x >> rec.y >> ship.dx >> ship.dy >> ship.id;
    ship.move();
    display(ship);
    return 0;
}