#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 201;
const int MOD = 10000000;



int rent[N][N];
int dp[N][N];



int main() {
    // input
    int n;
    cin >> n;

    for (int i = 1; i < n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            cin >> rent[i][j];
        }
    }

    // dp
    for (int step = 1; step < n; step ++) {
        for (int i = 1; i < n; i ++) {
            if (step == 1) {
                dp[i][i + step] = rent[i][i + step];
            } else {
                int min_rent = INF;
                for (int k = i + 1; k < i + step; k ++) {
                    min_rent = min(min_rent, dp[i][k] + dp[k][i + step]);
                }

                dp[i][i + step] = min(min_rent, rent[i][i + step]);
            }
        }
    }
    
    

    // result
    cout << dp[1][n] << endl;
    return 0;
}