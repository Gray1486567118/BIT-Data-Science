#include <stdio.h>
#include <math.h>

int next_prime(int now_prime);
int is_prime(int n);

int main()
{
	int n;
	scanf("%d", &n);
	int now_prime = 3;
	
	while (now_prime <= n / 2)
	{
		if (is_prime(n - now_prime))
		{
			printf("%d=%d+%d\n", n, now_prime, n - now_prime);
			break;
		}
		now_prime = next_prime(now_prime);
	}
	return 0;
}

int is_prime(int n)
{
	int m;
	int is = 1;
	for (m = 2; m <= sqrt(n); m ++)
	{
		if (n % m == 0)
		{
			is = 0;
			break;
		}
	}
	return is;
}

int next_prime(int now_prime)
{
	do
	{
		now_prime ++;
	}
	while (is_prime(now_prime) != 1);
	return now_prime;
}
