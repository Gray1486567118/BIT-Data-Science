#include <stdio.h>

void printchar(char c, int n);

int main() {
	int h, w, i;
	scanf("%d %d", &h, &w);
	
	for (i = 1; i <= h; i ++) {
		printchar(' ', i - 1);
		
		if (2 * w < 2 * h - 1 - 2 * (i - 1)) {
			printchar('*', w);
			printchar(' ', 2 * h - 1 - 2 * (i - 1) - 2 * w);
			printchar('*', w);
		} else {
			printchar('*', 2 * h - 1 - 2 * (i - 1));
		}
		
		printf("\n");
	}
	
	
	
	
	return 0;
}

void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		printf("%c", c);
	}
}
