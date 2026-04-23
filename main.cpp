#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// 0: 無效區, 1: 空位, 2: 玩家A, 3: 玩家B
class ChineseCheckers {
private:
    int board[17][17];

public:
    ChineseCheckers() {
        initializeBoard();
    }

    void initializeBoard() {
        // 先將全部設為 0 (不可行走區域)
        for (int i = 0; i < 17; i++)
            for (int j = 0; j < 17; j++)
                board[i][j] = 0;

        // 簡化版：我們只初始化一個中間的 5x5 核心區域作為示範
        // 真正的中國跳棋需要定義星形的 121 個座標點
        for (int r = 4; r <= 12; r++) {
            for (int c = 4; c <= 12; c++) {
                board[r][c] = 1; // 1 代表可以走的空位
            }
        }

        // 放置玩家 A 與玩家 B 的起始棋子 (示範用)
        board[4][8] = 2;
        board[12][8] = 3;
    }

    void display() {
        cout << "    ";
        for (int i = 0; i < 17; i++) cout << setw(2) << i;
        cout << "\n----------------------------------------\n";
        for (int r = 0; r < 17; r++) {
            cout << setw(2) << r << "| ";
            for (int c = 0; c < 17; c++) {
                if (board[r][c] == 0) cout << "  ";
                else if (board[r][c] == 1) cout << ". ";
                else if (board[r][c] == 2) cout << "A ";
                else if (board[r][c] == 3) cout << "B ";
            }
            cout << endl;
        }
    }

    // 移動邏輯：中國跳棋可以移動到相鄰格，或是「跳過」一顆棋子
    bool isValidMove(int r1, int c1, int r2, int c2) {
        if (board[r1][c1] <= 1 || board[r2][c2] != 1) return false;

        // 簡單判斷：相鄰移動
        if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1) return true;

        // 跳躍判斷：目標點距離為 2，且中間有一顆棋子
        if (abs(r1 - r2) == 2 && abs(c1 - c2) == 2) {
            int midR = (r1 + r2) / 2;
            int midC = (c1 + c2) / 2;
            if (board[midR][midC] > 1) return true;
        }

        return false;
    }

    void move(int r1, int c1, int r2, int c2) {
        if (isValidMove(r1, c1, r2, c2)) {
            board[r2][c2] = board[r1][c1];
            board[r1][c1] = 1;
        }
        else {
            cout << "無效移動！" << endl;
        }
    }
};

int main() {
    ChineseCheckers game;
    int r1, c1, r2, c2;

    while (true) {
        game.display();
        cout << "請輸入移動 (起始R 起始C 目標R 目標C): ";
        cin >> r1 >> c1 >> r2 >> c2;
        game.move(r1, c1, r2, c2);
    }
    return 0;
}