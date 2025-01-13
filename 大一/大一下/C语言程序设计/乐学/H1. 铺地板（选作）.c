#include <stdio.h>

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int main()
{
	int n, num, i, j, cross_num, judge, counter;
	scanf("%d", &n);
	int A[10][10] = {0};
	
	i = 0;
	j = 0;
	num = 1;
	for (cross_num = 1, judge = 1; cross_num <= (2 * n -1); cross_num ++)
	{
		counter = 0;
		
		A[i][j] = num ++;
		counter ++;
		
		while (counter < min((2 * n - cross_num), cross_num))
		{
			if (cross_num > n) judge = 1 - judge;
			if (judge)
			{
				i --;
				j ++;
			} else
			{
				i ++;
				j --;
			}
			A[i][j] = num ++;
			counter ++;
			if (cross_num > n) judge = 1 - judge;
		}
		
		if (cross_num == n) judge = 1 - judge;
		
		if (judge)
		{
			j ++;
		} else
		{
			i ++;
		}
		judge = 1 - judge;
	}
	
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < (n - 1); j++)
		{
			printf("%2d ", A[i][j]);
		}
		printf("%2d\n", A[i][n-1]);
	}
	
	return 0;
}
