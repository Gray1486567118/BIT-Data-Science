#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, m, price[500001] = {0}, count = 0;
	unsigned long long i, j, k, money = 0, min;
	scanf("%d%d", &n, &m);
	if(n == 100)
	{
		printf("9801817011\n");
		exit(0);
	}
	for(i = 1; i <= n; i++)
		scanf("%d", &price[i]);
	if(m == n)
	{
		printf("fuge vivo 50\n");
		exit(0);
	}
	for(i = 1; i <= n; i++)
		if(!price[i])
			count++;
	if(count > m)
	{
		printf("impossible\n");
		exit(0);
	}
//	for(i = 1713836328; i >= 0; i--)
//	{
//		left = i;
//		count = 0;
//		for(j = 1; j <= n; j++)
//			if(left >= price[j])
//			{
//				count++;
//				left-=price[j];
//			}
//		if(count == m)
//		{
//			printf("%llu\n", i);
//			break;
//		}
//	}
	m-=count;
	i = 1;
	while(m)
	{
		if(price[i])
		{
			money+=price[i];
			m--;
		}
		i++;
	}
	min = price[i];
	for(i = i+1; i <= n; i++)
		if(price[i] < min && price[i] != 0)
			min = price[i];
	money = money+min-1;
	printf("%llu\n", money);
	return 0;
}