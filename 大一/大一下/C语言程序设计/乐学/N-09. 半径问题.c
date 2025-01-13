#include <stdio.h>

int main()
{
	int m, q, v, b, elec, charge;
	scanf("%d %d %d %d", &m, &q, &v, &b);
	scanf("%d %d", &elec, &charge);
	
	double r = (double)m * v / q / b;
	int dire = elec ^ charge;
	printf("%.2f %d\n", r, dire);
	return 0;
} 
