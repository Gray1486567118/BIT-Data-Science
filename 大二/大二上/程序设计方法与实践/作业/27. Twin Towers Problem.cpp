#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

ll gcd(ll a, ll b);
void printchar(char c, int n);
int main() {
    int n1, n2;
    cin >> n1 >> n2;
    int count = 1;

    while (n1 != 0 && n2 != 0) {
        vector<int> t1(n1), t2(n2);
        for (int i = 0; i < n1; i ++) {
            cin >> t1[i];
        }

        for (int i = 0; i < n2; i ++) {
            cin >> t2[i];
        }

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

        for (int i = 1; i <= n1; i ++) {
            for (int j = 1; j <= n2; j ++) {
                if (t1[i - 1] == t2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        cout << "Twin Towers #" << count << endl;
        count ++;
        cout << "Number of Tiles : " << dp[n1][n2] << endl;

        cin >> n1 >> n2;
    }
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