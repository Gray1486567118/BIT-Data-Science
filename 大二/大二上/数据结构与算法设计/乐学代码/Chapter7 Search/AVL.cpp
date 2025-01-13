#include <bits/stdc++.h>
using namespace std;

typedef struct AVLNode {
    char val;
    int height;
    AVLNode *left, *right;
} AVLNode, *AVLTree;

AVLTree insert(AVLTree &T, char val);
AVLTree rotateLeft(AVLTree &T);
AVLTree rotateRight(AVLTree &T);
int getHeight(AVLTree &T);
void updateHeight(AVLTree &T);
void preOrder(AVLTree &T);
void inOrder(AVLTree &T);
void postOrder(AVLTree &T);
void printIndented(AVLTree &T, int depth);



int main() {
    string s;
    cin >> s;

    AVLTree tree = NULL;

    for (char c : s) {
        tree = insert(tree, c);
    }

    cout << "Preorder: ";
    preOrder(tree);
    cout << endl;

    cout << "Inorder: ";
    inOrder(tree);
    cout << endl;

    cout << "Postorder: ";
    postOrder(tree);
    cout << endl;

    cout << "Tree:" << endl;
    printIndented(tree, 0);

    return 0;
}



int getHeight(AVLTree &T) {
    return T ? T->height : 0;
}


void updateHeight(AVLTree &T) {
    if (T) {
        T->height = max(getHeight(T->left), getHeight(T->right)) + 1;
    }
}

AVLTree insert(AVLTree &T, char val) {
    if (!T) {
        T = new AVLNode{val, 1 , NULL, NULL};
        return T;
    } 

    if (val > T->val) {
        T->right = insert(T->right, val);
    } else if (val < T->val) {
        T->left = insert(T->left, val);
    } else {
        return T;
    }

    updateHeight(T);

    int balance = getHeight(T->left) - getHeight(T->right);

    // LL
    if (balance > 1 && val < T->left->val) {
        return rotateRight(T);
    } 

    // RR
    if (balance < -1 && val > T->right->val) {
        return rotateLeft(T);
    } 
    
    // LR
    if (balance > 1 && val > T->left->val) {
        T->left = rotateLeft(T->left);
        return rotateRight(T);
    } 

    // RL
    if (balance < -1 && val < T->right->val) {
        T->right = rotateRight(T->right);
        return rotateLeft(T);
    } 

    return T;
}


AVLTree rotateLeft(AVLTree &T) {
    AVLTree newRoot = T->right;
    T->right = newRoot->left;
    newRoot->left = T;
    updateHeight(T);
    updateHeight(newRoot);
    return newRoot;
}


AVLTree rotateRight(AVLTree &T) {
    AVLTree newRoot = T->left;
    T->left = newRoot->right;
    newRoot->right = T;
    updateHeight(T);
    updateHeight(newRoot);
    return newRoot;
}


void preOrder(AVLTree &T) {
    if (T) {
        cout << T->val;
        preOrder(T->left);
        preOrder(T->right);
    }
}

void inOrder(AVLTree &T){
    if (T) {
        inOrder(T->left);
        cout << T->val;
        inOrder(T->right);
    }
}

void postOrder(AVLTree &T) {
    if (T) {
        postOrder(T->left);
        postOrder(T->right);
        cout << T->val;
    }
}


void printIndented(AVLTree &T, int depth) {
    if (T) {
        printIndented(T->right, depth + 1);
        for (int i = 0; i < depth; i ++) {
            cout << "    ";
        }
        cout << T->val << endl;
        printIndented(T->left, depth + 1);
    }
}