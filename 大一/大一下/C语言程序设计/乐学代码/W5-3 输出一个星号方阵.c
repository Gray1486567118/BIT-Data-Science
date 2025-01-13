#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	
	int i, j;
	int printed = 0;
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n; j ++)
		{
			printf("*");
			printed = 1;
		}
		printf("\n");
	}
	if (printed == 0) printf("\n");
	return 0;
}
