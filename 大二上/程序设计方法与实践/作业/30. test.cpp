#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

vector<ll> dp(30001, 0); 

ll gcd(ll a, ll b);
void printchar(char c, int n);

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> t(m), w(m);
    for (int i = 0; i < m; i ++) {
        cin >> t[i] >> w[i];
    }

    for (int j = 0; j < m; j ++) {
        for (int i = n; i >= t[j] ; i --) {
            dp[i] = max(dp[i], dp[i - t[j]] + t[j] * w[j]);
        }
    }

    cout << dp[n] << endl;
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