#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;


stack<int> s;
int count_colors[1000010];
int result = 0;

ll gcd(ll a, ll b);
void printchar(char c, int n);
void visible(int n, const vector<int>& color, const vector<int>& height);

int main() {
	int m;
	scanf("%d", &m);
	
	for (int i = 0; i < m; i ++) {
		int n;
		scanf("%d", &n);
		
		vector<int> color(n), height(n);
        for (int j = 0; j < n; j ++) {
            scanf("%d", &color[j]);
        }
        for (int j = 0; j < n; j ++) {
            scanf("%d", &height[j]);
        }
        
        visible(n, color, height);
        result = 0;
	}
	return 0;
}

void visible(int n, const vector<int>& color, const vector<int>& height) {
	memset(count_colors, 0, sizeof(count_colors));
	
	for (int i = 0; i < n; i ++) {
		while (!s.empty() && height[s.top()] <= height[i]) {
			int popped = s.top();
			s.pop();
			
			count_colors[color[popped]] --;
			if (count_colors[color[popped]] == 0) {
				result --;
			}
		}
		
		s.push(i);
		count_colors[color[i]] ++;
		if (count_colors[color[i]] == 1) {
			result ++;
		}
		
		if (i != n - 1) {
			printf("%d ", result);
		} else {
			printf("%d\n", result);
		}
	}
	
	while (!s.empty()) {
		s.pop();
	}
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


