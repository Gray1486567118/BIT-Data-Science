#include <stdio.h>

int main()
{
	double s, p, q;
	scanf("%lf %lf %lf", &s, &p, &q);
	
	double v = s * 0.1 + (100 - p) / 100 * s * 0.9 + p / 100 * (s * 0.9) * q / 100;
	printf("%.2f\n", v); 
	
	
	return 0;
}
