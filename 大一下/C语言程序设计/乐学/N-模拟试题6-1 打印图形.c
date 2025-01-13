#include <stdio.h>
#include <string.h>

int main() {
	int n, m, i, j, printed;
	char s[10000];
	scanf("%d%d%s", &n, &m, &s);
	
	int len = strlen(s);
	int lines = len * m / n;
	if (len * m % n != 0) lines ++; 
	printed = 0;
	for (i = 1; i <= lines; i ++) {
		printf("%3d:", i);
		for (j = 0; j < n && printed < len * m; j ++, printed ++) {
			printf("%c", s[printed % len]);
		}
		printf("\n");
	}
	return 0;
}
