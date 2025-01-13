#include <stdio.h>

int main()
{
	double v, x1, x2, x3, s, t, T;
	scanf("%lf %lf %lf %lf %lf %lf", &v, &x1, &x2, &x3, &s, &t);
	
	double s1 = x3 - s;
	double s2 = t - x1;
	if (s1 > s2)
	{
		T = s1 / v;
	} else
	{
		T = s2 / v;
	}
	
	printf("%.1f\n", T);
	return 0;
}
