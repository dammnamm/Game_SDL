#include <bits/stdc++.h>
using namespace std;

void reverse(char a[])
{
    int n = strlen(a);
    for(int i=0; i<n/2; i++) {
        char temp = a[i];
        a[i] = a[n - i - 1];
        a[n-i-1] = temp;
    }
}

void delete_char(char a[], char c)
{
    int idx = 0;
    int n = strlen(a);
    for(int i=0; i<n; i++) {
        if(a[i] != c) {
            a[idx++] = a[i];
        }
    }
    a[idx] = '\0';
}

void pad_right(char a[], int n)
{
    int length = strlen(a);
    if(length < n) {
        for(int i=length; i<n; i++) {
            a[i] = ' ';
        }
        a[n] = '\0';
    }
}
void pad_left(char* a, int n) {
    int length = strlen(a);
    if (length < n) {
        for (int i = n - 1; i >= 0; i--) {
            if (i >= n - length) {
                a[i] = a[i - (n - length)];
            } else {
                a[i] = ' ';
            }
        }
        a[n] = '\0';
    }
}

int main()
{
    char str[] = "Hello, world!";
    //reverse
    reverse(str);
    cout << "str after reverse : " << str << endl;
    reverse(str);
    //delete
    delete_char(str, 'H');
    cout << "str after deleting 'H': " << str << endl;

    //pad_right
    pad_right(str, 15);
    cout << "str after padright: " << str << endl;

    //pad_left
    pad_left(str, 20);
    cout << "str after padleft: " << str << endl;
    
    return 0;
}