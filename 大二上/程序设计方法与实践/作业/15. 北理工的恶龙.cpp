#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;

struct Dragon {
	int difficulty;
	int exp;
};

ll gcd(ll a, ll b);
void printchar(char c, int n);
bool cmp_positive(Dragon a, Dragon b);
bool cmp_negative(Dragon a, Dragon b);

int main() {
	int n;
	cin >> n;
	
	vector<Dragon> dragons_positive;
	vector<Dragon> dragons_negative;
	for (int i = 0; i < n; i ++) {
		int d, e;
		cin >> d >> e;
		
		Dragon dragon;
		dragon.difficulty = d;
		dragon.exp = e;
		
		if (e >= 0) {
			dragons_positive.push_back(dragon);
		} else {
			dragons_negative.push_back(dragon);
		}
	}
	
	sort(dragons_positive.begin(), dragons_positive.end(), cmp_positive);
	sort(dragons_negative.begin(), dragons_negative.end(), cmp_negative);
	
	ll A = 0;
	ll payment = 0;
	
	for (int i = 0; i < dragons_positive.size(); i ++) {
		if (A < dragons_positive[i].difficulty) {
			payment += dragons_positive[i].difficulty - A;
			A = dragons_positive[i].difficulty;
		}
		
		A += dragons_positive[i].exp;
	}
	
	for (int i = 0; i < dragons_negative.size(); i ++) {
		if (A < dragons_negative[i].difficulty) {
			payment += dragons_negative[i].difficulty - A;
			A = dragons_negative[i].difficulty;
		}
		
		A += dragons_negative[i].exp;
	}
	
	cout << payment << endl; 
	return 0;
}


bool cmp_positive(Dragon a, Dragon b) {
	return a.difficulty < b.difficulty;
}

bool cmp_negative(Dragon a, Dragon b) {
	return (a.exp + a.difficulty) > (b.difficulty + b.exp);
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


