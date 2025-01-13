#include <stdio.h>

void printchar(char c, int n);

int main() {
	int n;
	scanf("%d", &n);
	
	printchar('G', 2 * n - 1);
	printf("\n");
	
	int i;
	for (i = 0; i < n - 2; i ++) {
		printf("G");
		printchar('+', 2 * n - 2);
		printf("\n");
	}
	
	printf("G");
	printchar('+', n - 2);
	printchar('G', n);
	printf("\n");
	
	for (i = 0; i < n - 2; i ++) {
		printf("G");
		printchar('+', 2 * n - 3);
		printf("G");
		printf("\n");
	}
	
	printchar('G', 2 * n - 1);
	printf("\n");
	return 0;
}





void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) printf("%c" ,c);
}
