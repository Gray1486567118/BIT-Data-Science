#include <stdio.h>

int main()
{
	int n, num;
	scanf("%d", &n);
	int A[10][10] = {0};
	
	int moves[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	
	int i, j, next;
	for (num = 1, i = 0, j = 0, next = 0; num <= n * n; num ++)
	{
		A[i][j] = num;
		
		int next_i = i + moves[next][0];
		int next_j = j + moves[next][1];
		
		if (next_i < 0 || next_i >= n || next_j < 0 || next_j >= n || A[next_i][next_j] != 0)
		{
			next = (next + 1) % 4;
		}		
		
		i += moves[next][0];
		j += moves[next][1];
	}
	
	for (i = 0; i < n; i ++)
	{
		printf(" ");
		for (j = 0; j < n - 1; j ++)
		{
			printf("%2d ", A[i][j]);
		}
		printf("%2d\n", A[i][n-1]);
	}
	
	return 0;
}
