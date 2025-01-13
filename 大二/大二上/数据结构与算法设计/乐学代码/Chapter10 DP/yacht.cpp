#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

ll gcd(ll a, ll b);
void printchar(char c, int n);


int cost[250][250];
int dp[250][250];

int main() {
	int n;
	cin >> n;
	
	for (int i = 1; i < n; i ++) {
		for (int j = i; j < n; j ++) {
			cin >> cost[i][j];
		}
	} 
	
	for (int i = 1; i < n; i ++) {
		dp[i][i] = cost[i][i];
	}
	
	for (int step = 1; step < n - 1; step ++) {
		for (int i = 1; i + step <= n - 1; i ++) {
			int j = i + step;
			dp[i][j] = cost[i][j];
			for (int k = i; k < j; k ++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		}
	}
	
	cout << dp[1][n - 1] << endl;
	return 0;
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


