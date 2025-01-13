#include <stdio.h>

int main()
{
	char name[100];
	gets(name);
	printf("Hi,there,%s!\n", name);
	return 0;
}
