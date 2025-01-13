#include <stdio.h>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

double bigger_than_400(double expected, double acceleration, double real)
{
	if (expected > 400)
	{
		if (real > 400)
		{
			real += acceleration * 0.8;
		} else
		{
			real = 400 + (expected - 400) * 0.8;
		}
	} else
	{
		real = expected;
	}
	return real;
}

int main()
{
	int a, b, c;
	double expected, real, acceleration;
	scanf("%d %d %d", &a, &b, &c); 
	real = a;
	
	if (b != 0)
	{
		expected = (double) a * (100 + b) / 100;
		acceleration = expected - a;
		real = bigger_than_400(expected, acceleration, real);
	}

	if (c != 0)
	{
		expected = real + c;
		acceleration = c;
		real = bigger_than_400(expected, acceleration, real);
	}
	
	printf("%d\n", (int)real);
	return 0;
}
