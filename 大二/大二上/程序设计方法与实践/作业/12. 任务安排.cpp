#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

struct task {
	int start;
	int end;
};

ll gcd(ll a, ll b);
void printchar(char c, int n);
bool cmp (task a, task b); 


int main() {
	// input
	int n;
	cin >> n;
	
	struct task t[n];
	for (int i = 0; i < n; i ++) {
		cin >> t[i].start >> t[i].end;
	}
	
	sort(t, t + n, cmp);
	
	int count = 1;
	int time_now = t[0].end;
	
	for (int i = 1; i < n; i ++) {
		if (t[i].start >= time_now) {
			time_now = t[i].end;
			count ++;
		}
	}
	
	cout << count << endl;
	return 0;
}


bool cmp (task a, task b) {
	return a.end < b.end;
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


