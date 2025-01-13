#include <stdio.h>

int main()
{
	int apple, first_take;
	scanf("%d", &apple);
	
	first_take = apple % 3;
	
	printf("%d\n", first_take);
	return 0;
}
