#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;



struct Triple
{
    int row, col, value;
};


void multiply(int r1, int c1, int nz1, vector<Triple> &mat1, int r2, int c2, int nz2, vector<Triple> &mat2);

int main() {
    // input matrix1
    int r1, c1, nz1;
    cin >> r1 >> c1 >> nz1;
    vector<Triple> mat1(nz1);
    for (int i = 0; i < nz1; i ++) {
        cin >> mat1[i].row >> mat1[i].col >> mat1[i].value;
    }

    // input matrix2
    int r2, c2, nz2;
    cin >> r2 >> c2 >> nz2;
    vector<Triple> mat2(nz2);
    for (int i = 0; i < nz2; i ++) {
        cin >> mat2[i].row >> mat2[i].col >> mat2[i].value;
    }


    multiply(r1, c1, nz1, mat1, r2, c2, nz2, mat2);
    return 0;
}


void multiply(int r1, int c1, int nz1, vector<Triple> &mat1, int r2, int c2, int nz2, vector<Triple> &mat2) {
    map<pair<int, int>, int> result;

    for (const auto &elem1 : mat1) {
        for (const auto &elem2 : mat2) {
            if (elem1.col == elem2.row) {
                result[{elem1.row, elem2.col}] += elem1.value * elem2.value;
            }
        }
    }

    cout << r1 << endl << c2 << endl;

    int nonZeroCount = 0;
    for (const auto &elem : result) {
        if (elem.second != 0) {
            nonZeroCount++;
        }
    }
    cout << nonZeroCount << endl;

    for (const auto &elem : result) {
        if (elem.second != 0) {
            cout << elem.first.first << "," << elem.first.second << "," << elem.second << endl;
        }
    }
}