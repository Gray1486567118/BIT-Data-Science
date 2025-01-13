#include <stdio.h>

int printchar(char ch, int num);
int printnum(int m, int num);


int main()
{
	int n, first_num, row, i;
	scanf("%d %d", &n, &first_num);
	int num_to_print = first_num;
	
	// first line
	for (i = 0; i < (3 * n - 1) / 2; i ++)
	{
		printf("%d", num_to_print);
		num_to_print = (num_to_print + 1) % 10;
	}
	if (n % 2 == 1)
	{
		num_to_print = (num_to_print + 8) % 10;
		for (i = 0; i < (3 * n - 1) / 2 - 1; i ++)
		{
			printf("%d", num_to_print);
			num_to_print = (num_to_print + 9) % 10;
		}
	} else
	{
		num_to_print = (num_to_print + 9) % 10;
		for (i = 0; i < (3 * n - 1) / 2; i ++)
		{
			printf("%d", num_to_print);
			num_to_print = (num_to_print + 9) % 10;
		}
	}
	printf("\n");

	
	// mid part
	int num = (first_num + 1) % 10;
	
	for (row = 1; row < n - 1; row ++)
	{
		printchar(' ', row);
		printf("%d", num);
		printchar(' ', 3 * n - 4 - 2 * row);
		printf("%d\n", num);
		num = (num + 1) % 10; 
	}
	
	//last line
	if (n > 1)
	{
		printchar(' ', row);
		for (i = 0; i < (n + 1) / 2; i ++)
		{
			printf("%d", num);
			num = (num + 1) % 10;
		}
		num -= 1;
		
		if (n % 2 == 1)
		{
			num -= 1;
			for (i = 0; i < n - ((n + 1) / 2); i ++)
			{
				printf("%d", num);
				num = (num + 9) % 10;
			}
		} else
		{
			for (i = 0; i < n / 2; i ++)
			{
				printf("%d", num);
				num = (num + 9) % 10;
			}
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
