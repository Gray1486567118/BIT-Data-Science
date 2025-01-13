#include <stdio.h>
#include <string.h> 
#define size 101

int main()
{
	char s1[size], s2[size];
	scanf("%s", &s1);
	scanf("%s", &s2);
	
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	
	int replace;
	int min = len2;  // 初始最小替换次数 
	int i, j;
	if (len2 > len1)
	{
		min = -1;
	} else
	{
		for (i = 0; i <= len1 - len2; i ++)
		{
			for (j = 0; j < len2; j ++)
			{
				if (s1[i + j] != s2[j])
				{
					replace ++;
				}
			}
			
			if (replace < min)
			{
				min = replace;
			}
			
			replace = 0;
		}
	}
	
	printf("%d\n", min);
	return 0;
}

