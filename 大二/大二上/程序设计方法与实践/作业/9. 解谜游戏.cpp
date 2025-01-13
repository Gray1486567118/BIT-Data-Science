#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 16;

void printchar(char c, int n);
void click (int x, int y);
int solve();

int n, m;
int boxes[N][N], backup[N][N];

int main() {
	int i, j;
	cin >> n >> m; 
	
	for (i = 0; i < n; i ++) {
		string s;
		cin >> s;
		for (j = 0; j < m; j ++) {
			boxes[i][j] = s[j] - '0';
		}
	}
	
	int answer = -1;
	
	int first_line;
	for (first_line = 0; first_line < (1 << m); first_line ++) {
		memcpy(backup, boxes, sizeof(boxes));
		
		int result = 0;
		
		for (j = 0; j < m; j ++) {
			if (first_line >> j & 1) {
				click(0, j);
				result ++;
			}
		}
		
		int more_clicks = solve();
		
		if (more_clicks != -1) {
			result += more_clicks;
			
			if (result < answer || answer == -1) {
				answer = result;
			}
		}
		
		memcpy(boxes, backup, sizeof(boxes));
	}
	
	cout << answer << endl;
	return 0;
}


int solve() {
	int result = 0;
	int i, j;
	
	for (i = 1; i < n; i ++) {
		for (j = 0; j < m; j ++) {
			if (boxes[i - 1][j]) {
				click(i, j);
				result ++;
			}
		}
	}
	
	for (j = 0; j < m; j ++) {
		if (boxes[n - 1][j] == 1) {
			return -1;
		}
	}
	
	return result;
}

void click (int x, int y) {
	boxes[x][y] ^= 1;
	if (x > 0) {
		boxes[x - 1][y] ^= 1;
	}
	
	if (x < n - 1) {
		boxes[x + 1][y] ^= 1;
	}
	
	if (y > 0) {
		boxes[x][y - 1] ^= 1;
	}
	
	if (y < m - 1) {
		boxes[x][y + 1] ^= 1;
	}
}


void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		cout << c;
	}
}

