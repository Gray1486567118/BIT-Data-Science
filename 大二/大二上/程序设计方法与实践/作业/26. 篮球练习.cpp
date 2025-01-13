#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

vector<vector<bool>> can_pass(21, vector<bool>(21, true));
vector<vector<ll>> dp(21, vector<ll>(21, 0));

ll gcd(ll a, ll b);
void printchar(char c, int n);
bool valid(int ex, int ey, int x, int y);
void init_can_pass(vector<vector<bool>>& can_pass, int dx, int dy, int ex, int ey);

int main() {
	int dx, dy, ex, ey;
	cin >> ex >> ey >> dx >> dy;
	
	init_can_pass(can_pass, dx, dy, ex, ey);

	dp[0][0] = can_pass[0][0] ? 1 : 0;	
	
	for (int i = 0; i <= ex; i ++) {
		for (int j = 0; j <= ey; j ++) {
			if (can_pass[i][j]) {
				if (i > 0) {
					dp[i][j] += dp[i - 1][j];
				}
				if (j > 0) {
					dp[i][j] += dp[i][j - 1];
				}
			}
		}
	} 
	
	cout << dp[ex][ey] << endl;
	return 0;
}



void init_can_pass(vector<vector<bool>>& can_pass, int dx, int dy, int ex, int ey) {
	can_pass[dx][dy] = false;
	if (valid(ex, ey, dx + 2, dy + 1)) can_pass[dx + 2][dy + 1] = false;
    if (valid(ex, ey, dx + 1, dy + 2)) can_pass[dx + 1][dy + 2] = false;
    if (valid(ex, ey, dx - 1, dy + 2)) can_pass[dx - 1][dy + 2] = false;
    if (valid(ex, ey, dx - 2, dy + 1)) can_pass[dx - 2][dy + 1] = false;
    if (valid(ex, ey, dx - 2, dy - 1)) can_pass[dx - 2][dy - 1] = false;
    if (valid(ex, ey, dx - 1, dy - 2)) can_pass[dx - 1][dy - 2] = false;
    if (valid(ex, ey, dx + 1, dy - 2)) can_pass[dx + 1][dy - 2] = false;
    if (valid(ex, ey, dx + 2, dy - 1)) can_pass[dx + 2][dy - 1] = false;
}


bool valid(int ex, int ey, int x, int y) {
	if (x >= 0 && y >= 0 && x <= ex && y <= ey) {
		return true;
	} 
	return false;
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


