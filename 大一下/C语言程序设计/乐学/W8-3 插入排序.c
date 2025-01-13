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
	
	for (i = 1; i < n ; i ++)
	{
		if (A[i] < A[i - 1])
		{
			int temp;
			temp = A[i];
			for (j = i - 1; j >= 0 && temp < A[j]; j --)
			{
				A[j + 1] = A[j];
			}
			A[j + 1] = temp;
		}
		
	}
   
   	for (i = 0; i < n - 1; i ++)
	{
		printf("%d ", A[i]);
	}
	printf("%d\n", A[i]);
	return 0;
}

