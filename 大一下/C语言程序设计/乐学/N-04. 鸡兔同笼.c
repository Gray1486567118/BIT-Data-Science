#include <stdio.h>

int main()
{
	int head, feet, chick, rabbit;
	scanf("%d %d", &head, &feet);
	
	chick = head;
	rabbit = 0;
	while ((chick * 2 + rabbit * 4) != feet)
	{
		chick --;
		rabbit ++;
	}
	
	printf("%d %d\n", chick, rabbit);
	return 0;
}
