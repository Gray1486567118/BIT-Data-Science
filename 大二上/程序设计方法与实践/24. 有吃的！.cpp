#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

const int dire[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

ll gcd(ll a, ll b);
void printchar(char c, int n);
int bfs(const vector<string>& maze, int n, int m, int sx, int sy, int ex, int ey, const vector<pair<int, int>>& channels);
bool valid(int x, int y, int n, int m);

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	
	vector<string> maze(n);
	vector<pair<int, int>> channels;
	for (int i = 0; i < n; i ++) {
		cin >> maze[i];
	}
	
	int sx, sy, ex, ey;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j ++) {
			if (maze[i][j] == 'N') {
				sx = i; 
				sy = j;
			} else if (maze[i][j] == 'C') {
				ex = i;
				ey = j;
			} else if (maze[i][j] == 'E') {
				channels.push_back(pair<int, int>(i, j));
			}
		}
	}
	
	int result = bfs(maze, n, m, sx, sy, ex, ey, channels);

	if (result == -1) {
		cout << "Bad Eureka" << endl;
	} else {
		cout << result << endl;
	}
	return 0;
}

int bfs(const vector<string>& maze, int n, int m, int sx, int sy, int ex, int ey, const vector<pair<int, int>>& channels) {
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	queue<pair<int, int>> q;
	queue<int> steps;
	
	q.push(make_pair(sx, sy));
	steps.push(0);
	visited[sx][sy] = true;
	
	bool usedC = false;

	while (!q.empty()) {
		int x = get<0>(q.front());
		int y = get<1>(q.front());
		q.pop();

		int step = steps.front();
		steps.pop();
		
		if (x == ex && y == ey) {
			return step;
		} 
		
		for (int i = 0; i < 4; i ++) {
			int next_x = x + dire[i][0];
			int next_y = y + dire[i][1];
			
			if (valid(next_x, next_y, n, m) && maze[next_x][next_y] != 'M' && !visited[next_x][next_y]) {
				visited[next_x][next_y] = true;
				q.push(make_pair(next_x, next_y));
				steps.push(step + 1);
			}
		}

		if (maze[x][y] == 'E' && !usedC) {
			for (auto& channel : channels) {
				if (!visited[channel.first][channel.second]) {
					visited[channel.first][channel.second] = true;
					q.push(channel);
					steps.push(step);
				}
			}
			usedC = true;
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


