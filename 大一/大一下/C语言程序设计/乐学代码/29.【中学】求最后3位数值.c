#include <stdio.h>

int main()
{
	int a, n, counter, output, big_than_1000;
	scanf("%d %d", &a, &n);
		
	for (counter = 0, output = 1, big_than_1000 = 0; counter < n; counter ++)
	{
		output *= a;
		if (output > 1000)
		{
			big_than_1000 = 1;
			output %= 1000;
		} 
	}
	
	if (big_than_1000 == 1)
	{
		printf("The last 3 numbers is %03d.\n", output);
	} else
	{
		printf("The last 3 numbers is %d.\n", output);
	}
	return 0;
}
