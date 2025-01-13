#include <stdio.h>

int main()
{
	int num;
	scanf("%d", &num);
	
	if (num > 0)
	{
		while (num > 0)
		{
			printf("*");
			num--;
		}
	}
	printf("\n");
	return 0;
}
