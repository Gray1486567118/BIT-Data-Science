#include <stdio.h>

int f(int n, int m);

int main() {
	int n, m;
	scanf("%d,%d", &n, &m);
	
	printf("%d\n", f(n, m));
	return 0;
}

int f(int n, int m) {
	if (n > 5 && m >= 0) {
		return 1;
	} else if (m < 0) {
		return 2;
	} 
	
	return f(n + 1, m) + f(n , m - 1);
}
