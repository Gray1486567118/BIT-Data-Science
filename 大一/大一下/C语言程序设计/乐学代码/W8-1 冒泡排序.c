#include <stdio.h>

int main()
{
	int n, i, j;
	scanf("%d", &n);
	
	int A[n];
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &A[i]);
	}
	
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n - i - 1; j ++)
		{
			if (A[j] > A[j + 1])
			{
				int temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		 } 
	}
	
	for (i = 0; i < n - 1; i ++)
	{
		printf("%d ", A[i]);
	}
	printf("%d\n", A[i]);
	
	
	return 0;
}

