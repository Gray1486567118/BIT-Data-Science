#include <stdio.h>

int main()
{
	long long int n, counter;
	scanf("%d", &n);
	
	long long int k = 1;
	while (k <= n)
	{
		long long int quotient = n / k;
		if (quotient == 1)
		{
			counter = n - n / 2;
		} else
		{
			long long int down = n / (quotient + 1) ;
		    long long int up = n / quotient + 1;
		    counter = up - down - 1;
		}
		printf("%lld %lld\n", quotient, counter);
		k += counter;
	}
	return 0;
}
