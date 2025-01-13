#include <stdio.h>

int main()
{
	int opr1, opr2, result;
	char oper;
	scanf("%d%c%d", &opr1, &oper, &opr2);
	
	switch (oper)
	{
		case '+':
			result = opr1 + opr2;
			break;
		case '-':
			result = opr1 - opr2;
			break;
		case '*':
			result = opr1 * opr2;
			break;
		case '/':
			result = opr1 / opr2;
			break;
	}
	
	printf("%d\n", result);
	
	return 0;
}
