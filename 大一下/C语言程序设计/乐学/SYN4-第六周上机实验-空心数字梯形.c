#include <stdio.h>

int printchar(char ch, int num);
int printnum(int m, int num);


int main()
{
	int n, first_num, row;
	scanf("%d %d", &n, &first_num);
	int num_to_print = first_num;
	
	// first line
	printnum(num_to_print, 3 * n - 2);
	printf("\n");
	num_to_print = (num_to_print + 1) % 10;
	
	// mid part
	for (row = 1; row < n - 1; row ++)
	{
		printchar(' ', row);
		printf("%d", num_to_print);
		printchar(' ', 3 * n - 4 - 2 * row);
		printf("%d\n", num_to_print);
		num_to_print = (num_to_print + 1) % 10;
	}
	
	//last line
	if (n > 1)
	{
		printchar(' ', row);
		printnum(num_to_print, n);
		printf("\n");
	}
	return 0;
}




int printnum(int m, int num)
{
	int i;
	for (i = 0; i < num; i ++)
	{
		printf("%d", m);
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
