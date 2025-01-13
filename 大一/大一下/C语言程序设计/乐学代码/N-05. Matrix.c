#include <stdio.h>

int main()
{
	int A[3][3];
	int i, j;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			scanf("%d", &A[i][j]);	
		}
	}
	
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if (j < 2)
			{
				printf("%d ", A[j][i]);	
			} else
			{
				printf("%d\n", A[j][i]);
			}
		}
	}
	return 0;
}
