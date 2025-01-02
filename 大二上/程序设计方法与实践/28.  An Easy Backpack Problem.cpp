#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

ll gcd(ll a, ll b);
void printchar(char c, int n);

int main() {
    int n, v;
    cin >> n >> v;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i] %= v;
    }    

    vector<vector<ll>> dp(n + 1, vector<ll>(v ,0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i ++) {
        for (int j = 0; j < v; j ++) {
            dp[i][j] = dp[i - 1][j];

            int pack = (j - p[i - 1] + v) % v;
            dp[i][j] = (dp[i][j] + dp[i - 1][pack]) % MOD;
        }
    }

    cout << dp[n][0] - 1 << endl;
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