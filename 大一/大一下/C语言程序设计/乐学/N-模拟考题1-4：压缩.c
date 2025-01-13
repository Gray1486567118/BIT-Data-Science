#include <stdio.h>

int main() {
	int len, i, j, p, remove;
	scanf("%d", &len);
	char s[len];
	scanf("%s", s);
	
	for (i = 0; i < len; i ++) {
		p = i + 1;
		while (s[p] == s[i])  p ++;
		
		remove = p - i - 1;
		if (remove > 0) {
			for (j = p; j <= len; j ++) {
				s[j - remove] = s[j];
			}
			len -= remove;
			s[len] = '\0';
		}
	}
	
	printf("%s\n", s);
	return 0;
}
