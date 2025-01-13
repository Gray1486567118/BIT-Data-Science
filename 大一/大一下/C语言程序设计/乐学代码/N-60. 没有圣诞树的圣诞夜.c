#include <stdio.h>

int len_trunk(int height);
void printchar(char c, int n);
int num_group(int height, int trunk);

int main()
{
	int n, trunk, group, i;
	scanf("%d", &n);
	
	trunk = len_trunk(n);
	group = num_group(n, trunk);
	
	int mid = 4 * group + 2;
	for (i = 1; i <= group; i ++)
	{
		printchar(' ', mid - 2);
		printchar('*', 3);
		printf("\n");
		
		printchar(' ', mid - 2 - 2 * i);
		printchar('*', 3 + 4 * i);
		printf("\n");
		
		printchar(' ', mid - 2 - 4 * i);
		printchar('*', 3 + 8 * i);
		printf("\n");
	}
	
	for (i = 1; i <= trunk; i ++)
	{
		printchar(' ', mid - 2);
		printchar('*', 3);
		printf("\n");
	}
	return 0;
}





int len_trunk(int height)
{
	int n = height % 3;
	if (n == 0)
	{
		return 3;
	} else if (n == 1)
	{
		return 1;
	} else 
	{
		return 2;
	}
}


void printchar(char c, int n)
{
	int i;
	for (i = 0; i < n; i ++)
	{
		printf("%c", c);
	}
}


int num_group(int height, int trunk)
{
	int group = height / 3;
	if (trunk == 3)    group --;
	return group;
}
