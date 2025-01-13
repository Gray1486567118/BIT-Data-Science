#include <stdio.h>

int main()
{
	int m, n;
	scanf("%d %d", &m, &n);

	if (m > n)
	{
		printf("min=%d\n", n);
	} else
	{
		printf("min=%d\n", m);
	}
	return 0;
}
