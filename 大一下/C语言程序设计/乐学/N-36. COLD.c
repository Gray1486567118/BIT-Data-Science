#include <stdio.h>

int main()
{
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	int A[n + 1];
	for (i = 0; i < n + 1; i ++)
	{
		A[i] = 0;
	}
	
	int p = 1;
	for (i = 0; i < n - 1; i ++)
	{
		for (j = 0; j < m; p ++)
		{
			if (p > n)
			{
				p = 1;
			}
			if (A[p] == 0)
			{
				j ++;
			}
		} 
		A[p - 1] = 1;
	}
	
	for (i = 1; i < n + 1; i ++)
	{
		if (A[i] == 0)
		{
			p = i;
			break;
		}
	}
	printf("%d\n", p);
	return 0;
}
