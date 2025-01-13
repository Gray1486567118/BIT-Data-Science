#include <stdio.h>

int main()
{
	int n;
	int num = 1;
	scanf("%d", &n);
	int counter = 0;
	int n_store = n;
	
	while (n > 0)
	{
		while (counter < n_store)
		{
			printf("%3d", num);
			num ++;
			counter ++;
		}
		printf("\n");
		counter = 0;
		n --;
	}
	return 0;
}
