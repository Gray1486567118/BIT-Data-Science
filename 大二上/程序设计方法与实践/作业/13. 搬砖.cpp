#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

ll gcd(ll a, ll b);
void printchar(char c, int n);
ll merge_parting(vector<int>& a, int left, int right);
ll merge_count(vector<int>& a, int left, int mid, int right);

int main() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; i ++) {
		cin >> a[i];
	}
	
	ll ans = merge_parting(a, 0, n - 1);
	
	cout << ans << endl;
	return 0;
}


ll merge_parting(vector<int>& a, int left, int right) {
	ll count = 0;
	if (left < right) {
		int mid = left + (right - left) / 2;
		
		count += merge_parting(a, left, mid);
		count += merge_parting(a, mid + 1, right);
		count += merge_count(a, left, mid, right);
	}
	
	return count;
}


ll merge_count(vector<int>& a, int left, int mid, int right) {
	ll count = 0;
	
	vector<int> left_half(a.begin() + left, a.begin() + mid + 1);
	vector<int> right_half(a.begin() + mid + 1, a.begin() + right + 1);
	
	int i = 0, j = 0, k = left;
	
	while (i < left_half.size() && j < right_half.size()) {
		if (left_half[i] <= right_half[j]) {
			a[k] = left_half[i];
			k ++;
			i ++;
		} else {
			a[k] = right_half[j];
			k ++;
			j ++;
			count += (left_half.size() - i);
		}
	}
	
	while (i < left_half.size()) {
		a[k] = left_half[i];
		k ++;
		i ++;
	}
	
	while (j < right_half.size()) {
        a[k] = right_half[j];
        k ++; 
		j ++;
    }
    return count;
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


