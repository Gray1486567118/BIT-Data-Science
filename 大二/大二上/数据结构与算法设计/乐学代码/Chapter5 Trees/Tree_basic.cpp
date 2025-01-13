#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 100;
const int MOD = 10000000;


int main() {
    string gList;
    cin >> gList;

    int depth = 0;
    int max_degree = 0;
    int index = 0;
    vector<int> level(N, 0);
    vector<int> degree(N, 0);

    int pos = 1;
    int len = gList.length();

    while (pos < len) {
        char curr = gList[pos];

        if (isalpha(curr)) {
            for (int i = 0; i < depth; i ++)  cout << "    ";
            cout << curr << endl;

            level[index ++] = depth;
        } else if (curr == '(') {
            depth ++;
        } else if (curr == ')') {
            depth --;
        }

        pos ++;
    }

    for (int i = 0; i < index - 1; i ++) {
        for (int j = i + 1; j < index; j ++) {
            if (level[i] == level[j]) {
                break;
            }

            if (level[i] + 1 == level[j]) {
                degree[i] ++;
            }
        }

        max_degree = max(max_degree, degree[i]);
    }

    cout << "Degree of tree: " << max_degree << endl;

    vector<int> num_node_of_same_degree(N, 0);

    for (int i = 0; i < index; i ++) {
        num_node_of_same_degree[degree[i]] ++;   
    }

    for (int i = 0; i <= max_degree; i ++) {
        cout << "Number of nodes of degree " << i << ": " << num_node_of_same_degree[i] << endl;
    }
    return 0;
}

