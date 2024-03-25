#include <bits/stdc++.h>

using namespace std;

// Hàm khởi tạo bản đồ với các quả mìn được đặt ngẫu nhiên
vector<vector<char>> initializeBoard(int m, int n, int k) {
    vector<vector<char>> board(m, vector<char>(n, '0'));
    srand(time(NULL));
    set<int> mines;
    while (mines.size() < k) {
        int mine = rand() % (m * n);
        mines.insert(mine);
    }
    for (int mine : mines) {
        int row = mine / n;
        int col = mine % n;
        board[row][col] = '*';
    }
    return board;
}

// Hàm in bản đồ
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Hàm kiểm tra xem một ô có phải là quả mìn không
bool isMine(const vector<vector<char>>& board, int row, int col) {
    return board[row][col] == '*';
}

// Hàm đếm số quả mìn xung quanh một ô
int countAdjacentMines(const vector<vector<char>>& board, int row, int col) {
    int count = 0;
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 8; ++i) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board[0].size() && isMine(board, newRow, newCol)) {
            count++;
        }
    }
    return count;
}

// Hàm hiển thị bản đồ sau khi mở một ô
void revealCell(vector<vector<char>>& board, int row, int col) {
    if (board[row][col] != '0') {
        return;
    }
    int count = countAdjacentMines(board, row, col);
    board[row][col] = '0' + count;
    if (count == 0) {
        int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        for (int i = 0; i < 8; ++i) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];
            if (newRow >= 0 && newRow < board.size() && newCol >= 0 && newCol < board[0].size()) {
                revealCell(board, newRow, newCol);
            }
        }
    }
}

// Hàm chơi trò chơi
void playGame(int m, int n, int k) {
    vector<vector<char>> board = initializeBoard(m, n, k);
    printBoard(board);
    while (true) {
        int x, y;
        cout << "Enter the coordinates (x, y): ";
        cin >> x >> y;
        if (isMine(board, x, y)) {
            cout << "YOU'RE DEAD!" << endl;
            // In ra bản đồ với tất cả các quả mìn
            for (const auto& row : board) {
                for (char cell : row) {
                    if (cell == '*') {
                        cout << "* ";
                    } else {
                        cout << countAdjacentMines(board, &cell - &row[0], &cell - &row[0]) << " ";
                    }
                }
                cout << endl;
            }
            break;
        } else {
            revealCell(board, x, y);
            printBoard(board);
        }
    }
}

int main() {
    int m, n, k;
    cout << "Enter the size of the board (m, n) and number of mines (k): ";
    cin >> m >> n >> k;
    playGame(m, n, k);
    return 0;
}
