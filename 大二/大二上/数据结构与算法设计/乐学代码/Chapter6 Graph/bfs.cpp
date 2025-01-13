#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

map<char, bool> visited;
string bfsResult;

class ALGraph {
public:
    map<char, vector<char>> adjList;
    map<int, char> indexToVertex;
    map<char, int> vertexToIndex;

    void addEdge(char u, char v) {
        adjList[u].insert(adjList[u].begin(), v);
        adjList[v].insert(adjList[v].begin(), u);
    }

    void printGraph() {
        cout << "the ALGraph is" << endl;
        for (auto &pair : adjList) {
            cout << pair.first;
            for (auto &neighbour : pair.second) {
                cout << " " << vertexToIndex[neighbour];
            }
            cout << endl;
        }
    }

    string BFS(char start, map<char, bool> &visited) {
        string result;
        queue<char> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            result += curr;

            for (char neighbour : adjList[curr]) {
                if (!visited[neighbour]) {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }

        return result;
    }
};


int main() {
    ALGraph graph;

    int index = 0;
    char vertex, startVertex;
    while (cin >> vertex && vertex != '*') {
        graph.adjList[vertex] = {};
        if (index == 0) startVertex = vertex;

        graph.indexToVertex[index] = vertex; 
        graph.vertexToIndex[vertex] = index;
        index++;
    }

    cin.ignore();
    string edge;
    
    while (getline(cin, edge) && edge != "-1,-1") {
        stringstream ss(edge);
        string part;
        int m, n;

        getline(ss, part, ',');
        m = stoi(part);

        getline(ss, part, ',');
        n = stoi(part);

        char v1 = graph.indexToVertex[m];
        char v2 = graph.indexToVertex[n];
        graph.addEdge(v1, v2);
    }

    graph.printGraph();

    for (const auto &pair : graph.adjList) {
        if (!visited[pair.first]) {
            bfsResult += graph.BFS(pair.first, visited);
        }
    }
    cout << "the Breadth-First-Seacrh list:" << bfsResult << endl;
    return 0;
}