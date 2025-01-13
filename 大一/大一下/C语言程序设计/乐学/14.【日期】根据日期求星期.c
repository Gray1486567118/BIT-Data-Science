#include <stdio.h>

int main()
{
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	
	if (month < 3) 
	{
        month += 12;
        year--;
    }
	
	int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
	printf("%d\n", (h + 1) % 7);
	return 0;
}
