#include <stdio.h>

int main()
{
	double r,h;
	double pi = 3.1415926;
	scanf("%lf%lf",&r,&h);
	printf("s=%.2f,v=%.2f\n",2*pi*r*h,pi*r*r*h);
	return 0;
}
