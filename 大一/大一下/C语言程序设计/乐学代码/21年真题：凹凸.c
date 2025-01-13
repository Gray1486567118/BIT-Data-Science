#include <stdio.h>

void printchar(char c, int n);

int main() {
	int n, i;
	scanf("%d", &n);
	
	if (n % 2 == 0) {
		printchar('*', n / 2);
		printchar(' ', n / 2 - 1);
		printchar('*', n / 2);
		printf("\n");
		
		for (i = 0; i < n / 3; i ++) {
			printf("*");
			printchar(' ', n / 2 - 2);
			printf("*");
			printchar(' ', n / 2 - 1);
			printf("*");
			printchar(' ', n / 2 - 2);
			printf("*");
			printf("\n");
		}
		
		printf("*");
		printchar(' ', n / 2 - 2);
		printchar('*', n / 2 + 1);
		printchar(' ', n / 2 - 2);
		printf("*");
		printf("\n");
		
		for (i = 0; i < n / 2 - 1; i ++) {
			printf("*");
			printchar(' ', n / 2 * 3 - 3);
			printf("*");
			printf("\n");
		}
		
		printchar('*', n / 2 * 3 - 1);
		printf("\n");
	} else {
		printchar(' ', n / 2 - 1);
		printchar('*', n / 2 + 2);
		printf("\n");
		
		for (i = 0; i < n / 3; i ++) {
			printchar(' ', n / 2 - 1);
			printf("*");
			printchar(' ', n / 2);
			printf("*");
			printf("\n");
		}
		
		printchar('*', n / 2);
		printchar(' ', n / 2);
		printchar('*', n / 2);
		printf("\n");
		
		for (i = 0; i < n / 2 - 1; i ++) {
			printf("*");
			printchar(' ', n / 2 * 3 - 2);
			printf("*");
			printf("\n");
		}
		
		printchar('*', n / 2 * 3);
		printf("\n");
	}
	return 0;
} 




void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++)  printf("%c" ,c);
}
