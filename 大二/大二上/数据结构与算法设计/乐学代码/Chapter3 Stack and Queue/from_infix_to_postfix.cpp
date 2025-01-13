#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;


int prec(char op);
string in_to_post(const string &infix);


int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++) {
        string infix;
        cin >> infix;
        infix.pop_back();

        string postfix = in_to_post(infix);
        cout << postfix << endl;
    }
    return 0;
}


int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; 
    return 0;
}

string in_to_post(const string &infix) {    
    string postfix;
	stack<char> op;
	
    for (char ch : infix) {
        if (ch == '(') {
            // left parenthesis
            op.push(ch);
        } else if (isalpha(ch)) {
            // letter
            postfix += ch;
        } else if (ch == ')') {
            // right parenthesis
            while (op.top() != '(') {
                postfix += op.top();
                op.pop();
            }
            op.pop();
        } else {
            // operator
            while (!op.empty() && ((prec(ch) <= prec(op.top()) && ch != '^') || (prec(ch) < prec(op.top()) && ch == '^'))) {
                postfix += op.top();
                op.pop();
            }

            op.push(ch);
        }
    }

    while (!op.empty()) {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}
