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
		for (int i = 0; i < n; i ++) {
			int input;
			cin >> input;
			
			if (!s.empty()) {
				int top = s.top();
				if (abs(top - input) % 2 == 0) {
					s.pop();
				} else {
					s.push(input);
				}
			} else {
				s.push(input);
			}
		} 
		
		if (s.size() == 0 || s.size() == 1) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
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


