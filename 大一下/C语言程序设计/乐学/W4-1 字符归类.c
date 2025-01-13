#include <stdio.h>

int main()
{
	char ch;
	scanf("%c", &ch);
	
	if (48 <= ch && ch <= 57)
	{
		printf("Digital.\n");
	} else if (65 <= ch && ch <= 90)
	{
		printf("Upper case letter.\n");
	} else if (97 <= ch && ch <= 122)
	{
		printf("Lower case letter.\n");
	} else
	{
		printf("Other.\n");
	}

	return 0;
}
