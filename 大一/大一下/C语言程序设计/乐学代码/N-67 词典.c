#include <stdio.h>
#include <string.h>
#define MAX_STRINGS 2000

int common_pre_len(char dic[2000][11], int n);
void remove_pre(char dic[2000][11], int n, int pre_len);
int compare(char *word1, char *word2);
void swap(int *a, int *b);
void alph_sequence(char dic[2000][11], int n, int *sort);


int main()
{
	int n, i;
	scanf("%d", &n);
	
	char dic[2000][11];
	getchar();
	for (i = 0; i < n; i ++)
	{
		gets(dic[i]);
	}
	
	int pre_len = common_pre_len(dic, n);
	if (pre_len > 0)
	{
		remove_pre(dic, n, pre_len);	
	}
	
	int sort[n + 1];
	for (i = 0; i < n; i ++)
	{
		sort[i] = i;
	}
	
	alph_sequence(dic, n, sort);
	
	for (i = 0; i < n; i ++)
	{
		printf("%d\n", sort[i] + 1);
	}
	
	
	return 0;
}


int common_pre_len(char dic[2000][11], int n)
{
	int pre_len = 0;
	int min_len = strlen(dic[0]);
	
	int i, j;
	for (i = 1; i < n; i ++)
	{
		if (strlen(dic[i]) < min_len)
		{
			min_len = strlen(dic[i]);
		}
	}
	
	for (i = 0; i < n; i ++)
	{
		char same = dic[0][i];
		for (j = 0; j < min_len; j ++)
		{
			if (dic[j][i] != same)
			{
				return pre_len;
			}
		}
		pre_len ++;	
	}
	return pre_len;
}


void remove_pre(char dic[2000][11], int n, int pre_len)
{
	int i, j;
	for (i = 0; i < n; i ++)
	{
		int len = strlen(dic[i]);
		
		for (j = 0; j < len - pre_len; j ++)
		{
			if (len == pre_len)
			{
				dic[i][0] = '\0';
				break;
			}
			dic[i][j] = dic[i][j + pre_len];
		}
		
		dic[i][len - pre_len] = '\0';
	}
}


int compare(char *word1, char *word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	if (len1 == 0)    return 1;
	if (len2 == 0)    return 0;
	
	int min_len, shorter;
	if (len1 > len2)
	{
		min_len = len2;
		shorter = 2;
	} else if (len1 < len2)
	{
		min_len = len1;
		shorter = 1;
	} else 
	{
		min_len = len1;
		shorter = 0;
	}
	
	
	int i;
	for (i = 0; i < min_len; i ++)
	{
		if (word1[i] == word2[i])
		{
			if (i == min_len - 1)
			{
				if (shorter == 1)
				{
					return 1;
				} else if (shorter == 2)
				{
					return 0;
				} else
				{
					return -1;
				}
			}
			continue;
		} else if (word1[i] < word2[i])
		{
			return 1;
		} else
		{
			return 0;
		}
	}	
}


void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


void alph_sequence(char dic[2000][11], int n, int *sort)
{
	int i, j;
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n - i - 1; j ++)
		{
			if (compare(dic[j], dic[j + 1]) == 0)
			{
				swap(&sort[j], &sort[j + 1]);
				
				
				char swapper[11];
				strcpy(swapper, dic[j]);
				strcpy(dic[j], dic[j + 1]);
				strcpy(dic[j + 1], swapper);
			}
		}
	}
}

