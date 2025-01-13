#include <bits/stdc++.h>
using namespace std;

int main() {
    int m;
    cin >> m;

    while (m --) {
        string s;
        cin >> s;

        int count = 0, enter = 0, out = 0;
        for (char c : s) {
            if (c == '+') {
                if (out > 0) {
                    out --;
                } else {
                    count ++;
                }
                enter ++;
            } else {
                if (enter > 0) {
                    enter --;
                } else {
                    count ++;
                }
                out ++;
            }
        }

        cout << count << endl; 
    }
    return 0;
}