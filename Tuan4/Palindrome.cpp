#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& str) {
    int i = 0;
    int j = str.length() - 1;
    while (i < j) {
        if (str[i] != str[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    string str; cin >> str;
    if (isPalindrome(str)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}
