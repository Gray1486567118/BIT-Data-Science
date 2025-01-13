#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 110;
const int MOD = 10000000;

int n, m;
// int dire[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int dx[4] = {0, 1, 0, -1};  
int dy[4] = {-1, 0, 1, 0}; 

vector<pair<int, int>> path;
int maze[N][N];
bool visited[N][N];

bool isValid(int x, int y);
bool dfs(int x, int y);


int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            cin >> maze[i][j];
        }
    }

    if (dfs(1, 1)) {
        for (const auto& p : path) {
            cout << "<" << p.first << "," << p.second << "> ";
        }
        cout << endl;
    } else {
        cout << "There is no solution!" << endl;
    }
    return 0;
}



bool dfs(int x, int y) {
    path.push_back({x, y});
    visited[x][y] = true;

    // end
    if (x == n && y == m) {
        return true;
    }

    for (int i = 0; i < 4; i ++) {
        int next_x = x + dx[i];
        int next_y = y + dy[i];

        // int next_x = x + dire[i][0];
        // int next_y = y + dire[i][1];

        if (isValid(next_x, next_y) && maze[next_x][next_y] == 0 && visited[next_x][next_y] == false) {
            if (dfs(next_x, next_y)) {
                return true;
            }
        }
    }

    path.pop_back();
    visited[x][y] = false;
    return false;
}

bool isValid(int x, int y) {
    return (x >= 1 && y >= 1 && x <= n && y <= m);
}
