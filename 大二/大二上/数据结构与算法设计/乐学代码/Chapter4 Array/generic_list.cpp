#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;


struct GListNode {
    bool isAtom;
    char atom;
    GListNode* head;
    GListNode* tail;

    GListNode(char a): isAtom(true), atom(a), head(nullptr), tail(nullptr) {} 
    GListNode(GListNode* h, GListNode* t): isAtom(false), head(h), tail(t) {}
};

GListNode* CreateGList(const string& S, int& pos);
GListNode* GetHead(GListNode* L);
GListNode* GetTail(GListNode* L);
void DestroyGList(GListNode*& L);
void PrintGList(GListNode* L);


int main() {
    string s;
    cin >> s;

    int pos = 0;
    GListNode* L = CreateGList(s, pos);

    cout << "generic list: ";
    PrintGList(L);
    cout << endl;

    int cmd;
    while (!L->isAtom && L->head != nullptr) {
        cin >> cmd;
        if (cmd == 1) {
            GListNode* newL = GetHead(L);
            cout << "destroy tail" << endl << "free list node" << endl;
            if (newL) {
                DestroyGList(L->tail);
                L = newL;
            } else {
                break;
            }
        } else if (cmd == 2) {
            GListNode* newL = GetTail(L);
            cout << "free head node" << endl << "free list node" << endl;
            if (newL) {
                DestroyGList(L->head);
                L = newL;
            } else {
                cout << "generic list: ()" << endl;
                break;
            }
        }

        cout << "generic list: ";
        PrintGList(L);
        cout << endl;
    }
    return 0;
}

GListNode *CreateGList(const string &S, int &pos) {
    if (S[pos] == '(') {
        pos ++;
        GListNode* L = new GListNode(nullptr, nullptr);
        GListNode* curr = L;

        while (S[pos] != ')') {
            GListNode* element = nullptr;
            if (S[pos] == ',') {
                pos ++;
            } else if (isalpha(S[pos])) {
                element = new GListNode(S[pos++]);
            } else if (S[pos] == '(') {
                element = CreateGList(S, pos);
            }

            if (curr->head == nullptr) {
                curr->head = element;
            } else {
                curr->tail = new GListNode(element, nullptr);
                curr = curr->tail;
            }
        } 

        pos ++;
        return L;
    }
    return nullptr;
}


GListNode* GetHead(GListNode *L) {
    return L && !L->isAtom ? L->head : nullptr;
}


GListNode* GetTail(GListNode* L) {
    return L && !L->isAtom ? L->tail : nullptr;
}

void DestroyGList(GListNode*& L) {
    if (L) {
        if (!L->isAtom) {
            DestroyGList(L->head);
            DestroyGList(L->tail);
        }
        delete L;
        L = nullptr;
    }
}

void PrintGList(GListNode* L) {
    if (!L) return;
    if (L->isAtom) {
        cout << L->atom;
    } else {
        cout << "(";
        GListNode* curr = L;
        while (curr) {
            PrintGList(curr->head);
            curr = curr->tail;
            if (curr) {
                cout << ",";
            }
        }
        cout << ")";
    }
}