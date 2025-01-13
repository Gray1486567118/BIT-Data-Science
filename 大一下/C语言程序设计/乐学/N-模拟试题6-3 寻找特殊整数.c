#include <stdio.h>
#include <math.h>

int main() {
	int n, i;
	scanf("%d", &n);
	
	int have_output = 0;
	
	for (i = pow(10, n - 1); i < pow(10, n); i ++) {
		int sum = 0, num = i;
		while (num > 0) {
			sum += pow(num % 10, n);
			num /= 10;
		}
		if (i == sum) {
			printf("%d\n", i);
			have_output = 1;
		}
	}
	
	if (have_output == 0) {
		printf("No output.\n");
	}
	return 0;
}
