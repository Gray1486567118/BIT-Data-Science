#include <stdio.h>
#define size 100

int main()
{
	char str1[size], str2[size];
	char input;
	int i;
	
	// input
	if ((input = getchar()) == '\n')
	{
		str1[0] = '\0';
	} else
	{
		str1[0] = input;
		for (i = 1; (input = getchar()) != '\n'; i ++)
		{
			str1[i] = input;
		}
		str1[i] = '\0';
	}
	
	if ((input = getchar()) == '\n')
	{
		str2[0] = '\0';
	} else
	{
		str2[0] = input;
		for (i = 1; (input = getchar()) != '\n'; i ++)
		{
			str2[i] = input;
		}
		str2[i] = '\0';
	}
	
	
	// output
	char *p1 = str1, *p2 = str2;

	while ((*p1 != '\0') && (*p2 != '\0'))
	{
		if (*p1 < *p2)
		{
			printf("%c", *p1);
			p1 ++;
		} else
		{
			printf("%c", *p2);
			p2 ++;
		}
	}
	printf("%s%s\n", p1, p2);
	
	
	return 0;
}
