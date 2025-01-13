#include <stdio.h>

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	if ( m == 0)
	{
		printf((n == 0) ? "Yes\n" : "No\n");
	} else
	{
		printf((n % m == 0) ? "Yes\n" : "No\n");
	}

	return 0;
}
