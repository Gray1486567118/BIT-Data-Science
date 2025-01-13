#include <stdio.h>

int main() {
	long long n, x1, r1, x2, r2, i, j;
	scanf("%lld %lld %lld %lld %lld", &n, &x1, &r1, &x2, &r2);
	
	// (j, i)
	for (i = n; i >= -n; i --) {
		for (j = -n; j <= n ; j ++) {
			long long d1 = (j - x1) * (j - x1) + i * i;
			long long d2 = (j - x2) * (j - x2) + i * i;
			if (d1 <= r1 * r1 && d2 >= r2 * r2) {
				printf("*");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
	return 0;
}
