#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

int depth = 0;


typedef struct BSTNode {
    int val;
    BSTNode *left, *right;
} BSTNode, *BSTree;


void insert(BSTree &T, int n);
void printMidSeq(BSTree &T);
void printIndented(BSTree &T, int depth);

int main() {
    int n;
    BSTree tree = NULL;
    while (cin >> n) {
        if (n == 0) break;
        insert(tree, n);
    }

    printIndented(tree, depth);
    cout << endl;
    printMidSeq(tree);
    cout << endl;
    return 0;
}


void insert(BSTree &T, int n) {
    if (T == NULL) {
        T = new BSTNode{n, NULL, NULL};
    } else if (n == T->val) {
        cout << "same elem error" << endl;
        return;
    } else if (n < T->val) {
        insert(T->left, n);
    } else {
        insert(T->right, n);
    }
}


void printIndented(BSTree &T, int depth) {
    if (T == NULL) {
        return;
    }
    printIndented(T->left, depth + 1);
    for (int i = 0; i < depth; i ++) {
        cout << "    ";
    }
    cout << T->val << endl;
    printIndented(T->right, depth + 1);
}

void printMidSeq(BSTree &T) {
    if (T == NULL) {
        return;
    }

    printMidSeq(T->left);
    cout << " " << T->val;
    printMidSeq(T->right);
}
