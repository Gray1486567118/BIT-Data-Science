#include <stdio.h>
#include <string.h>

int main() {
	char s[10000];
	scanf("%s", &s);
	int len = strlen(s);
	int left, right;
	if (s[len - 1] < 'A' || (s[len - 1] > 'Z' && s[len - 1] < 'a') || s[len - 1] > 'z') {
		right = len - 2;
	} else {
		right = len - 1;
	}
	
	for (left = 0; left < right; left ++, right --) {
		if (s[left] > s[right]) {
			char t = s[left];
			s[left] = s[right];
			s[right] = t;
			
		}
	}
	
	printf("%s", s);
	return 0;
}
