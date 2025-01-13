#include <stdio.h>
#include <string.h>

void bubble(char *array, int len);



int main()
{
	char array[100];
	scanf("%s", array);
	
	int len = strlen(array);
	bubble(array, len);
	
	return 0;
}



void bubble(char *array, int len)
{
	int i, j;
	for (i = 0; i < len - 1; i ++)
	{
		for (j = 0; j < len - 1 - i; j ++)
		{
			if (array[j] < array[j + 1])
			{
				char t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}
	
	printf("%s\n", array);
}
