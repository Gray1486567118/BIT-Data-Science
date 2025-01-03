#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

int n, k;

ll gcd(ll a, ll b);
void printchar(char c, int n);
bool judge_cut(const vector<int>& ropes, int len, int k);

int main() {
	cin >> n;
	vector<int> rope(n);
	
	for (int i = 0; i < n; i ++) {
		cin >> rope[i];
	}
	
	cin >> k;
	sort(rope.begin(), rope.end());
	
	int left = 1, right = rope[n - 1];
	int result = 0;
	
	while (left <= right) {
		int mid = left + (right - left) / 2;
		
		if (judge_cut(rope, mid, k)) {
			result = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	
	cout <<result << endl;
	return 0;
}


bool judge_cut(const vector<int>& ropes, int len, int k) {
	int count = 0;
	for (int i = 0; i < n; i ++) {
		count += ropes[i] / len;
	}
	
	return count >= k;
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


