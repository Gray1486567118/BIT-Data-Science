#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define ll long long
#define ull unsigned long long

int max (int a, int b) {
	return a > b ? a : b;
}


int main() {
	int t, n, i, j;
	scanf("%d", &t);
	
	for (i = 0; i < t; i ++) {
		scanf("%d", &n);
		int a[n];
		for (j = 0; j < n; j ++) {
			scanf("%d", &a[j]);
		}
		
		ll water = 0;
		int left = 0, right = n - 1;
		int left_max = 0, right_max = 0;
		
		while (left < right) {
			left_max = max(left_max, a[left]);
			right_max = max(right_max, a[right]);
			
			if (left_max < right_max) {
				water += left_max - a[left];
				left ++;
			} else {
				water += right_max - a[right];
				right --;
			}
		}
		
		printf("%lld\n", water);
	}
	
	return 0;
}

