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
int bfs(const vector<string>& maze, int n, int m, int k, int sx, int sy, int ex, int ey);
bool valid(int x, int y, int n, int m);

int main() {
	int t;
	scanf("%d", &t); 
	
	for (int i = 0; i < t; i ++) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		
		vector<string> maze(n);
		for (int j = 0; j < n; j ++) {
			cin >> maze[j];
		}
		
		int sx, sy, ex, ey;
		for (int j = 0; j < n; j ++) {
			for (int h = 0; h < m; h ++) {
				if (maze[j][h] == 'S') {
					sx = j; 
					sy = h;
				} else if (maze[j][h] == 'E') {
					ex = j;
					ey = h;
				}
			}
		}
		
		int result = bfs(maze, n, m, k, sx, sy, ex, ey);
		cout << result << endl;
	}
	return 0;
}

int bfs(const vector<string>& maze, int n, int m, int k, int sx, int sy, int ex, int ey) {
	vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(k, false)));
	queue<tuple<int, int, int>> q;
	
	q.push(tuple<int, int, int>(sx, sy, 0));
	visited[sx][sy][0] = true;
	
	while (!q.empty()) {
		int x = get<0>(q.front());
		int y = get<1>(q.front());
		int t = get<2>(q.front());
		q.pop();
		
		if (x == ex && y == ey) {
			return t;
		} 
		
		for (int i = 0; i < 4; i ++) {
			int next_x = x + dire[i][0];
			int next_y = y + dire[i][1];
			int next_t = t + 1;
			
			if (valid(next_x, next_y, n, m) && maze[next_x][next_y] != '#' && !visited[next_x][next_y][next_t % k]) {
				if (maze[next_x][next_y] == '*' && next_t % k != 0) {
					continue;
				} 
				
				visited[next_x][next_y][next_t % k] = true;
				q.push(tuple<int, int, int>(next_x, next_y, next_t));
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


