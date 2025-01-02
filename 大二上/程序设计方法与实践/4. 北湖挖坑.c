#include <stdio.h>
#define ll long long

int main() {
	// input
	int n, h, i, j;
	scanf("%d %d", &n, &h);
	
	int lake[n];
	for (i = 0; i < n; i ++) {
		scanf("%d", &lake[i]);
	}
	
	
	// process
	ll day = h - lake[0];
	for (i = 0; i < n - 1; i ++) {
		int diff = lake[i] - lake[i + 1];
		
		if (diff > 0) {
			day += diff;
		}
	}
	
	printf("%lld\n", day);
	
	return 0;
}
