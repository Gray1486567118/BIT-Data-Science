#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;



ull max_nodes(ull n, ull m);



int main() {
    int t;
    cin >> t;

    while (t --) {
        ull n, m;
        cin >> n >> m;
        ull result = max_nodes(n, m);
        cout << result << endl;
    }
    return 0;
}



ull max_nodes(ull n, ull m) {
    ull pow2m = pow(2, m);
    if (n <= m) return 0;
    if (n >= pow2m * 2 - 1) return pow2m;
    if (n >= pow2m && n < pow2m + m) return pow2m / 2;
    if (n >= pow2m + m) return pow2m / 2 + max_nodes(n - pow2m + 1, m);

    ull curr_n = m + 1;
    ull adder = 2;
    ull curr_adder = 2;
    ull node = 1;
    int flag = 0;
    while (curr_n <= n) {
        if (flag == 0) {
            curr_n += 1;
        } else {
            curr_n += curr_adder;
            if (curr_adder == 2) {
                adder ++;
                curr_adder = adder;
            } else {
                curr_adder --;
            }
        }

        // 1 2 1 3 1 2 1 4 1 2 1 3 1 2 1 /5

        node ++;
        flag = 1 - flag;
    }
    
    return --node;
}