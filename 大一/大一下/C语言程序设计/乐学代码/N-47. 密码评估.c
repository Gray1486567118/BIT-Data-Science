#include <stdio.h>
#include <string.h>

int main()
{
	int n, i;
	scanf("%d", &n);
	
	for (i = 0; i < n; i ++)
	{
		int len;
		scanf("%d", &len);
		char pw[len + 1];
		scanf("%s", &pw);
		int invalid = 1;
		int strength = 0;
		int has_alpha = 0;
		int has_digit = 0;
		int i;
		
		// validity
		if (len >= 6)
		{
			for (i = 0; i < len; i ++)
			{
				if (pw[i] >= '0' && pw[i] <='9') 
				{
					has_digit = 1;
				} else if ((pw[i] >= 'a' && pw[i] <='z') || (pw[i] >= 'A' && pw[i] <='Z'))
				{
					has_alpha = 1;
				}
				
				if (has_digit == 1 && has_alpha == 1)
				{
					invalid = 0;
					break;
				}
			}
		}
		
		// strength
		if (invalid == 1)
		{
			printf("INVALID\n");
		} else
		{
			// len
			if (len > 10) strength ++;
			
			// capital
			int capital = 0;
			int has_small = 0;
			int has_big = 0;
			for (i = 0; i < len; i ++)
			{
				if (pw[i] >= 'a' && pw[i] <='z')
				{
					has_small = 1;
				} else if (pw[i] >= 'A' && pw[i] <='Z')
				{
					has_big = 1;
				}
				
				if (has_big == 1 && has_small == 1)
				{
					strength ++;
					break;
				}
			}
			
			// special
			for (i = 0; i < len; i ++)
			{
				if (pw[i] < '0' || (pw[i] >'9' && pw[i] < 'A') || (pw[i] >'Z' && pw[i] < 'a') || pw[i] >'z')
				{
					strength ++;
					break;
				}
			}	
			
			// strength
			if (strength == 0)
			{
				printf("RUO\n");
			} else if (strength == 3)
			{
				printf("QIANG\n");
			} else 
			{
				printf("ZHONG\n");
			}
		}
	}
	return 0;
}

