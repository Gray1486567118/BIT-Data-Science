#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 2000001;
const int MOD = 10000000;

vector<int> wells(N);
int counter = 0;

void qsort(vector<int>& A, int left, int right);
int p(vector<int>& A, int left, int right);


int main() {
    int x, y;
    wells[0] = 0;

    while (scanf("%d,%d", &x, &y) != EOF) {
        wells[++counter] = y;
    }

    qsort(wells, 1, counter);

    int mid = (1 + counter) / 2;
    cout << wells[mid] << endl;
    return 0;
}


void qsort(vector<int>& A, int left, int right) {
    if (left < right) {
        int pivot = p(A, left, right);
        qsort(A, left, pivot - 1);
        qsort(A, pivot + 1, right);
    }
}


int p(vector<int>& A, int left, int right) {
    int pivot = A[left];
    A[0] = pivot;

    while (left < right) {
        while (left < right && A[right] >= pivot) {
            right --;
        }
        A[left] = A[right];

        while (left < right && A[left] <= pivot) {
            left ++;
        }
        A[right] = A[left];
    }
    A[left] = pivot;
    return left;
}

