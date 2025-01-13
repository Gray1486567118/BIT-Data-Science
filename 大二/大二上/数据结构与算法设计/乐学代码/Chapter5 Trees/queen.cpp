#include <iostream>
using namespace std;

int n, m, totalSolutions;
int *row, *column, *slashDiagonal, *antiSlashDiagonal;

bool isValidPlacement() {
    for (int i = 1; i <= n; i++) {
        if (row[i] == 999) {
            for (int j = 1; j <= n; j++) {
                if (column[j] == 999) {
                    if (!(antiSlashDiagonal[i + j] == 1 || slashDiagonal[n + i - j + 1] == 1)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void searchSolutions(bool placeQueen, int level, int placedQueens) {
    if (level > n) {
        if (placedQueens == m && isValidPlacement()) {
            totalSolutions++;
        }
        return;
    }

    // 剪枝：当前剩余行数不足以放置剩余皇后
    if (n - level + placedQueens < m) {
        return;
    }

    // 尝试不放置和放置皇后的情况
    if (!placeQueen) {
        searchSolutions(false, level + 1, placedQueens);
        searchSolutions(true, level + 1, placedQueens + 1);
    } else {
        for (int i = 1; i <= n; i++) {
            if (column[i] == 999 && antiSlashDiagonal[level + i] == 999 && slashDiagonal[n + level - i + 1] == 999) {
                row[level] = level;
                column[i] = i;
                antiSlashDiagonal[level + i] = 1;
                slashDiagonal[n + level - i + 1] = 1;

                searchSolutions(false, level + 1, placedQueens);
                searchSolutions(true, level + 1, placedQueens + 1);

                row[level] = 999;
                column[i] = 999;
                antiSlashDiagonal[level + i] = 999;
                slashDiagonal[n + level - i + 1] = 999;
            }
        }
    }
}

int main() {
    cin >> n >> m;

    column = new int[n + 1];
    row = new int[n + 1];
    slashDiagonal = new int[2 * n + 1];
    antiSlashDiagonal = new int[2 * n + 1];

    // 初始化
    fill(column, column + n + 1, 999);
    fill(row, row + n + 1, 999);
    fill(slashDiagonal, slashDiagonal + 2 * n + 1, 999);
    fill(antiSlashDiagonal, antiSlashDiagonal + 2 * n + 1, 999);

    totalSolutions = 0;
    searchSolutions(false, 1, 0);
    searchSolutions(true, 1, 1);

    cout << totalSolutions << endl;

    delete[] column;
    delete[] row;
    delete[] slashDiagonal;
    delete[] antiSlashDiagonal;

    return 0;
}
