#include <stdio.h>

void trans(char *word, int len)
{
	int i;
	for (i = 0; i < len; i ++)
	{
		if (word[i] <= 'G' || (word[i] >= 'a' && word[i] <= 'g')) word[i] += 26;
		word[i] -= 7;
	}
 } 

int main()
{
	int len;
	scanf("%d", &len);
	char word[len + 1];
	scanf("%s", &word);
	
	trans(word, len);
	printf("%s\n", word);
	return 0;
}

