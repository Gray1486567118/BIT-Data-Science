#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;



struct Compare {
    bool operator()(int a, int b) {
        return a > b;
    }
};



int main() {
    // input
    int n;
    cin >> n;

    priority_queue<int, vector<int>, Compare> minHeap;

    for (int i = 0; i < n; i ++) {
        int frequency;
        cin >> frequency;
        minHeap.push(frequency);   
    }


    // count WPL
    int wpl = 0;
    while (minHeap.size() > 1) {
        int min1 = minHeap.top();
        minHeap.pop();
        int min2 = minHeap.top();
        minHeap.pop();

        int sum = min1 + min2;
        wpl += sum;
        minHeap.push(sum);
    }

    cout << "WPL=" << wpl << endl;
    return 0;
}