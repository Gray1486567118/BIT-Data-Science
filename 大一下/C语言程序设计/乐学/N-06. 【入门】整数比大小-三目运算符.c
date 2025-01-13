#include <stdio.h>

int main()
{
	int a, b, min;
	scanf("%d %d", &a, &b);
	
	min = (a > b) ? b : a;
	printf("min=%d\n", min);
	return 0 ;
}
