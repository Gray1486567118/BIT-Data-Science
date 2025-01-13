#include <stdio.h>
#include <math.h>
#define pow2(x) ((x) * (x))

int main()
{
	int n, counter;
	scanf("%d", &n);
	
	for (counter = 0; counter < n; counter ++)
	{
		double x0, y0, r, x1, y1;
		scanf("%lf %lf %lf %lf %lf", &x0, &y0, &r, &x1, &y1);
		long long scaled_x0 = round(x0 * 10000); 
		long long scaled_y0 = round(y0 * 10000); 
		long long scaled_r  = round(r  * 10000); 
		long long scaled_x1 = round(x1 * 10000); 
		long long scaled_y1 = round(y1 * 10000); 

		long long D = pow2(scaled_x1 - scaled_x0) + pow2(scaled_y1 - scaled_y0);
		long long R = pow2(scaled_r);
		if (D > R)
		{
			printf("NO\n");
		} else
		{
			printf("YES\n");
		}	
	}
	return 0;
}
