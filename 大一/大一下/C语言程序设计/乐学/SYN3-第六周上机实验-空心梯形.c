#include <stdio.h>

int printchar(char ch, int num);



int main()
{
	int n, row;
	scanf("%d", &n);
	
	// first line
	printchar('*', 3 * n - 2);
	printf("\n");
	
	// mid part
	for (row = 1; row < n - 1; row ++)
	{
		printchar(' ', row);
		printf("*");
		printchar(' ', 3 * n - 4 - 2 * row);
		printf("*\n");
	}
	
	//last line
	if (n > 1)
	{
		printchar(' ', row);
		printchar('*', n);
		printf("\n");
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
