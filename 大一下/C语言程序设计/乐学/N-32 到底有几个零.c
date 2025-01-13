#include <stdio.h>
#include <math.h>

int main()
{
	int m, counter;
	long long n, num, num_of_5;
	scanf("%d", &m);
	
	for (counter = 0; counter < m; counter ++)
	{
		scanf("%lld", &n);
		int count_of_5; // 大于等于5的几次方 
		for (num = 1, count_of_5 = -1; num <= n; num *= 5)
		{
			count_of_5 ++;
		}
		//printf("%d", count_of_5);
		
		for (num_of_5 = 0; count_of_5 > 0; count_of_5 --)
		{
			num /= 5;
			num_of_5 += n / num;
		}
		printf("%lld\n", num_of_5);
	}
	return 0;
}
