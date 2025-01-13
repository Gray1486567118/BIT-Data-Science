#include <stdio.h>

void printchar(char c, int n);


int main() {
	int n, i;
	char start;
	scanf("%d %c", &n, &start);
	
	if (start < 'A' || (start > 'Z' && start < 'a') || start >'z') {
		printf("Input error!\n");
		return 0;
	} else if (start >= 'a' && start <= 'z') {
		start -= 'a' - 'A';
	}
	
	// 1st line
	for (i = 0; i < n - 1; i ++) {
		printf("%c ", start + i <= 90 ? start + i : start + i - 26);
	}
	printf("%c\n", start + i <= 90 ? start + i : start + i - 26);
	
	// mid
	int left = start + 1;
	int right = start + n;
	for (i = 0; i < n - 2; i ++) {
		if (left > 90) left -= 26; 
		if (right > 90) right -= 26;
		
		printf("%c", left);
		printchar(' ', 2 * n - 3);
		printf("%c", right);
		printf("\n");
		
		left ++; 
		right ++;
	}
	
	// last
	if (n > 1){
		for (i = 0; i < n - 1; i ++) {
			printf("%c ", left + i <= 90 ? left + i : left + i - 26);
		}
		printf("%c\n", left + i <= 90 ? left + i : left + i - 26);	
	}
	
	return 0;
}


void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++)   printf("%c", c);
}
