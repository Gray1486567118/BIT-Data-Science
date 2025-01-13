#include <stdio.h>

int main()
{
	int n, counter;
	char ch;
	scanf("%d", &n);
	
	int s = 0;
	int t = 0;
	
	getchar();
	for (counter = 1; counter <= n; counter ++)
	{
		scanf("%c", &ch);
		if (ch == 's' && s == 0) s = counter;
		if (ch == 't') t = counter;
	}
	
	if (s != 0 && t != 0 && s < t)
	{
		printf("good pronunciation\n");
	} else
	{
		printf("just like Eijvy\n");
	}
	
	return 0;
}
