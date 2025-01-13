#include <stdio.h>

int printchar(char ch, int num);
int printnum(int m, int num);


int main()
{
	int n, first_num, row, i;
	scanf("%d %d", &n, &first_num);
	int num_to_print = first_num;
	
	// first line
	for (i = 0; i < 3 * n - 2; i ++)
	{
		printf("%d", num_to_print);
		num_to_print = (num_to_print + 1) % 10;
	}
	printf("\n");

	
	// mid part
	int num1 = (first_num + 1) % 10;
	int num2 = (first_num + 3 * n - 4) % 10;
	
	for (row = 1; row < n - 1; row ++)
	{
		printchar(' ', row);
		printf("%d", num1);
		num1 = (num1 + 1) % 10; 
		printchar(' ', 3 * n - 4 - 2 * row);
		printf("%d\n", num2);
		num2 = (num2 + 9) % 10;
	}
	
	//last line
	if (n > 1)
	{
		printchar(' ', row);
		for (i = 0; i < n; i ++)
		{
			printf("%d", num1);
			num1 = (num1 + 1) % 10;
		}
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
