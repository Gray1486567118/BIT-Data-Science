#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int N = 10001;
const int MOD = 10000000;



const int INF = 0x3f3f3f3f;
vector<vector<int>> adjMatrix; // 邻接矩阵存储图
vector<int> shortestDist;      // 存储最短距离
vector<bool> visited;          // 标记节点是否已访问
int n, m; 



void dijkstra(int source) {
    shortestDist.assign(n, INF);
    visited.assign(n, false);
    shortestDist[source] = 0;
    
    for (int i = 0; i < n; i++) {
        // 找到当前未访问的节点中距离源节点最短的节点
        int minDist = INF, u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && shortestDist[j] < minDist) {
                minDist = shortestDist[j];
                u = j;
            }
        }

        // 如果没有可访问的节点，结束
        if (u == -1) break;

        visited[u] = true;

        // 更新与 u 相邻节点的最短距离
        for (int v = 0; v < n; v++) {
            if (!visited[v] && adjMatrix[u][v] != INF) {
                shortestDist[v] = min(shortestDist[v], shortestDist[u] + adjMatrix[u][v]);
            }
        }
    }
}

int main() {
    char ch, a, b, c;
    cin >> m >> ch >> n >> ch >> c; 

    adjMatrix.assign(n, vector<int>(n, INF)); // 初始化
    for (int i = 0; i < n; i++) {
        adjMatrix[i][i] = 0; // 自己到自己距离为 0
    }

    // 读取边的信息
    for (int i = 0; i < n; i++) {
        int dist;
        cin >> ch >> a >> ch >> b >> ch >> dist >> ch;
        int u = a - 'a', v = b - 'a'; 
        adjMatrix[u][v] = min(adjMatrix[u][v], dist); 
    }

    int source = c - 'a';

    dijkstra(source);

    // 输出
    for (int i = 0; i < m; i++) {
        cout << (char)(i + 'a') << ":" << (shortestDist[i] == INF ? -1 : shortestDist[i]) << endl;
    }

    return 0;
}