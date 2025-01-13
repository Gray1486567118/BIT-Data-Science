#include <stdio.h>
#define size 5000

void input(int *a, int n);
unsigned long long min_consumption(int *energy, int *times, int n, int S);
void swap(int *a, int *b);

int main()
{
	int n, S, i;
	scanf("%d %d", &n, &S);
	int energy[size], times[size];
	
	input(energy, n);
	input(times, n);
	
	unsigned long long consumption = min_consumption(energy, times, n, S);
	printf("%llu\n", consumption);
	
	return 0;
}


void input(int *a, int n)
{
	int i;
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &a[i]); 
	 } 
}

unsigned long long min_consumption(int *energy, int *times, int n, int S)
{
	unsigned long long consumption = 0;
	
	unsigned long long beat = 0;
	int i, j;
	for (i = 0; i < n; i ++)
	{
		for (j = 0; j < n - i - 1; j ++)
		{
			if (times[j] < times[j + 1])
			{
				swap(&times[j], &times[j + 1]);
				swap(&energy[j], &energy[j + 1]);
			}
		}
	}
	
	int time_of_wipe = 0;
	for (i = 0; i < n; i ++)
	{
		beat += energy[i];
		if (beat > S)
		{
			time_of_wipe = times[i];
			break;
		}
	}
	
	consumption += (unsigned long long) S * time_of_wipe;

	
	for (j = 0; j < i; j ++)
	{
		consumption += (unsigned long long) energy[j] * (times[j] - time_of_wipe);
	}
	
	return consumption;
}


void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


