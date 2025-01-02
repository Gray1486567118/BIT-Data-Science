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
	cin >> n;
	
	int total = 0;
	priority_queue<int, vector<int>, greater<int> > pq;
	
	for (int i = 0; i < n; i ++) {
		int input;
		cin >> input;
		pq.push(input);
	}
	
	while (pq.size() > 1) {
		int first = pq.top();
		pq.pop();
		int second = pq.top();
		pq.pop();
		
		int brawn = first + second;
		pq.push(brawn);
		
		total += brawn;
	}
	
	cout << total << endl;
	
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


