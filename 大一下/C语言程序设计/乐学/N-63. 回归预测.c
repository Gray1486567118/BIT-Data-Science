#include <stdio.h>
#define size 50000

void input(double *a, int n);
double sum(double *a, int n);
void linear_regression(double *x, double *y, int n, double *b_a);
double predict(double *b_a, double p);


int main()
{
	int n, i;
	double p;
	
	while (scanf("%d %lf", &n, &p) != EOF)
	{
		double ori_x[size], ori_y[size];
		double b_a[2] = {0, 0};
		input(ori_x, n);
		input(ori_y, n);
		
		linear_regression(ori_x, ori_y, n, b_a);
		double predict_y = predict(b_a, p);
		
		if (100 * b_a[0] == 0 && 100 * b_a[1] == 0) 
		{
			printf("y=0 predict=%.2lf\n", predict_y);
		} else if ((int) (100 * b_a[0]) == 0)
		{
			printf("y=%.2lf predict=%.2lf\n", b_a[1], predict_y);
		} else if ( (int) (100 * b_a[1]) == 0)
		{
			printf("y=%.2lfx predict=%.2lf\n", b_a[0], predict_y);
		} else if (b_a[1] < 0)
		{
			printf("y=%.2lfx%.2lf predict=%.2lf\n", b_a[0], b_a[1], predict_y);
		} else
		{
			printf("y=%.2lfx+%.2lf predict=%.2lf\n", b_a[0], b_a[1], predict_y);
		}
	} 
	return 0;
}


void input(double *a, int n)
{
	int i; 
	for (i = 0; i < n ; i ++)
	{
		scanf("%lf", &a[i]);
	}
}


void linear_regression(double *x, double *y, int n, double *b_a)
{
	double a, b;
	double avg_x = 1.0 * sum(x, n) / n;
	double avg_y = 1.0 * sum(y, n) / n;
	
	double b1 = 0, b2 = 0;  // ·Ö×Ó ·ÖÄ¸
	int i;
	for (i = 0; i < n; i ++)
	{
		b1 += (x[i] - avg_x) * (y[i] - avg_y);
	}
	
	for (i = 0; i < n; i ++)
	{
		b2 += (x[i] - avg_x) * (x[i] - avg_x);
	}
	
	b = b1 / b2;
	a = avg_y - b * avg_x;
	
	b_a[0] = b;
	b_a[1] = a;
}


double sum(double *a, int n)
{
	int i; 
	double result = 0;
	for (i = 0; i < n ; i ++)
	{
		result += a[i];
	}
	
	return result;
}


double predict(double *b_a, double p)
{
	return b_a[0] * p + b_a[1];
}
