#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void find_prime(bool *prime_bucket, int n)
{
	int i, j;
	int primes[n];
	int k = 0;
	for (i = 2; i <= n; i ++)
	{
		if (prime_bucket[i] == true)    primes[++ k] = i;
		for (j = 1; j <= k && i * primes[j] < n; j ++)
		{
			prime_bucket[i * primes[j]] = false;
			
			if (i % primes[j] == 0)
			{
				break;
			}
		}
	}
	
}


int main()
{
	bool prime_bucket[20001];
	prime_bucket[0] = 0;
	prime_bucket[1] = 0;
	
	int i;
	for (i = 2; i <= 20001; i ++)
	{
		prime_bucket[i] = true;
	}
	
	find_prime(prime_bucket, 20001);
	
	int input;
	while (scanf("%d", &input)) 
	{
		double sq_input = sqrt(input);
		int int_sq_input = (int) sq_input;
		
		if (sq_input != int_sq_input)
		{
			printf("TCL!\n");
		} else 
		{
			if (prime_bucket[int_sq_input])
			{
				printf("TQL!\n");
			} else
			{
				printf("TCL!\n");
			}
		}
		
		char c = getchar();
		if (c == '\n')     break;
	}
	return 0;
}
