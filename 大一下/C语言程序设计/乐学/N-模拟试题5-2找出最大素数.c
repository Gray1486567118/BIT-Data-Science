#include <stdio.h>
#include <math.h>

int isPrime(int n);

int main() {
	int n, i;
	scanf("%d", &n);
	
	for (i = n; i > 1; i --) {
		if (isPrime(i)) {
			printf("The max prime number is %d.\n", i);
			break;
		}
	}
	
	return 0;
}


int isPrime(int n) {
	int i;
	for (i = 2; i <= sqrt(n); i ++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}
