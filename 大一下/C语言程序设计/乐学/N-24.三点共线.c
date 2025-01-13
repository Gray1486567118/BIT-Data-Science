#include <stdio.h>

int main()
{
	int x1, y1, x2, y2, x3, y3;
	scanf("(%d,%d)(%d,%d)(%d,%d)", &x1, &y1, &x2, &y2, &x3, &y3);
	
	if ( ((x1 == x2) && (x2 == x3)) || ( (y1 == y2) && (y2 == y3) ) )
	{
		printf("Yes\n");
	} else if ( ((double) (x2 - x1) / (y2 - y1)) == ((double) (x3 - x1) / (y3 - y1)) )
	{
		printf("Yes\n");
	} else
	{
		printf("No\n");
	}
	return 0;
}
