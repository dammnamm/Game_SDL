#include <iostream>
#include <string>

bool isPalindrome(const std::string& str) {
    int start = 0;
    int end = str.length() - 1;
    while (start < end) {
        if (str[start] != str[end]) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

int main() {
    int n; std::cin >> n;
    std::string str = std::to_string(n);
    if (isPalindrome(str)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    return 0;
}
