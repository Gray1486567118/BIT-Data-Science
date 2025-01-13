#include <stdio.h>

int main()
{
	int a11, a12, a21, a22, det;
	scanf("%d %d", &a11, &a12);
	scanf("%d %d", &a21, &a22);
	
	det = a11 * a22 - a12 * a21;
	printf("determinant=%d\n", det);
	return 0;
 } 
