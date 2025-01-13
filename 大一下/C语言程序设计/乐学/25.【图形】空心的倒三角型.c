#include <stdio.h>

int main()
{
	int h;
	scanf("%d", &h);
	
	int k;
	for (k = 0; k < (2 * h - 1); k ++)
	{
		printf("*");
	}
	printf("\n");
	
	int i, j, counter;
	for(i = 1, j = 2 * h - 5, k = 0; k < h - 2; k ++)
	{
		for (counter = 0; counter < i; counter ++)
		{
			printf(" ");
		}
		printf("*");
		for (counter = 0; counter < j; counter ++)
		{
			printf(" ");
		}
		printf("*\n");
		i ++;
		j -= 2;
	}
	
	for (k = 0; k < (h - 1); k ++)
	{
		printf(" ");
	}
	printf("*\n");
	
	return 0;	
}
