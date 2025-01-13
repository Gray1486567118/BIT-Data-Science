#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;

void heapSort(vector<int>& A, int len);
void buildHeap(vector<int>& A, int len);
void headAdjust(vector<int>& A, int k, int len);
void printHeap(vector<int>& A, int len);

int main() {
    int n;
    cin >> n;

    vector<int> A(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> A[i];
    }

    heapSort(A, n);
    return 0;
}



void heapSort(vector<int>& A, int len) {
    buildHeap(A, len);
    printHeap(A, len);
    for (int i = len; i > 1; i --) {
        swap(A[1], A[i]);
        headAdjust(A, 1, i - 1);
        if (i == len) {
            printHeap(A, len - 1);
        } else if (i == len - 1) {
            printHeap(A, len - 2);
        }
    }
}


void buildHeap(vector<int>& A, int len) {
    for (int i = len / 2; i >= 1; i --) {
        headAdjust(A, i, len);
    }
}


void headAdjust(vector<int>& A, int k, int len) {
    // max heap
    A[0] = A[k];  // A[0] restores A[k] temporarily
    for (int i = 2 * k; i <= len; i *= 2) {
        if (i + 1 <= len && A[i] < A[i + 1]) {
            i ++;
        }
        if (A[0] >= A[i]) {
            break;
        } else {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}


void printHeap(vector<int>& A, int len) {
    for (int i = 1; i <= len; i ++) {
        cout << A[i] << " ";
    }
    cout << endl;
}