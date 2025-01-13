#include <stdio.h>

int main()
{
	int x1, x2, y1, y2, z1, z2;
	scanf("%d %d %d", &x1, &y1, &z1);
	scanf("%d %d %d", &x2, &y2, &z2);
	int v1 = x1 * y1 * z1;
	int v2 = x2 * y2 * z2;
	
	double chocs = (x1 / x2) * (y1 / y2) * (z1 / z2);
	double ratio = chocs * v2 / v1 * 100;
	
	printf("%.2f%%\n", ratio);
	
	return 0;
}
