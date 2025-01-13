#include <stdio.h>

int cal_gcd(int m, int n) // m > n
{
	if (n == 0)
	{
		return m;
	}
	return cal_gcd(n, m%n);
}

int main()
{
	int K, a, b, x;
	scanf("%d%d%d", &K, &a, &b);
	
	// 第K个质数: number
	int number = 2; 
	int counter = 1;
	int divider, is_prime;
	while (counter < K)
	{
		is_prime = 1;
		number ++;
		
		for (divider = 2; divider < number; divider ++)
		{
			if ((number % divider) == 0)
			{
				is_prime = 0;
				break;
			}	
		}	
		
		if (is_prime)
		{
			counter ++;
		}
	}
	
	// 行列式: x
	x = ((30 * 24) / a) % 10;
	
	// gcd
	int gcd = cal_gcd(4321, 1234);
	
	// lcm
	int lcm = 463 * b / cal_gcd(463, b);
	int fourth = (lcm / 10) % 10;
	
	int code = number * 1000 + x * 100 + gcd * 10 + fourth;
	printf("%d\n", code);
	
	return 0;
}
