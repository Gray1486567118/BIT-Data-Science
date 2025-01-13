#include <stdio.h>

double sum(int n);

int main() {
	int n;
	scanf("%d", &n);
	
	printf("%lf\n", sum(n));
	return 0;
}

double sum(int n) {
	if (n == 1) {
		return 1;
	}
	
	return sum(n - 1) + 1.0 / (2 * n - 1);
}
