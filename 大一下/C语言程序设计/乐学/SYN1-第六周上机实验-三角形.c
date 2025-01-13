#include <stdio.h>

int main()
{
	int n, row, i;
	scanf("%d", &n);
	
	for (row = 0; row < n; row ++)
	{
		// space
		for (i = 0; i < row; i ++)
		{
			printf(" ");
		} 
		
		// *
		int num_ch = 2 * n - 1 - 2 * row;
		for (i = 0; i < num_ch; i ++)
		{
			printf("*");
		}
		printf("\n");
	}
	
	return 0;
}
