#include <stdio.h>
#include <math.h>

int main()
{
	double x, y;
	int k = 1;
	scanf("%lf", &x);
	
	if (x < 0)
	{
		y = pow(2, x) +1;
	} else if (x >= 0 && x < 5)
	{
		y = sqrt(x + 4);
	} else if (x < 16)
	{
		y = 1.0 / (16.0 - x) + 32.0 / 11;
	} else
	{
		printf("Jaanai tcl!\n");
		k = 0;
	}
	
	if (k == 1)
	{
		printf("%.2f\n", y);
	}
	return 0;
}

