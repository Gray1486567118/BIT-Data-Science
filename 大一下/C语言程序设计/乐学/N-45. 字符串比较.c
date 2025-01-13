#include <stdio.h>
#include <string.h>
#define size 51



int main()
{
	char s1[size], s2[size], s3[size], result[size];
	scanf("%s %s %s", &s1, &s2, &s3);
	
	int len1 = strlen(s1), len2 = strlen(s2), len3 = strlen(s3);
	
	// shorter
	if (len1 < len2)
	{
		if (len1 < len3)
		{
			strcpy(result, s1);
		} else if (len1 == len3)
		{
			if (strcmp(s1, s3) > 0)  // >0 latter
			{
				strcpy(result, s1);
			} else {
				strcpy(result, s3);
			}
		} else
		{
			strcpy(result, s3);
		}
	} else if (len1 == len2)
	{
		if (len1 > len3)
		{
			strcpy(result, s3);
		} else if (len1 < len3)
		{
			if (strcmp(s1, s2) > 0)  // >0 latter
			{
				strcpy(result, s1);
			} else {
				strcpy(result, s2);
			}
		} else // equal length
		{
			if (strcmp(s1, s2) > 0)
			{
				if (strcmp(s1, s3) > 0)
				{
					strcpy(result, s1);
				} else
				{
					strcpy(result, s3);
				}
			} else if (strcmp(s1, s2) == 0)
			{
				if (strcmp(s1, s3) > 0)
				{
					strcpy(result, s1);
				} else 
				{
					strcpy(result, s3);
				}
			} else
			{
				if (strcmp(s2, s3) > 0)
				{
					strcpy(result, s2);
				} else
				{
					strcpy(result, s3);
				}
			}
		}
	} else    // len1 > len2
	{
		if (len2 < len3)
		{
			strcpy(result, s2);
		} else if (len2 > len3)
		{
			strcpy(result, s3);
		} else
		{
			if (strcmp(s2, s3) > 0)  // >0 latter
			{
				strcpy(result, s2);
			} else {
				strcpy(result, s3);
			}
		}
	}
	
	printf("%s\n", result);
	return 0;
}

