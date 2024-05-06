#include <bits./stdc++.h>
using namespace std;

void printvector(vector<vector<int>> matrix) {
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, m; cin >> n >> m;
    int cnt = 1;
    vector<vector<int>> matrix(n, vector<int>(m));
    int top = 0, bottom = n - 1, left = 0, right = m - 1;
    while(top <= bottom && left <= right) {
        for(int i = left; i <= right; i++) {
            matrix[top][i] = cnt;
            cnt++;
        }
        top++;
        for(int i = top; i <= bottom; i++) {
            matrix[i][right] = cnt;
            cnt++;
        }
        right--;
        if(top <= bottom) {
            for(int i = right; i >= left; i--) {
                matrix[bottom][i] = cnt;
                cnt++;
            }
            bottom--;
        }
        if(left <= right) {
            for(int i = bottom; i >= top; i--) {
                matrix[i][left] = cnt;
                cnt++;
            }
            left++;
        }
    }
    printvector(matrix);
    return 0;
}