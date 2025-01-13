#include <stdio.h>
#include <string.h>
#define size 10

unsigned long long trans(char *num, int len, int system);
int cToi(char num);
void sort(unsigned long long system[][2], int n);
void swap(unsigned long long *a, unsigned long long *b);


int main()
{	
	int n, i;
	char num[size];
	scanf("%d", &n); 
	unsigned long long system[n][2];
	for (i = 0; i < n; i ++)
	{
		system[i][0] = 0;
		system[i][1] = 0;
	}
	
	for (i = 0; i < n; i ++)
	{
		scanf("%s %llu", &num, &system[i][1]);
		int len = strlen(num);
		
		unsigned long long result = trans(num, len, system[i][1]);
		system[i][0] = result;
	}
	
	sort(system, n);
	
	for (i = 0; i < n; i ++)
	{
		printf("%llu %llu\n", system[i][0], system[i][1]);
	}
	return 0;
}


int cToi(char num)
{
	if (num >= '0' && num <= '9')
	{
		return num - '0';
	} else
	{
		return num - 'a' + 10;
	}
	
}


unsigned long long trans(char *num, int len, int system)
{
	unsigned long long result = 0;
	int digit = len - 1;
	
	int i, j;
	for (i = 0; i < len; i ++, digit --)
	{
		unsigned long long amount = cToi(num[i]);
		unsigned long long mul = 1;
		for (j = 0; j < digit; j ++)
		{
			mul *= system;
		}
		
		result += amount * mul;
	}
	
	return result;
}


void swap(unsigned long long *a, unsigned long long *b)
{
	unsigned long long t = *a;
	*a = *b;
	*b = t;
}


void sort(unsigned long long system[][2], int n)
{
	int i, j, k;
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n - i - 1; j ++)
		{
			if (system[j][1] < system[j + 1][1])
			{
				swap(&system[j][0], &system[j + 1][0]);
				swap(&system[j][1], &system[j + 1][1]);				
			 } 
		}
	}
	
	for (i = 0; i < n; i ++)
	{
		int same_sys_count = 1;
		
		for (j = i; j < n; j ++)
		{
			if (system[j][1] == system[j + 1][1])
			{
				same_sys_count ++;
			} else 
			{
				break;
			}
		}
		
		for (j = i; j < i + same_sys_count; j ++)
		{
			for (k = i; k < 2 * i + same_sys_count - j - 1; k ++)
			{
				if (system[k][0] < system[k + 1][0])
				{
					swap(&system[k][0], &system[k + 1][0]);
					swap(&system[k][1], &system[k + 1][1]);				
				} 	
			}
		}
		
		i += same_sys_count - 1;
	}
	
}
