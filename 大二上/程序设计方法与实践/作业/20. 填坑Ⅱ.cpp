#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

ll gcd(ll a, ll b);
void printchar(char c, int n);

int main() {
	int n;
	stack<int> s;
	
	while (cin >> n) {
		int no = 0;
		int highest = 0;
		
		for (int i = 0; i < n; i ++) {
			int input;
			cin >> input;
			highest = max(highest, input);
			
			if (no == 1) {
				continue;
			} else {
				if (s.empty()) {
					s.push(input);
				} else if (s.top() == input) {
					s.pop();
				} else if (s.top() < input) {
					no = 1;
				} else {
					s.push(input);
				}
			}
		}
		
		if (s.size() > 1) {
			no = 1;
		} else if (s.size() == 1) {
			if (s.top() != highest) {
				no = 1;
			}
		}
		
		
		if (no == 1) {
			cout << "NO" << endl;
		} else {
			cout << "YES" << endl;
		}
		
		while (!s.empty()) {
			s.pop();
		}
	}
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


