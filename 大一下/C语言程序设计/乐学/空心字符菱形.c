#include <stdio.h>
#include <math.h>

int main()
{
	char ch;
	int n, row;
	scanf("%c %d", &ch, &n);
	
	for (row = 1; row <= 2 * n - 1; row ++)
	{
		int num_space1 = abs(n - row);
		while (num_space1 > 0)
		{
			printf(" ");
			num_space1 --;
		}
		
		if (row == 1 || row == 2 * n - 1)
		{
			printf("%c\n", ch);
			ch ++;
		} else
		{
			printf("%c", ch);
			int num_space2 = 2 * n - 3 - 2 * abs(row - n);
			while (num_space2 > 0)
			{
				printf(" ");
				num_space2 --;
			}
			printf("%c\n", ch);
			if (row < n) ch ++;
			else ch --;
		}
	}
	return 0;
} 
