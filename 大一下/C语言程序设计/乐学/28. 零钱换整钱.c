#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	
	double h = 11.25 * n;
	double num_1 = h / 1.8;
	double num_5 = h / 1.5;
	double num_10 = h / 2.0;
	if ((num_1 == (int) num_1) && (num_5 == (int) num_5) && (num_10 == (int) num_10))
	{
		printf("%d,%d,%d\n", (int) num_1, (int) num_5, (int) num_10);
	} else
	{
		printf("No change.\n");
	}
	return 0;
}
