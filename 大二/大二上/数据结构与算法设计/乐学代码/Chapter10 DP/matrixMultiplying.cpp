#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 101;
const int MOD = 10000000;



int mat[N];
int dp[N][N];
int split[N][N];



void printSeq(int i, int j);



int main() {
    // input
    int n;
    cin >> n;

    for (int i = 0; i <= n; i ++) {
        cin >> mat[i];
    }

    if (n == 1) {
        printf("0\n(A1)\n");
        return 0;
    }
    
    // init
    memset(dp, 0, sizeof(dp));
    memset(split, 0, sizeof(split));

    // dp
    for (int len = 1; len < n; len ++) {
        for (int i = 1; i <= n - len; i ++) {
            int j = i + len;
            dp[i][j] = INF;
            

            for (int k = i; k < j; k ++) {
                int multiplying = mat[i - 1] * mat[k] * mat[j];
                int cost = dp[i][k] + dp[k + 1][j] + multiplying;
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    // output
    cout << dp[1][n] << endl;
    printSeq(1, n);
    cout << endl;
    return 0;
}


void printSeq(int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }

    cout << "(";
    printSeq(i, split[i][j]);
    printSeq(split[i][j] + 1, j);
    cout << ")";
}