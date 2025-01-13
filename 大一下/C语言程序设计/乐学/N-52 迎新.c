#include <stdio.h>

void vrqfb(int *grade, int n)
{
	int e, s, k, i, j;
	int counter = 0;
	
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &e);
		if (e == 0)
		{
			scanf("%d", &s);
			if(counter == 0)
			{
				grade[1] = s;
			} else
			{
				if (s > grade[counter])
				{
					grade[counter + 1] = s;
				} else
				{
					for (j = counter; j >= 1 && s < grade[j]; j --)
					{
						grade[j + 1] = grade[j];
					}
					grade[j + 1] = s;
				}
			}
			counter ++;
		} else if (e == 1)
		{
			scanf("%d", &k);
			printf("%d\n", grade[k]);
			for (j = k; j <= counter; j ++)
			{
				grade[j] = grade[j + 1];
			} 
			counter --;
		}
	}
}


int main()
{
	int n; //days
	scanf("%d", &n);

	int grade[4001] = {0};
	vrqfb(grade, n);
	return 0;
}

