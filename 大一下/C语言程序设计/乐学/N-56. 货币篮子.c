#include <stdio.h>
#include <string.h>
#include <math.h>

double inflation (double x, double rate, int year)
{
	return x / pow(1 + rate, year);
}


double trans(char *cur, double x)
{
	if (strcmp(cur, "CNY") == 0)
	{
		return x;
	} else if (strcmp(cur, "USD") == 0)
	{
		return x / 6.48;
	} else if (strcmp(cur, "JPY") == 0)
	{
		return x / 0.061;
	} else if (strcmp(cur, "EUR") == 0)
	{
		return x / 7.82;
	} else if (strcmp(cur, "GBP") == 0)
	{
		return x / 9.02;
	}
}


int main()
{
	int year;
	double inf_rate, x;
	char s[4];
	
	scanf("%d %lf", &year, &inf_rate);
	scanf("%lf", &x);
	scanf("%s", &s);
	
	double x_prior = inflation(x, inf_rate, year);
	double x_trans = trans(s, x_prior);
	
	printf("%.2f\n", x_trans); 
	return 0;
}

