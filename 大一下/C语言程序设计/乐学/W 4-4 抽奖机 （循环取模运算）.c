#include <stdio.h>
#include <math.h>

int main()
{
	int n, num, counter, bonus, num_backup;
	scanf("%d", &n);
	
	for (num = 1, counter = 0, bonus = 0; num <= n; num ++)
	{
		for (num_backup = num; num_backup > 0; num_backup /= 10)
		{
			if (num_backup % 10 == 6)
			{
				counter ++;
			}
		}
		
		for (; counter > 0; counter --)
		{
			bonus += 6 * pow(10, counter-1);
		}
	}
	
	printf("%d\n", bonus);
	return 0;
}
