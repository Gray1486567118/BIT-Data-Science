#include <stdio.h>
#include <math.h>

int main() {
	int n, m, i;
	int sum = 0;
	scanf("%d,%d", &m, &n);
	for (i = m; i <= n; i ++) {
		if (sqrt(i) == (int) sqrt(i)) {
			sum += i;
		}
	}
	
	printf("%d", sum);
	return 0;
}
