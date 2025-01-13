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
	int weekdays = 2; // 1901.1.1 Tuesday
	int year;
	int month = 5;
	int day = 1;
	scanf("%d", &year);
	
	// days of years
	weekdays += 365 * (year - 1901) ;
	
	// leap year before this year
	weekdays += (year - 1901) / 4;
	
	// days of month
	int m;
	for (m = 1; m <= month; m ++)
	{
		weekdays += num_days(year, m);
	}
	
	// days this month
	weekdays = weekdays - (num_days(year, month) - day) - 1;
	
	weekdays %= 7;
	
	if (weekdays == 1)
	{
		printf("5.01-5.07");
	} else if (weekdays == 2)
	{
		printf("4.30-5.06");
	} else if (weekdays == 3)
	{
		printf("4.29-5.05");
	} else if (weekdays == 4)
	{
		printf("4.28-5.04");
	} else if (weekdays == 5)
	{
		printf("4.27-5.03");
	} else if (weekdays == 6)
	{
		printf("5.01-5.07");
	} else if (weekdays == 0)
	{
		printf("4.30-5.06");
	}
	return 0;
}
