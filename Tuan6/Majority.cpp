#include <bits/stdc++.h>
using namespace std;

bool majority(bool a, bool b, bool c) {
    return int(a) + int(b) + int (c) >= 2;
}

int main() {
    cout << majority(true, false, false);
    return 0;
}