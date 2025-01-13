#include <stdio.h>

int num_days(int year, int month)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		return 31;	
	} else if (month == 2)
	{
		if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		{
			return 29;
		} else 
		{
			return 28;
		}
	} else
	{
		return 30;
	}
}

int main()
{
	int year, month, day, n;
	scanf("%d %d %d %d", &year, &month, &day, &n);
	
	while (n > 0)
	{
		if ((day + n) > num_days(year, month))
		{
			n -= ((num_days(year, month) - day) + 1);
			day = 1;
			month ++;
			if (month > 12)
			{
				month = 1;
				year ++;
			}
		} else 
		{
			day += n;
			n = 0;
		}
	}

	printf("%d.%d.%d\n", year, month, day);
	return 0;
}
