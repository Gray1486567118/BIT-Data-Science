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



BiTree* buildTree(vector<char>& inorder, vector<char>& postorder, int inStart, int inEnd, int& postIndex, unordered_map<char, int>& inMap);
void printLevelOrder(BiTree* root);


int main() {
    string in;
    string post;
    cin >> in;
    cin >> post;

    vector<char> inOrder(in.begin(), in.end());
    vector<char> postOrder(post.begin(), post.end());

    unordered_map<char, int> inMap;
    for (int i = 0; i < inOrder.size(); i ++) {
        inMap[inOrder[i]] = i;
    }

    int postIndex = postOrder.size() - 1;
    BiTree* root = buildTree(inOrder, postOrder, 0, inOrder.size() - 1, postIndex, inMap);

    printLevelOrder(root);
    return 0;
}



BiTree* buildTree(vector<char>& inorder, vector<char>& postorder, int inStart, int inEnd, int& postIndex, unordered_map<char, int>& inMap) {
    if (inStart > inEnd) {
        return nullptr;
    }

    char rootVal = postorder[postIndex --];
    BiTree* root = new BiTree(rootVal);

    int inIndex = inMap[rootVal];

    root->rchild = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex, inMap);
    root->lchild = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex, inMap);
    return root;
}


void printLevelOrder(BiTree * root) {
    if (!root) return;

    queue<BiTree*> q;
    q.push(root);

    while (!q.empty()) {
        BiTree* node = q.front();
        q.pop();
        cout << node->data;

        if (node->lchild) q.push(node->lchild);
        if (node->rchild) q.push(node->rchild);
    }
    cout << endl;
} 
