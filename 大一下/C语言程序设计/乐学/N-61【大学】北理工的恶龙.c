#include <stdio.h>

int fight(int *dragon, int *brave, int n, int m, int big_worrier);

int main()
{
	int n, m, i;
	scanf("%d %d", &n, &m);
	
	int dragon[n], brave[m];
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &dragon[i]);
	}
	
	int big_worrier = 0;
	for (i = 0; i < m; i ++)
	{
		scanf("%d", &brave[i]);
		
		if (brave[i] > big_worrier)  
		{
			big_worrier = brave[i];
		}
	} 
	
	int beat = fight(dragon, brave, n, m, big_worrier);
	
	if (beat == 0)
	{
		printf("bit is doomed!\n");
	} else
	{
		printf("%d\n", beat);
	}
	return 0;
}

int fight(int *dragon, int *brave, int n, int m, int big_worrier)
{
	if (m < n)
	{
		return 0;
	} else
	{
		int i, j;
		int min_p = 0;
		
		for (i = 0; i < n; i ++)
		{
			int min_worrier = big_worrier;
			int has_worrier = 0;
			int position;
			
			for (j = 0; j < m; j ++)
			{
				if (brave[j] >= dragon[i] && brave[j] <= min_worrier && brave[j] != 0)
				{
					min_worrier = brave[j];
					position = j;
					has_worrier = 1;
				}
			}
			
			if (has_worrier == 0)
			{
				return 0;
			}
			
			min_p += min_worrier;
			brave[position] = 0;
		}
		
		return min_p;
	}
	
}

