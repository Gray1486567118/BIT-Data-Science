#include <stdio.h>

int yihuo(int a, int b)
{
	int num = a;
	if (a == b)
	{
		return a;
	} else
	{
		while (a < b)
		{
			num ^= ++a;
		}
		return num;
	}
}

int main()
{
	int n, counter, low, up;
	scanf("%d", &n);
	
	for (counter = 0; counter < n; counter ++)
	{
		scanf("%d %d", &low, &up);
		if (up - low > 3)
		{
			if (low % 2 == 0)
			{
				low = up - (up - low) % 4;
				printf("%d\n", yihuo(low, up));
			} else
			{
				if ((up - low) % 4 == 0)
				{
					printf("%d\n", low);
				} else
				{
					printf("%d\n", low ^ yihuo(up - (up - low) % 4 + 1, up));
				}
			}
		} else
		{
			printf("%d\n", yihuo(low, up));
		}
	}
	return 0;
}
