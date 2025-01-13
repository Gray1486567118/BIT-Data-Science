#include <stdio.h>

void printchar(char ch, int num);


int main()
{
	int first_num, n, i;
	scanf("%d %d", &first_num, &n);
	int num_to_print = first_num;
	
	// first line
	for (i = 0; i < n; i ++)
	{
		printf("%d", num_to_print);
		num_to_print = (num_to_print + 1) % 10;
	}
	printf("\n");
	
	// mid
	if (n != 1 && n != 0)
	{
		int num1 = (num_to_print + n * 2 - 4) % 10;
		int num2 = num_to_print;
		int num_space = n - 3;
		
		for (i = 0; i < n - 2; i ++)
		{
			printf("%d", num1);
			num1 = (num1 + 9) % 10;
			
			printchar(' ', num_space);
			num_space --;
			
			printf("%d", num2);
			num2 = (num2 + 1) % 10;
			printf("\n");
		}
		
		printf("%d\n", num1);
	}
	return 0;
}





void printchar(char ch, int num)
{
	int i;
	for (i = 0; i < num; i ++)
	{
		printf("%c", ch);
	}
}
