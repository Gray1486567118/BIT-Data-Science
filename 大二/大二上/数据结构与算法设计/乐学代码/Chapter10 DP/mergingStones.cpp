#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 201;
const int MOD = 10000000;


int stones[N];
int prefix[N];
int min_dp[N][N];
int max_dp[N][N];



int main() {
    // input
    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        cin >> stones[i];
        stones[i + n] = stones[i];
    }


    // init prefix
    prefix[0] = 0;

    for (int i = 1; i <= 2 * n; i ++) {
        prefix[i] = stones[i] + prefix[i - 1];
    }


    // init dp arrays
    memset(min_dp, INF, sizeof(min_dp));
    memset(max_dp, 0, sizeof(max_dp));
    for (int i = 1; i <= 2 * n; i ++) {
        min_dp[i][i] = 0;
        max_dp[i][i] = 0;
    }


    // dp
    for (int len = 1; len < n; len ++) {
        for (int i = 1; i <= 2 * n - len; i ++) {
            int j = i + len;

            for (int k = i; k < j; k ++) {
                int score = prefix[j] - prefix[i - 1];
                min_dp[i][j] = min(min_dp[i][j], min_dp[i][k] + min_dp[k + 1][j] + score);
                max_dp[i][j] = max(max_dp[i][j], max_dp[i][k] + max_dp[k + 1][j] + score);
            }
        }
    }


    // output
    int min_result = INF;
    int max_result = 0;

    for (int i = 1; i <= n; i ++) {
        min_result = min(min_result, min_dp[i][i + n - 1]);
        max_result = max(max_result, max_dp[i][i + n - 1]);
    }

    cout << min_result << endl;
    cout << max_result << endl;

    return 0;
}