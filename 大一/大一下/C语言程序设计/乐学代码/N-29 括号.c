#include <stdio.h>

int main()
{
	int n, left, right, counter;
	scanf("%d", &n);
	char ch;
	getchar();
	
	int wrong = 0;
	for (left = 0, right = 0, counter = 0; counter < n; counter ++)
	{
		scanf("%c", &ch);
		if (ch == '[')
		{
			left ++;
		} else if (ch == ']')
		{
			right ++; 
		}
		if (right > left)
		{
			wrong = 1;
			break;
		}
	} 
	
	if ((n % 2) == 1 || left != right || wrong == 1)
	{
		printf("No\n");
	} else
	{
		printf("Yes\n");
	}
	return 0;
}
