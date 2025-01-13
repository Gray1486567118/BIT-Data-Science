#include <stdio.h>

int main()
{
	int m, n, sum;
	scanf("%d", &n);
	
	for (sum = 0, m = 1; sum < n; m ++)
	{
		sum += m;
	}
	printf("%d\n", --m);
	return 0;
}
