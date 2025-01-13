#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;



set<char> operators = {'+', '-', '*', '/', '%', '^'};

bool valid_bracket(string &infix);
bool valid_expression(string &infix);
int prec(char op);
queue<string> in_to_post(const string &infix);
int eval(queue<string> postfix, ll &result);



int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++) {
        string infix;
        cin >> infix;
        
        // 括号是否匹配
        if (!valid_bracket(infix) || !valid_expression(infix)) {
            cout << "error." << endl;
            continue;
        }

        queue<string> postfix = in_to_post(infix);
        ll result;

        if (eval(postfix, result) == 0) {
            cout << "error." << endl;
        } else if (eval(postfix, result) == -1) {
            cout << "Divide 0." << endl;
        } else {
            cout << result << endl;
        }

        // while (!postfix.empty()) {
        //     cout << postfix.front() << " ";
        //     postfix.pop();
        // }
        // cout << endl;
    }
    return 0;
}



bool valid_expression(string &infix) {
    if (infix.empty())  return false;

    if ((operators.count(infix[0]) && infix[0] != '-') 
        || operators.count(infix.back())) {
        return false;
    }

    for (int i = 0; i < infix.size(); ++i) {
        char ch = infix[i];

        if (ch == '(') {
            char next = infix[i + 1];
            if ((operators.count(next) && next != '-') || next == ')') {
                return false;
            }
        }
    }

    return true;
}

bool valid_bracket(string &infix) {
    stack<char> bracket;
    for (char c : infix) {
        if (c == '(') {
            bracket.push(c);
        } else if (c ==')') {
            if (bracket.empty()) {
                return false;
            } else {
                bracket.pop();
            }
        }
    }

    if (bracket.empty())  return true;
    return false;
}

int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3; 
    return 0;
}

queue<string> in_to_post(const string &infix) {    
    queue<string> postfix;
	stack<char> op;

    int i = 0;

    while (i < infix.size()) {
        char ch = infix[i];

        if (ch == '(') {
            op.push(ch);
            i++;
        } else if (ch == ')') {
            while (!op.empty() && op.top() != '(') {
                postfix.push(string(1, op.top()));
                op.pop();
            }
            if (!op.empty()) op.pop();
            i++;
        } else if (isdigit(ch) || (ch == '-' && (i == 0 || infix[i - 1] == '(' || operators.count(infix[i - 1])))) {
            // 处理正负数（负号作为运算符时与数字绑定）
            string num;
            if (ch == '-') {
                num += ch;
                i++;
            }
            while (i < infix.size() && isdigit(infix[i])) {
                num += infix[i];
                i++;
            }
            postfix.push(num);
        } else if (operators.count(ch)) {
            while (!op.empty() && ((prec(ch) <= prec(op.top()) && ch != '^') || (prec(ch) < prec(op.top()) && ch == '^'))) {
                postfix.push(string(1, op.top()));
                op.pop();
            }
            op.push(ch);
            i++;
        } else {
            // 无效字符
            i++;
        }
    }

    while (!op.empty()) {
        postfix.push(string(1, op.top()));
        op.pop();
    }

    return postfix;
}

int eval(queue<string> postfix, ll &result) {
    stack<ll> s;

    while (!postfix.empty()) {
        string token = postfix.front();
        postfix.pop();

        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            s.push(stoll(token));
        } else if (operators.count(token[0])) {
            if (s.size() < 2)  return 0;

            ll b = s.top();
            s.pop();
            ll a = s.top();
            s.pop();
            ll answer = 0;

            switch (token[0]) {
                case '+': 
                    answer = a + b; break;
                case '-': 
                    answer = a - b; break;
                case '*': 
                    answer = a * b; break;
                case '/': 
                    if (b == 0)  return -1;
                    answer = a / b;
                    break;
                case '%':
                    if (b == 0)  return -1;
                    answer = a % b;
                    break;
                case '^':
                    if (b < 0) {
                        return 0;
                    }
                    answer = pow(a, b);
                    break;
                default: 
                    return 0;
            }

            s.push(answer);
        } else {
            return 0;
        }
    }

    if (s.size() != 1)  return 0;
    result = s.top();
    return 1;
}