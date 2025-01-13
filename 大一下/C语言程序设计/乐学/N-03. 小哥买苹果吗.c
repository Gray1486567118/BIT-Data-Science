#include <stdio.h>

int main()
{
	int coin, num_fruits, price_a, price_p, coin_remain;
	scanf("%d %d %d %d", &coin, &num_fruits, &price_a, &price_p);
	
	int num_a = 0;
	int num_p;
	while (num_a * price_a <= coin)
	{
		num_p = num_fruits - num_a;
		coin_remain = coin - num_a * price_a;
		if ((num_p * price_p) == coin_remain)
		{
			printf("%d %d\n", num_a, num_p);
			break;
		}
		num_a ++;
	}
	return 0;
}
