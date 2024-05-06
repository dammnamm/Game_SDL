#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
void recursion(int n, string s, vector<char> chars){
    if(s.size() == n){
        cnt++;
        return;
    }
    for(int i=0; i<chars.size(); i++){
        recursion(n, s+chars[i], chars);
    }
}

int main() {
    string s; cin >> s;
    vector<char> chars;
    for(int i=0; i<s.size(); i++){
        if(find(chars.begin(), chars.end(), s[i]) == chars.end()){
            chars.push_back(s[i]);
        }
    }
    recursion(chars.size(), "", chars);
    cout << cnt << endl;
    return 0;
}