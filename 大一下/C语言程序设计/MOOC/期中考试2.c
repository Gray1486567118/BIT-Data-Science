#include <stdio.h>
#include <string.h>
#define size 3000

int find_pattern(char *s1, char *pattern, int len1, int len2);

int main()
{
	char s1[size], s2[size], s3[size];
	gets(s1);
	gets(s2);
	gets(s3);
	int position = 0, i;
	int move;
	
	int len1 = strlen(s1), len2 = strlen(s2), len3 = strlen(s3);
	
	if (len3 == 0)
	{
		while (find_pattern(s1, s2, len1, len2) != -1)
		{
			position = find_pattern(s1, s2, len1, len2);
			
			move = len2;
			for (i = position + len2; i < len1; i ++)
			{
				s1[i - len2] = s1[i];
			}
			
			len1 -= len2;
			s1[len1] = '\0';
		}
	} else 
	{
		while (find_pattern(s1, s2, len1, len2) != -1)
		{
			position = find_pattern(s1, s2, len1, len2);
			if (len2 == len3)
			{
				for (i = 0; i < len3; i ++)
				{
					s1[i + position] = s3[i];
				}
			} else if (len2 < len3)
			{
				move = len3 - len2;
				for (i = len1 - 1; i >= position + len2; i --)
				{
					s1[i + move] = s1[i];
				} 
				
				for (i = 0; i < len3; i ++)
				{
					s1[i + position] = s3[i];
				}
				
				len1 += move;
				s1[len1] = '\0';
			} else
			{
				move = len2 - len3;
				for (i = position + len2; i < len1; i ++)
				{
					s1[i - move] = s1[i];
				}
				
				for (i = 0; i < len3; i ++)
				{
					s1[i + position] = s3[i];
				}
				
				len1 -= move;
				s1[len1] = '\0';
			}
		}
	}
	
	printf("%s", s1);
	return 0;

}




int find_pattern(char *s1, char *pattern, int len1, int len2)
{
	int i, j;
	
	if (len1 >= len2)
	{
		for (i = 0; i < len1 - len2 + 1; i ++)
		{
			int match = 1;
			for (j = 0; j < len2; j ++)
			{
				if (pattern[j] != s1[i + j])
				{
					match = 0;
					break;
				}
			} 
			
			if (match == 1)
			{
				return i;
			}
		}
		
	}
	

	return -1; // ²»´æÔÚ 
}
