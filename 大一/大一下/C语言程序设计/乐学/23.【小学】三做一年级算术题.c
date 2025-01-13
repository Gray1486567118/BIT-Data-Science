#include <stdio.h>

int main()
{
	char input, big, small, op;
	int opr1, opr2, result;
	
	input = getchar();
	big = input;
	small = input;
	
	while ((input = getchar()) != '=')
	{
		if (input == 44)
		{
			continue;
		} else if (input > 47)
		{
			if (input > big)
			{
				big = input;
			}
			if (input < small)
			{
				small = input;
			}
		} else 
		{
			op = input;	
		}
	}
	
	opr1 = big - 48;
	opr2 = small - 48;
	
	if (opr2 == 0 && op == 47)
	{
		printf("Error!\n");
	} else
	{
		if (op == 43)
		{
			result = opr1 + opr2;
		} else if (op == 45)
		{
			result = opr1 - opr2;
		} else if (op == 42)
		{
			result = opr1 * opr2;
		} else if (op == 47)
		{
			result = opr1 / opr2;
		} else if (op == 37)
		{
			result = opr1 % opr2;
		}
		printf("%d%c%d=%d\n", opr1, op, opr2, result);
	}
	
	return 0;
}
