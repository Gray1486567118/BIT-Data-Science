#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

ll gcd(ll a, ll b);
void printchar(char c, int n);

struct Idiom {
    int a, b, c, d;
};


int bfs(int startI, int endI, const vector<Idiom>& idioms, const vector<vector<int>>& adjList);

int main() {
    int m;
    scanf("%d", &m);

    vector<Idiom> idioms(m);  
    vector<vector<int>> graph(m);  
    unordered_map<int, vector<int>> startWith, endWith;    

    
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &idioms[i].a, &idioms[i].b, &idioms[i].c, &idioms[i].d);
        startWith[idioms[i].a].push_back(i);  
        endWith[idioms[i].d].push_back(i);    
    }

    Idiom start, end;
    scanf("%d %d %d %d", &start.a, &start.b, &start.c, &start.d);
    scanf("%d %d %d %d", &end.a, &end.b, &end.c, &end.d);

    int startI = -1, endI = -1;


    for (int i = 0; i < m; i++) {
        if (idioms[i].a == start.a && idioms[i].b == start.b && idioms[i].c == start.c && idioms[i].d == start.d) {
            startI = i;
        }
        if (idioms[i].a == end.a && idioms[i].b == end.b && idioms[i].c == end.c && idioms[i].d == end.d) {
            endI = i;
        }
    }

    if (startI == endI) {
        printf("1\n");
        return 0;
    }

    for (unordered_map<int, vector<int>>::iterator it = endWith.begin(); it != endWith.end(); it ++) {
        int lastDigit = it->first;
        vector<int>& indices = it->second;

        if (startWith.count(lastDigit)) {
            vector<int>& startIndices = startWith[lastDigit];
            for (size_t i = 0; i < indices.size(); i++) {
                for (size_t j = 0; j < startIndices.size(); j++) {
                    if (indices[i] != startIndices[j]) {
                        graph[indices[i]].push_back(startIndices[j]);  
                    }
                }
            }
        }
    }

    int result = bfs(startI, endI, idioms, graph);
    printf("%d\n", result);

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


int bfs(int startI, int endI, const vector<Idiom>& idioms, const vector<vector<int>>& adjList) {
    int m = idioms.size();
    vector<bool> visited(m, false);  
    vector<int> steps(m, -1);        

    queue<int> q;
    q.push(startI);               
    visited[startI] = true;
    steps[startI] = 1;            

    while (!q.empty()) {
        int currentIdx = q.front();
        q.pop();

        for (size_t i = 0; i < adjList[currentIdx].size(); i++) {
            int nextIdx = adjList[currentIdx][i];
            if (!visited[nextIdx]) {
                visited[nextIdx] = true;
                steps[nextIdx] = steps[currentIdx] + 1;
                q.push(nextIdx);

                if (nextIdx == endI) {
                    return steps[nextIdx];  
                }
            }
        }
    }

    return -1;  
}
