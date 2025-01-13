#include <stdio.h>

int main()
{
	double v, a, t, s;
	scanf("%lf %lf %lf", &v, &a, &t);
	
	s = v * t + 0.5 * a * t * t;
	printf("%.3f\n", s);
	return 0;
}
