#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 100001;
const int MOD = 10000000;



int cutoff = 5;
int counter = 0;  // num of numbers
vector<int> arr;
vector<int> median;

void QSort(vector<int>& A, int low, int high);
int partition(vector<int>& A, int low, int high);
void median3(vector<int>& A, int low, int high);
void swap(vector<int>& A, int i1, int i2);
void InsertSort(vector<int>& A, int low, int high);


int main() {
    // init arr[0] = 0 to restore pivot
    arr.push_back(0);
    // input
    string input;

    while (true) {
        cin >> input;
        if (input == "#") {
            break;
        }

        arr.push_back(stoi(input));
        counter ++;
    }


    // QSort
    QSort(arr, 1, counter);

    // output
    cout << "After Sorting:" << endl;
    for (int i = 1; i <= counter; i ++) {
        cout << arr[i] << " ";
    }
    if (counter != 0) {
        cout << endl;
    }

    cout << "Median3 Value:" << endl;
    if (counter <= cutoff) {
        cout << "none" << endl;
    } else {
        for (int i = 0; i < median.size(); i ++) {
            cout << median[i] << " ";
        }
        cout << endl;
    }
    return 0;
}



void QSort(vector<int>& A, int low, int high) {
    int pivot;

    if (high - low >= cutoff) {
        pivot = partition(A, low, high);
        QSort(A, low, pivot - 1);
        QSort(A, pivot + 1, high);
    } else {
        // InsertSort
        InsertSort(A, low, high);
    }
}


int partition(vector<int>& A, int low, int high) {
    if (low < high) {
        median3(A, low, high);
        int pivotkey = A[low];
        int i = low, j = high;

        do {
            while (i < j && pivotkey < A[j]) j --;
            if (i < j) {
                A[i ++] = A[j];
            }

            while (i < j && pivotkey > A[i]) i ++;
            if (i < j) {
                A[j --] = A[i];
            }
        } while (i < j);
        A[i] = pivotkey;
        return i;
    }
    return low;
    
//     A[0] = pivotkey;

//     while (low < high) {
//         while (low < high && A[high] >= pivotkey) {
//             high --;
//         }
//         A[low] = A[high];

//         while (low < high && A[low] <= pivotkey) {
//             low ++;
//         }
//         A[high] = A[low];
//     } 

//     A[low] = pivotkey;
//     return low;
}


void median3(vector<int>& A, int low, int high) {
    int mid = (high + low) / 2;
    int smallest, smaller;

    if (A[low] < A[mid]) {
        smallest = low;
        smaller = mid;
    } else {
        smallest = mid;
        smaller = low;
    }

    if (A[high] < A[smallest]) {
        smaller = smallest;
    } else if (A[high] < A[smaller]) {
        smaller = high;
    }

    swap(A, low, smaller);
    median.push_back(A[low]);
}


void swap(vector<int>& A, int i1, int i2) {
    int temp = A[i1];
    A[i1] = A[i2];
    A[i2] = temp;
}

void InsertSort(vector<int>& A, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= low && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}