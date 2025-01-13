#include <stdio.h>
#include <string.h>
#define size 101

int match(char *s)
{
	char pattern1[7] = "CCCGGG";
	char pattern2[7] = "GGGCCC";
	int i;
	int match = 2;
	
	for (i = 0; i < 6; i ++)
	{
		if (s[i] != pattern1[i])
		{
			match --;
			break;
		} 
	}
	
	for (i = 0; i < 6; i ++)
	{
		if (s[i] != pattern2[i])
		{
			match --;
			break;
		} 
	}
	
	return match;
}

void seq(char *s, char *cut)
{
	int i, j, k;
	int len = strlen(s);
	int lastCut = -1;
	
	for (i = 0; i < len - 1; i ++)
	{
		if (i + 5 < len)
		{
			if (match(&s[i]) > 0)
			{
				i += 2;
				for (j = len - 1 - i, k = lastCut + 1; j < len - 1 - lastCut; j ++, k ++)
				{
					cut[j] = s[k];
				} 
				lastCut = i;
			}
		}
	}
	
	
	for (i = lastCut + 1, j = 0; i < len; i ++, j ++)
	{
		cut[j] = s[i];
	}
	cut[len] = '\0';
}

int main()
{
	char s1[size], s2[size], cut1[size], cut2[size];
	scanf("%s %s", &s1, &s2);
	
	seq(s1, cut1);
	seq(s2, cut2);
	
	printf("%s\n%s\n", cut1, cut2);
	return 0;
}

