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
    int n;
    cin >> n;

    vector<int> treats(n);
    for (int i = 0; i < n ; i ++) {
        cin >> treats[i];
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i ++) {
        dp[i][i] = treats[i] * n;
    }

    for (int candies = 2; candies <=n; candies ++) {
        for (int l = 0; l <= n - candies; l ++) {
            int r = l + candies - 1;
            int age = n - r + l;
            dp[l][r] = max(treats[l] * age + dp[l + 1][r], 
                           treats[r] * age + dp[l][r - 1]);
        }
    }

    cout << dp[0][n - 1] << endl;

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