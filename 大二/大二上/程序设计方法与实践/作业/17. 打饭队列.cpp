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
	deque<string> que;
	
	for (int i = 0; i < n; i ++) {
		string input;
		cin >> input;
		
		if (input == "Arrive") {
			string name;
			cin >> name;
			que.push_back(name);
		} else if (input == "Leave") {
			if (!que.empty()) {
				que.pop_front();	
			}
		} else if (input == "QueueHead") {
			if (!que.empty()) {
                cout << que.front() << endl;  
            } else {
                cout << "Empty queue" << endl;  
            }
		} else if (input == "QueueTail") {
			if (!que.empty()) {
                cout << que.back() << endl;  
            } else {
                cout << "Empty queue" << endl;  
            }
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


