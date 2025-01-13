#include <stdio.h>

char nextchar(char ch)
{
	ch ++;
	if (ch == 91)
	{
		ch = 65;
	}
	return ch;
}

void printchar(char ch, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%c", ch);
	}
}



int main()
{
	int n, i;
	scanf("%d", &n);
	char ch = 'A';
	
	// 1st line
	for (i = 0; i < n; i ++)
	{
		printf("%c", ch);
		ch = nextchar(ch);
	}
	printf("\n");
	
	
	if (n != 1)
	{
		// mid
		int num_space = n - 2;
		for (i = 0; i < n - 2; i ++)
		{
			printchar(' ', num_space);
			num_space --;
			printf("%c", ch);
			ch = nextchar(ch);
			printf("\n");
		}
		
		// last line
		for (i = 0; i < n; i ++)
		{
			printf("%c", ch);
			ch = nextchar(ch);
		}
		printf("\n");
	}
	
	return 0;
}

