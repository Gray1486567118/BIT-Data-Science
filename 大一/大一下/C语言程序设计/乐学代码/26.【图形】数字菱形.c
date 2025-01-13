#include <stdio.h>
#include <math.h>

int main()
{
	int n;
	scanf("%d", &n);
	int row = 2 * n - 1;
	
	int k, num;
	for (k = 1; k <= row; k ++)
	{
		int space = abs(k - n) * 2;
		int counter;
		for (counter = 0; counter < space; counter ++)
		{
			printf(" ");
		 } 
		for (num = n; num >= ((k <= n) ? (n-k+1) : (k-n+1)); num --)
		{
			printf("%-2d", num);
		}
		num += 2;
		while (num <= n)
		{
			printf("%-2d", num);
			num ++;
		}
		printf("\n");
	}
	
	return 0;	
}
