#include <stdio.h>

int maxDif(int *a, int len)
{
	int maxdif = a[1] - a[0];
	int max_index1 = 0, max_index2 = 1, min = a[0];
	
	int i;
	for (i = 1; i < len; i ++)
	{
		if (a[i] < min)
		{
			max_index1 = i;
			min = a[i];
		} else
		{
			if (a[i] - min > maxdif)
			{
				maxdif = a[i] - min;
				max_index2 = i;
			}
		}
	}
	
	return maxdif;
}



int main()
{
	int n, m, i, input;
	scanf("%d %d", &n, &m);
	int s[n + 1];
	s[0] = 0;
	
	for (i = 1; i < n + 1; i ++)
	{
		s[i] = s[i - 1] - 1;
		scanf("%d", &input);
		if (input == 1)
		{   
			s[i] += m;
		}
	}
	
	int like = maxDif(s, n + 1);
	printf("%d\n", like);
	return 0;
}

