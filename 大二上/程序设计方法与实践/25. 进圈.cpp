#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

const int dire[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Node {
	int x, y, t;
};

ll gcd(ll a, ll b);
void printchar(char c, int n);
int bfs(const vector<string>& maze, int n, int m, int k, int sx, int sy, int ex, int ey);
bool valid(int x, int y, int n, int m);

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	
	vector<string> maze(n);
	for (int i = 0; i < n; i ++) {
		cin >> maze[i];
	}
	
	int sx, sy, ex, ey;
	scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
	sx --; sy --; ex --; ey --;
	
	int result = bfs(maze, n, m, k, sx, sy, ex, ey);

	cout << result << endl;
	return 0;
}

int bfs(const vector<string>& maze, int n, int m, int k, int sx, int sy, int ex, int ey) {
	if (sx == ex && sy == ey) {
		return 0;
	}

	vector<vector<int>> visited_s(n, vector<int>(m, -1));
	vector<vector<int>> visited_e(n, vector<int>(m, -1));
	
	queue<Node> q_s, q_e;

	q_s.push({sx, sy, 0});
	q_e.push({ex, ey, 0});

	visited_s[sx][sy] = 0;
	visited_e[ex][ey] = 0;

	while (!q_s.empty() && !q_e.empty()) {
		int start_size = q_s.size();
		while (start_size --) {
			Node curr = q_s.front();
			q_s.pop();

			for (int i = 0; i < 4; i ++) {
				for (int step = 1; step <= k; step ++) {
					int next_x = curr.x + dire[i][0] * step;
					int next_y = curr.y + dire[i][1] * step;

					if (!valid(next_x, next_y, n, m) || maze[next_x][next_y] == '#') {
						break;
					}

					if (visited_e[next_x][next_y] != -1) {
						return curr.t + 1 + visited_e[next_x][next_y];
					}

					if (visited_s[next_x][next_y] == -1) {
						visited_s[next_x][next_y] = curr.t + 1;
						q_s.push({next_x, next_y, curr.t + 1});
					}
				}
			}
		}

		int end_size = q_e.size();
		while (end_size --) {
			Node curr = q_e.front();
			q_e.pop();

			for (int i = 0; i < 4; i ++) {
				for (int step = 1; step <= k; step ++) {
					int next_x = curr.x + dire[i][0] * step;
					int next_y = curr.y + dire[i][1] * step;

					if (!valid(next_x, next_y, n, m) || maze[next_x][next_y] == '#') {
						break;
					}

					if (visited_s[next_x][next_y] != -1) {
						return curr.t + 1 + visited_s[next_x][next_y];
					}

					if (visited_e[next_x][next_y] == -1) {
						visited_e[next_x][next_y] = curr.t + 1;
						q_e.push({next_x, next_y, curr.t + 1});
					}
				}
			}
		}
	}
	return -1;
}

bool valid(int x, int y, int n, int m) {
	return x >= 0 && y >= 0 && x < n && y < m;
}

void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		cout << c;
	}
}

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}


