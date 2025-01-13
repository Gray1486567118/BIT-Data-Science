#include <stdio.h>

// Merge function to merge two sorted arrays and count inversions
int merge(int arr[], int temp_arr[], int left, int mid, int right) {
    int inv_count = 0;
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp_arr[k++] = arr[i++];
        } else {
            temp_arr[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp_arr[k++] = arr[i++];
    }

    while (j <= right) {
        temp_arr[k++] = arr[j++];
    }

	int loop_var;
    for (loop_var = left; loop_var <= right; loop_var++) {
        arr[loop_var] = temp_arr[loop_var];
    }

    return inv_count;
}

// Merge sort function to count inversions
int merge_sort(int arr[], int temp_arr[], int left, int right) {
    int inv_count = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        inv_count += merge_sort(arr, temp_arr, left, mid);
        inv_count += merge_sort(arr, temp_arr, mid + 1, right);
        inv_count += merge(arr, temp_arr, left, mid, right);
    }
    return inv_count;
}

// Function to calculate minimum swaps needed to revert to original order
int minimum_swaps(int n, int m, int swaps[][2]) {
    int arr[n];
    int temp_arr[n];

    // Initialize array with natural numbers
    int i;
	for (i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Apply swaps
    for (i = 0; i < m; i++) {
        int swap1 = swaps[i][0] - 1;
        int swap2 = swaps[i][1] - 1;
        int temp = arr[swap1];
        arr[swap1] = arr[swap2];
        arr[swap2] = temp;
    }

    // Calculate minimum swaps needed to revert to original order
    int min_swaps = merge_sort(arr, temp_arr, 0, n - 1);

    return min_swaps;
}

int main() {
    int n, m, i;
    scanf("%d %d", &n, &m);

    int swaps[m][2];
    for (i = 0; i < m; i++) {
        scanf("%d %d", &swaps[i][0], &swaps[i][1]);
    }

    // Output
    printf("%d\n", minimum_swaps(n, m, swaps));

    return 0;
}

