#include <stdio.h>

int main()
{
	int m, n, counter;
	scanf("%d %d", &m, &n);
	
	for (counter = 0; counter < n; counter ++)
	{
		printf("%d", m);
		m ++;
	}
	printf("\n");
	return 0;
}
