#include <stdio.h>
#include <math.h>

double cal_pi(double prec)
{
	double pi = 0;
	int i = 1;
	double divider = 1;
	while (fabs(4.0 / divider) >= prec)
	{
		pi += 4.0 / divider * i;
		divider += 2;
		i = -i;
	}
	return pi;
}


int main()
{
	double precision;
	scanf("%lf", &precision);
	
	double pi = cal_pi(precision);
	printf("%.4lf\n", pi);
	return 0;
}

