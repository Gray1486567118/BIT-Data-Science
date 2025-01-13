#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;


int main() {
    // input
    int n;
    vector<pair<int, int>> acts;
    scanf("%d", &n);

    for (int i = 0; i < n; i ++) {
        int start, end;
        scanf("%d %d", &start, &end);

        acts.emplace_back(start, 1);
        acts.emplace_back(end, -1);
    }


    // sort
    sort(acts.begin(), acts.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

    // for (const auto &act : acts) {
    //     cout << act.first << " " << act.second << endl;
    // }


    // scan
    int curr_rooms = 0, max_rooms = 0;

    for (const auto& act : acts) {
        curr_rooms += act.second;
        max_rooms = max(max_rooms, curr_rooms);
    }


    // output
    printf("%d\n", max_rooms);
    return 0;
}