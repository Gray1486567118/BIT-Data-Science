#include <stdio.h>
int printchar(char ch, int num);

int main()
{
	int n, m, k, row; // height width equator
	scanf("%d %d %d", &n, &m, &k);
	
	// 上界 
	printf("+");
	printchar('-', m - 2);
	printf("+\n");
	
	// 其余部分
	for (row = 2; row <= n; row ++)
	{
		if (row == k)
		{
			printf("<");
			printchar('=', m - 2);
			printf(">\n");
		} else if (row == n)
		{
			printf("+");
			printchar('-', m - 2);
			printf("+\n");	
		} else
		{
			printf("|");
			printchar('.', m - 2);
			printf("|\n");
		}
	}
	return 0;
}

int printchar(char ch, int num)
{
	int i;
	for (i = 0; i < num; i ++)
	{
		printf("%c", ch);
	}
	return 0;
}
