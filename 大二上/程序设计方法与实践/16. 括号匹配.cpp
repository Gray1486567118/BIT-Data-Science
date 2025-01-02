#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

ll gcd(ll a, ll b);
void printchar(char c, int n);
pair<int, int>  seq_process(const string& s); 

int main() {
	int n;
	cin >> n;
	
	unordered_map<int ,int> remain_left;
	unordered_map<int ,int> remain_right;
	int pairs = 0;
	int paired = 0;
	
	for (int i = 0; i < n; i ++) {
		string s;
		cin >> s;
		
		pair<int, int> result = seq_process(s);
		int left = result.first;
		int right = result.second;
		
		if (left == 0 && right == 0) {
			paired ++;
			continue;
		} else if (left == 0) {
			remain_right[right] ++;
		} else if (right == 0) {
			remain_left[left] ++;
		}
	} 
	
	for (auto it = remain_left.begin(); it != remain_left.end(); it ++) {
		int left = it->first;
		int count = it->second;
		
		if (remain_right.find(left) != remain_right.end()) {
			pairs += min(count, remain_right[left]);
		}
	}
	
	pairs += (paired / 2);
	cout << pairs <<endl;
	return 0;
}


pair<int, int>  seq_process(const string& s) {
	int left = 0, right = 0;
	
	for (int i = 0; i < s.size(); i ++) {
		if (s[i] == '('){
			left ++;
		} else {
			if (left > 0) {
				left --;
			} else {
				right ++;
			}
		}
	}
	
	return make_pair(left, right);
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


