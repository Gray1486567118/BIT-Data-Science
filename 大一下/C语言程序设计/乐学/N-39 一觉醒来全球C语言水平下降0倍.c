#include <stdio.h>

int main()
{
	int n, i;
	scanf("%d", &n);
	
	int A[n], B[n];
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &A[i]);
	}
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &B[i]);
	}
	for (i = 0; i < n - 1; i ++)
	{
		printf("%d ", A[i] + B[i]);
	}
	printf("%d\n", A[i] + B[i]);
	return 0;
}
