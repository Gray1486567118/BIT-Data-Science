#include <stdio.h>

void printChar(char ch, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%c", ch);
	}
}

char vowel(char ch)
{
	if (ch == 97 || ch == 101 || ch == 105 || ch == 111 || ch == 117)
	{
		ch ++;
	}
	return ch;
}

char nextchar(char ch)
{
	ch ++;
	ch = vowel(ch);
	if (ch == 123)
	{
		ch = 98;
	}
	return ch;
}

char priorchar(char ch)
{
	ch --;
	if (ch == 97 || ch == 101 || ch == 105 || ch == 111 || ch == 117)
	{
		ch --;
	}
	if (ch == 96)
	{
		ch = 122;
	}
	return ch;
}



int main()
{
	int n, i;
	char ch;
	scanf("%d %c", &n, &ch);
	ch = vowel(ch);
	
	int num_space1 = 0, num_space2 = 2 * n - 3;
	char first = ch, second;
	for (i = 0, second = ch; i < 2 * n - 2; i ++)
	{
		second = nextchar(second);
	}

	// 1st half
	for (i = 0; i < n - 1; i ++)
	{
		printChar(' ', num_space1);
		num_space1 ++;
		
		printf("%c", first);
		first = nextchar(first);
		
		printChar(' ', num_space2);
		num_space2 -= 2;
		
		printf("%c", second);
		second = priorchar(second);
		
		printf("\n");
	}
	
	// mid
	printChar(' ', num_space1);
	printf("%c\n", first);
	
	// 2nd half
	
	for (i = 0; i < n - 1; i ++)
	{
		num_space1 --;
		printChar(' ', num_space1);
		
		first = priorchar(first);
		printf("%c", first);
		
		num_space2 += 2;
		printChar(' ', num_space2);
		
		second = nextchar(second);
		printf("%c", second);
		
		printf("\n");
	}

	return 0;
}

