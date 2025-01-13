#include <stdio.h>

int main() {
	int x = 10;
	
	for (  ; x > 3; x --) {
		if (x % 3) x --; --x; --x;
		printf("%d\n", x);
	}
	return 0;
}
