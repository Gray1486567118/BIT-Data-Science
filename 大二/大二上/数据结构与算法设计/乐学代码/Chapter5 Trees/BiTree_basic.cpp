#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

struct BiTree {
    char data;
    BiTree *lchild, *rchild;
    BiTree(char value): data(value), lchild(nullptr), rchild(nullptr) {} 
};


BiTree* createTree(string& preOrder, int& index);
void printIndented(BiTree* root, int depth = 0);
void preSeq(BiTree* root);
void midSeq(BiTree* root);
void postSeq(BiTree* root);
int countLeaf(BiTree* root);
void swapBiTree(BiTree* root);


int main() {
    string preOrder;
    cin >> preOrder;
    int index = 0;
    BiTree* root = createTree(preOrder, index);

    cout << "BiTree" << endl;
    printIndented(root);

    cout << "pre_sequence  : ";
    preSeq(root);
    cout << endl;

    cout << "in_sequence   : ";
    midSeq(root);
    cout << endl;

    cout << "post_sequence : ";
    postSeq(root);
    cout << endl;

    cout << "Number of leaf: " << countLeaf(root) << endl;

    swapBiTree(root);
    cout << "BiTree swapped" << endl;
    printIndented(root);

    cout << "pre_sequence  : ";
    preSeq(root);
    cout << endl;

    cout << "in_sequence   : ";
    midSeq(root);
    cout << endl;

    cout << "post_sequence : ";
    postSeq(root);
    cout << endl;
    return 0;
}



BiTree* createTree(string& preOrder, int& index) {
    if (index >= preOrder.size() || preOrder[index] == '#') {
        index ++;
        return nullptr;
    }
    BiTree* root = new BiTree(preOrder[index ++]);
    root->lchild = createTree(preOrder, index);
    root->rchild = createTree(preOrder, index);
    return root;
}


void printIndented(BiTree* root, int depth) {
    if (root) {
        for (int i = 0; i < depth; i ++) {
            cout << "    ";
        }
        cout << root->data << endl;
        printIndented(root->lchild, depth + 1);
        printIndented(root->rchild, depth + 1);
    }
}

void preSeq(BiTree* root) {
    if (root) {
        cout << root->data;
        preSeq(root->lchild);
        preSeq(root->rchild);
    }
}

void midSeq(BiTree* root) {
    if (root) {
        midSeq(root->lchild);
        cout << root->data;
        midSeq(root->rchild);
    }
}

void postSeq(BiTree* root) {
    if (root) {
        postSeq(root->lchild);
        postSeq(root->rchild);
        cout << root->data;
    }
}

int countLeaf(BiTree* root) {
    if (!root) {
        return 0;
    }
    if (!root->lchild && !root->rchild) {
        return 1;
    }
    return countLeaf(root->lchild) + countLeaf(root->rchild);
}

void swapBiTree(BiTree* root) {
    if (root) {
        swap(root->lchild, root->rchild);
        swapBiTree(root->lchild);
        swapBiTree(root->rchild);
    }
}