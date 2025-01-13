#include <bits/stdc++.h>
using namespace std;
const int N = 1000001;

vector<int> T(N);

int findLeftA(const vector<int>& T, int low, int high);
int findLeftD(const vector<int>& T, int low, int high);
int findRightA(const vector<int>& T, int low, int high);
int findRightD(const vector<int>& T, int low, int high);

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++) {
        cin >> T[i];
    }

    bool isAscending = T[0] < T[n - 1];


    int left, right;
    if (isAscending) {
        left = findLeftA(T, 0, n - 1);
        if (left != -1) {
            right = findRightA(T, left, n - 1);
        }
    } else {
        left = findLeftD(T, 0, n - 1);
        if (left != -1) {
            right = findRightD(T, left, n - 1);
        }
    }

    if (left == -1) {
        cout << "No ";
    } else {
        for (int i = left; i <= right; i++) {
            cout << i << " ";
        }
    }

    cout << endl;
    return 0;
}



int findLeftA(const vector<int>& T, int low, int high) {
    int left = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (T[mid] > mid) {
            high = mid - 1;
        } else if (T[mid] < mid) {
            low = mid + 1;
        } else {
            left = mid;
            high = mid - 1;
        }
    }

    return left;
}


int findLeftD(const vector<int>& T, int low, int high) {
    int left = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (T[mid] > mid) {
            low = mid + 1;
        } else if (T[mid] < mid) {
            high = mid - 1;
        } else {
            left = mid;
            high = mid - 1;
        }
    }

    return left;
}

int findRightA(const vector<int>& T, int low, int high) {
    int right = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (T[mid] > mid) {
            high = mid - 1;
        } else if (T[mid] < mid) {
            low = mid + 1;
        } else {
            right = mid;
            low = mid + 1;
        }
    }

    return right;
}


int findRightD(const vector<int>& T, int low, int high) {
    int right = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (T[mid] > mid) {
            low = mid + 1;
        } else if (T[mid] < mid) {
            high = mid - 1;
        } else {
            right = mid;
            low = mid + 1;
        }
    }

    return right;    
}