#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 1500;
const int MOD = 10000000;



vector<int> graph[N]; // graph 
int dp[N][2];         // dp
bool visited[N];      // visited


void dfs(int u);


int main() {
    int n;

    while (scanf("%d", &n) != EOF) {
        // init
        for (int i = 0; i < n; i ++) {
            graph[i].clear();
        }
        memset(dp, 0, sizeof(dp));
        memset(visited, false, sizeof(visited));

        // input graph
        for (int i = 0; i < n; i ++) {
            int u, m;
            char c;
            cin >> u >> c >> c >> m >> c;

            for (int j = 0; j < m; j++) {
                int v;
                cin >> v;
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }

        dfs(0);

        cout << min(dp[0][0], dp[0][1]) << endl;
    }
    return 0;
}



void dfs(int u) {
    // dfs + dp
    visited[u] = true;
    dp[u][0] = 0;
    dp[u][1] = 1;

    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v);
            dp[u][0] += dp[v][1];
            dp[u][1] += min(dp[v][1], dp[v][0]);
        }
    }
}