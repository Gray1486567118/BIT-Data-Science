#include <stdio.h>

int main() {
	int n, score;
	scanf("%d %d", &n, &score);
	
	int have_solution = 0;
	int a, b, c;
	if (n * 12 > score) {
		c = score / 12;
	} else {
		c = n;
	}
	
	while (c >= 0) {		
		for (a = n - c; a >= 0; a --) {
			b = n - c - a;
			if (2.3 * a + 3.4 * b + 12 * c == score) {
				printf("%d %d %d\n", c, b, a);
				have_solution = 1;
			}
		}
		
		c--;
	}
	
	
	
	
	if (have_solution == 0) {
		printf("Error!\n");
	}
	return 0;
}
