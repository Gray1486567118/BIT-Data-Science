#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 101;
const int MOD = 10000000;


ll dp[N][N];
int triangle[N][N];



int main() {
    // input
    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= i; j ++) {
            cin >> triangle[i][j];
        }   
    }

    // dp
    // init dp
    for (int i = 1; i <= n; i ++) {
        dp[n][i] = triangle[n][i];
    }

    for (int i = n - 1; i >= 1; i --) {
        for (int j = 1; j <= i; j ++) {
            dp[i][j] = triangle[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }


    // result
    cout << dp[1][1] << endl;
    return 0;
}