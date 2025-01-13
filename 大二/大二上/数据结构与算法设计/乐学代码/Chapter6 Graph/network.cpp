#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int MOD = 10000000;



struct Edge {
    int to, cost;
    Edge(int t, int c) : to(t), cost(c) {}

    bool operator<(const Edge &e2) const {
        return cost > e2.cost;
    }
};




int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i ++) {
        int v1, v2, cost;
        cin >> v1 >> v2 >> cost;
        graph[v1].emplace_back(v2, cost);
        graph[v2].emplace_back(v1, cost);
    }

    vector<bool> visited(n + 1, false);
    priority_queue<Edge> pq;
    pq.emplace(1, 0);

    int minCost = 0, edgeCount = 0;

    while (!pq.empty()) {
        Edge curr = pq.top();
        pq.pop();

        int v = curr.to, cost = curr.cost;
        if (visited[v]) {
            continue;
        }

        visited[v] = true;
        minCost += cost;
        edgeCount ++;

        for (const Edge &e : graph[v]) {
            if (!visited[e.to]) {
                pq.emplace(e.to, e.cost);
            }
        }
    }

    if (edgeCount == n) {
        cout << minCost << endl;
    } else {
        cout << "-1" << endl;
    }
    return 0;
}