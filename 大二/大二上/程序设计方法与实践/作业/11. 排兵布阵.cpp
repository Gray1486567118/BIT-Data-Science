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
	// input
	int n;
	cin >> n;
	
	vector<ll> x(n), y(n), x_i(n);
	
	for (int i = 0; i < n; i ++) {
		cin >> x[i] >> y[i];
	}
	
	// cal
	ll total = 0;
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	ll mid_y = y[n / 2];
	
	// y
	for (int i = 0; i < n; i ++) {
		total += abs(y[i] - mid_y);
	}
	
	// x
	for (int i = 0; i < n; i ++) {
		x_i[i] = x[i] - i;
	}
	
	sort(x_i.begin(), x_i.end());
	ll mid_x_i = x_i[n / 2];
	
	for (int i = 0; i < n; i ++) {
		total += abs(x_i[i] - mid_x_i);
	}
	
	printf("%lld\n", total); 
	
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

