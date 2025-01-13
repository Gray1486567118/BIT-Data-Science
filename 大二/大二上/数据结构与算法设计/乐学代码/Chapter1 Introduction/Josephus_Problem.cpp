#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

struct Node {
    int number;
    Node* next;
    Node(int num) : number(num), next(nullptr) {}
};

Node* createCircList(int n);
void solve(int n, int k, int m);

ll gcd(ll a, ll b);
void printchar(char c, int n);

int main() {
    int n, k, m;
    scanf("%d,%d,%d", &n, &k, &m);

    if (n < 1 || m < 1 || k < 1) {
        cout << "n,m,k must bigger than 0." << endl;
    } else if (k > n) {
        cout << "k should not bigger than n." << endl;
    } else {
        solve(n, k, m);
    }

    return 0;
}


Node* createCircList(int n) {
    Node* head = new Node(1);
    Node* prev = head;
    for (int i = 2; i <= n; i ++) {
        Node* node = new Node(i);
        prev->next = node;
        prev = node;
    }

    prev->next = head;
    return head;
}

void solve(int n, int k, int m) {
    Node* head = createCircList(n);

    Node* prev = nullptr;
    Node* curr = head;
    for (int i = 1; i < k; i ++) {
        prev = curr;
        curr = curr->next;
    }

    int printed = 0;
    while (n > 1) {
        for (int i = 1; i < m; i ++) {
            prev = curr;
            curr = curr->next;
        }

        cout << curr->number;
        printed ++;

        if (printed % 10 == 0) {
            cout << endl;
        } else {
            cout << " ";
        }
        

        prev->next = curr->next;
        delete curr;
        curr = prev->next;

        n --;
    }

    cout << curr->number << endl;
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