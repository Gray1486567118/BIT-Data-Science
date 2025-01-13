#include <stdio.h>

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	int output = 0;
	while (n <= m)
	{
		if (n % 3 == 0)
		{
			printf("%d\n", n);
			output = 1;
		}
		n ++;
	}
	
	if (output == 0) printf("\n");
	return 0;
}
