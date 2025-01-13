#include <stdio.h>

int main()
{
	int t = 0, i;
	for(i = 1;i <= 9;i ++){
		int x;
		scanf("%d", &x);
		t ^= x;
	}
	printf("%d\n", t);
	return 0;
}
