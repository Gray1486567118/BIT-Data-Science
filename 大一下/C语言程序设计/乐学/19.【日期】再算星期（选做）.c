#include <stdio.h>

int main()
{
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	
	int error = 0;
	if (month > 12 || month < 1)
	{
		printf("month is error.\n");
		error = 1;
	}
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)  && day > 31)
	{
		printf("day is error.\n");
		error = 1;
	} else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
		printf("day is error.\n");	
		error = 1;
	} else if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if (day > 29)
			{
				printf("day is error.\n");	
				error = 1;
			}
		} else
		{
			if (day > 28)
			{
				printf("day is error.\n");	
				error = 1;
			}
		}
	}
	
	if (error == 0) 
	{
		if (month < 3) 
		{
        month += 12;
        year--;
    	}
	
		int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
		printf("%d\n", (h + 1) % 7);
	}
	
	return 0;
 } 
