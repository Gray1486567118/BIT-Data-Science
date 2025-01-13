#include <stdio.h>
#define size 201307


int main()
{
	int n, i, input, max = -1;
	scanf("%d", &n);
	
	int a[size + 1];
	for (i = 0; i < size + 1; i ++)
	{
		a[i] = 0;
	}
	
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &input);
		if (a[input] != 1)
		{
			a[input] ++;
			if (input > max)
			{
				max = input;
			}
		}
	}
	
	for (i = 0; i < max; i ++)
	{
		if (a[i] == 1)
		{
			printf("%d ", i);
		}
	}
	printf("%d\n", max);
	return 0;
}

