#include <stdio.h>

int main()
{
	int n, num, row;
	scanf("%d", &n);
	

	for (row = 1; row <= n; row ++)
	{
		int num_space = (n - row) * 2;
		while (num_space > 0)
		{
			printf(" ");
			num_space --;
		}
		for (num = 1; num <= row; num ++)
		{
			printf("%2d", num);
		}
		for (num -= 2; num >= 1; num --)
		{
			printf("%2d", num);
		}
		printf("\n");
	}
	return 0;
}
