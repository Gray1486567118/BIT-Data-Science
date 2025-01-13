#include <stdio.h>
#include <math.h>

double max(double a, double b)
{
	return (a > b) ? a : b;
}

int main()
{
	double m1, m2, W1, W2;
	scanf("%lf %lf %lf %lf", &m1, &m2, &W1, &W2);
	
	double v1 = sqrt(2 * W1 / m1);
	double v2 = sqrt(2 * W2 / m2);
//	printf("%f %f\n", v1, v2);
	
	double u2_1 = 2 * m1 / (m1 + m2) * v1 + (m2 - m1) / (m1 + m2) * v2;
	double u2_2 = 2 * m1 / (m1 + m2) * v1 - (m2 - m1) / (m1 + m2) * v2;
	
	double u2 = max(u2_1, fabs(u2_2));
	
	double I = m2 * max(v2, fabs(u2));
	printf("%.2f\n", I);
	return 0;
}
