#include <stdio.h>

int main()
{
	int type, counter;
	double degree;
	
	for (counter = 0; counter < 3; counter ++)
	{
		scanf("%d %lf", &type, &degree);
		
		if (type == 1)
		{
			degree = (degree - 32) / 1.8;
			printf("The Centigrade is %.2f\n", degree);
		} else if (type == 2)
		{
			degree = degree * 1.8 + 32;
			printf("The Fahrenheit is %.2f\n", degree);
		} else
		{
			printf("Wrong input!\n");
		}
	}
	return 0;
}
