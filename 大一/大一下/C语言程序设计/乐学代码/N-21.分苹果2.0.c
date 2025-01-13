#include <stdio.h>

int main()
{
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);
	
	int counter, apple;
	for (counter = 1; counter <= m; counter ++)
	{
		scanf("%d", &apple);
		if (apple < t)
		{
			n = n - (t - apple);	
		}
	} 
	if (n < 0)
	{
		printf("N\n");
		printf("%d\n", -n);
	} else
	{
		printf("Y\n");
		printf("%d\n", n);
	}
	return 0;
}
