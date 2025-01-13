#include <stdio.h>
#include <math.h>

int cal_gcd(int a, int b)
{
	a = abs(a);
	b = abs(b);
	if (b == 0)
	{
		return a;
	}
	return cal_gcd(b, a%b);
}



int main()
{
	int num1, den1, num2, den2, gcd, num, den;
	char cal;
	scanf("%d/%d %c %d/%d", &num1, &den1, &cal, &num2, &den2);
	
	if (cal == '+')
	{
		num = num1 * den2 + num2 * den1;
		den = den1 * den2;
	} else if (cal == '-')
	{
		num = num1 * den2 - num2 *den1;
		den = den1 * den2;
	} else if (cal == '*')
	{
		num = num1 * num2 ;
		den = den1 * den2;
	} else if (cal == '/')
	{
		num = num1 * den2 ;
		den = den1 * num2;
	}
	
	gcd = cal_gcd(num, den);
	num /= gcd;
	den /= gcd;
	if (num == 0)
	{
		printf("%d/%d %c %d/%d = 0\n", num1, den1, cal, num2, den2);
	} else if(den == 1)
	{
		printf("%d/%d %c %d/%d = %d\n", num1, den1, cal, num2, den2, num);
	} else
	{
		printf("%d/%d %c %d/%d = %d/%d\n", num1, den1, cal, num2, den2, num, den);
	}

	return 0;
}

