#include <stdio.h>
#include <string.h>
#include <ctype.h>

int next_char(char *str, int *i)
{
	while (str[*i] == ' ') 
	{
		(*i) ++;
	}
	if ( (str[*i] >= 'A' && str[*i] <= 'Z') || (str[*i] >= 'a' && str[*i] <= 'z') )
	{
		return 1;
	} else if (str[*i] == ',')
	{
		return 2;
	} else if (str[*i] == '.')
	{
		return 3;
	}
	
	// character: 1;  comma: 2;  period: 3
}

void printChar(int *first_char, int *first_word, char *str, int i)
{
	if (str[i] == '.')
	{
		*first_char = 1;
	}
	
	if (*first_char == 1)
	{
		str[i] = toupper(str[i]);
		*first_char = 0;
	} else
	{
		str[i] = tolower(str[i]);
	}
	
	*first_word = 0;
	printf("%c", str[i]);
}



int count_period(char *str, int len)
{
	int i, period = 0;
	for (i = 0; i < len; i ++)
	{
		if (str[i] == '.')
		{
			period ++;
		}
	}
	return period;
}






int main()
{
	char str[256];
	fgets(str, 255, stdin);
	int len = strlen(str), i;
	int first_char = 1;
	int first_word = 1;
	str[len - 1] = '\0';
	
	int period = count_period(str, len);
	
	for (i = 0; i < len; i ++)
	{
		if (period == 0)
		{
			break;
		}
		
		if (str[i] == ' ')
		{
			if (next_char(str, &i) == 1)
			{
				if (first_word == 0)
				{
					printf(" ");
				}
				printChar(&first_char, &first_word, str, i);
			} else if (next_char(str, &i) == 2)
			{
				printf("%c", ',');
			} else if (next_char(str, &i) == 3)
			{
				printf("%c", '.');
				period --;
				first_char = 1;
			}
		} else if (str[i] == '.')
		{
			printf("%c", '.');
			period --;
			first_char = 1;
		} else
		{
			printChar(&first_char, &first_word, str, i);
		}
	}
	
	printf("\n");
	return 0;
}

