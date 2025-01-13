#include <stdio.h>

void printchar(char c, int n);
char nextchar(char c, int direction);

int main()
{
	int n, i, j;
	char first_char;
	scanf("%d %c", &n, &first_char);
	
	int num_space = n - 1;
	char char_to_print = first_char;
	
	// 1st line
	
	
	for (i = 1; i <= n; i ++)
	{
		printchar(' ', num_space);
		num_space --;
		
		for (j = 0; j < i; j ++)
		{
			printf("%c", char_to_print);
			char_to_print = nextchar(char_to_print, 1);
		}
		
		
		char_to_print = nextchar(char_to_print, 2);
		for (j = 0; j < i - 1; j ++)
		{
			char_to_print = nextchar(char_to_print, 2);
			printf("%c", char_to_print);
		}
		
		char_to_print = nextchar(char_to_print, 1);
		printf("\n");
	}
	return 0;
}



void printchar(char c, int n)
{
	int i;
	for (i = 0; i < n; i ++)
	{
		printf("%c", c);
	}
}


char nextchar(char c, int direction)
{
	if (direction == 1)
	{
		c ++;
	} else
	{
		c --;
	}
	
	if (c > 'Z')    c = 'A';
	if (c < 'A')    c = 'Z';
	
	return c;
}
