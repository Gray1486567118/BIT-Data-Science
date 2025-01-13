#include <stdio.h>

int main()
{
	int c1, c2;
	scanf("%c%c", &c1, &c2);
	
	int high = ((c1>>4) & (c2>>4)) <<4;
	int low = (c1 % 16) ^ (c2 % 16);
	int output = high + low;
	printf("%c\n", output);
	
	return 0;
}
