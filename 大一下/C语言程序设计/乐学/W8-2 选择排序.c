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
	
	for (i = 0; i < n - 1; i ++)
	{
		for (j = i; j < n - 1; j ++)
		{
			int small = j;
			if (A[j + 1] < A[j])
			{
				small = j + 1;
			}
			
			if (small != i)
			{
				int temp = A[j];
				A[j] = A[small];
				A[small] = temp;	
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

