#include <stdio.h>

int main()
{
	int n, peach;
	scanf("%d", &n);
	
	for (peach = 1; n > 1; n --)
	{
		peach = (peach + n - 1) * 2;
	}
	if (peach == 1)
	{
		printf("The monkey got 1 peach in first day.\n");
	} else
	{
		printf("The monkey got %d peaches in first day.\n", peach);
	}
	return 0;
}
