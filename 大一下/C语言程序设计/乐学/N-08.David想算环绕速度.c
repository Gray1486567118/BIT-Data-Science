#include <stdio.h>
#include <math.h>

int main()
{
	double m, r, v;
	const double G = 6.67e-11;
	scanf("%lf %lf", &m, &r);
	
	v = sqrt(G * m / r);
	printf("%e\n", v);
	
	return 0;
}
