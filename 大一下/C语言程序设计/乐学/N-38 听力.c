#include <stdio.h>

int main()
{
	int n, i, input, j;
	scanf("%d", &n);
	
	int s[n + 1], Max[n];
	for (i = 0; i < n + 1; i ++)
	{
		s[i] = 0;
	}
	
	for (i = 0; i < n; i++)
	{
		scanf("%d", &input);
		s[input] ++;
	}
	
	for (i = 0, j = 0; i < n + 1; i++)
	{
		while (s[i] != 0)
		{
			Max[j] = i;
			j ++;
			s[i] --;
		}
	}
	
	for (i = 0; i < n; i ++)
	{
		Max[i] -= i;
	}
	
	long long result = 1;
	for (i = 0; i < n; i++)
	{
		result *= Max[i];
		result %= 167772161;
	}
	
	printf("%lld\n", result);
	return 0;
 } 
