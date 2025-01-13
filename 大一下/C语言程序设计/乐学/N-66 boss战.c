#include <stdio.h>
#include <stdbool.h>

void euler_sleve(bool *numbers, int *store_primes, int n);
void damage(int *store_primes, int n);


int main()
{
	int n;
	scanf("%d", &n);
	bool numbers[n + 1];
	int store_primes[n + 1];
	
	euler_sleve(numbers, store_primes, n);
	damage(store_primes, n);
	
	return 0;
}


void euler_sleve(bool *numbers, int *store_primes, int n)
{
	int i, j;
	
	// 初始化 
	for (i = 0; i < n + 1; i ++)
	{
		numbers[i] = true;
		store_primes[i] = 0; 
	}
	numbers[0] = false;
	numbers[1] = false;
	
	// 筛
	int k = 0;  // 指向 store_primes[k]的指针 
	for (i = 2; i < n + 1; i ++)
	{
		if (numbers[i] == true)
		{
			store_primes[k] = i;  // 存入素数 
			k ++;
		}
		
		for (j = 0; j < k && i * store_primes[j] <= n; j ++)
		{
			numbers[i * store_primes[j]] = false;
			
			if (i % store_primes[j] == 0)
			{
				break;
			}
		}
	}
}


void damage(int *store_primes, int n)
{
	int has_damage = 0;
	
	int i;
	for (i = 0; store_primes[i] != 0 && store_primes[i + 1] != 0 && i < n; i ++)
	{
		if (store_primes[i + 1] - store_primes[i] <= 2)
		{
			printf("%d\n", store_primes[i] * store_primes[i + 1]);
			has_damage = 1;
		}
	}
	
	if (has_damage == 0)
	{
		printf("0\n");
	}
}
