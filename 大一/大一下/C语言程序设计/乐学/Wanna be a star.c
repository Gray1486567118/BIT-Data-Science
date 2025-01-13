#include <stdio.h>

int main()
{
	int max, min, input;
	scanf("%d", &input);
	int sum = input;
	max = input;
	min = input;
	
	int counter;
	for (counter = 0; counter < 9; counter ++)
	{
		scanf("%d", &input);
		if (input > max) max = input;
		if (input < min) min = input;
		sum += input;
	}
	sum = sum - max - min;
	
	printf("Canceled Max Score:%d\n", max);
	printf("Canceled Min Score:%d\n", min);
	printf("Average Score:%d\n", sum / 8) ;
	
	return 0;
}
