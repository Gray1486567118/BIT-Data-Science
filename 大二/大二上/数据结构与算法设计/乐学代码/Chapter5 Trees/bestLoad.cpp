#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;



int maxLoad = 0;
vector<int> bestSolution;
int c, n;
vector<int> weights;



void backtrack(int index, int currLoad, vector<int>& currSolution);



int main() {
    // input
    cin >> c >> n;
    weights.resize(n);
    for (int i = 0; i < n; i ++) {
        cin >> weights[i];   
    }

    vector<int> currSolution;
    backtrack(0, 0, currSolution);

    // output
    cout << maxLoad << endl;

    for (int i: bestSolution) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}


void backtrack(int index, int currLoad, vector<int>& currSolution) {
    // trim
    if (currLoad > c) {
        return;
    }

    if (currLoad > maxLoad || (currLoad == maxLoad && currSolution < bestSolution)) {
        maxLoad = currLoad;
        bestSolution = currSolution;
    }

    if (index == n) {
        return;
    }

    currSolution.push_back(index + 1);
    backtrack(index + 1, currLoad + weights[index], currSolution);
    currSolution.pop_back();  // backtrack

    backtrack(index + 1, currLoad, currSolution);
}
