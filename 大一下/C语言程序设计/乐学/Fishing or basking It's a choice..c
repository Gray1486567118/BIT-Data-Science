#include <stdio.h>

int num_days(int year, int month);
int weekday(int year, int month, int day);

int main()
{
	int n, counter, year, month, day;
	scanf("%d", &n);
	for (counter = 0; counter < n; counter ++)
	{
		scanf("%d %d %d", &year, &month, &day);
		int remainder = weekday(year, month, day);
		if (remainder <= 2)
		{
			printf("He was fishing on %d.%d.%d\n", year, month, day);
		} else
		{
			printf("He was basking on %d.%d.%d\n", year, month, day);
		}
	}
	return 0;
}

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

int weekday(int year, int month, int day)
{
	int weekdays = 0;
	
	// days of years
	weekdays += 365 * (year - 1990) ;
	
	// leap year before this year
	weekdays += (year - 1989) / 4;
	
	// days of month
	int m;
	for (m = 1; m <= month; m ++)
	{
		weekdays += num_days(year, m);
	}
	
	// days this month
	weekdays = weekdays - (num_days(year, month) - day) - 1;
	weekdays %= 5;
	return weekdays;
}
