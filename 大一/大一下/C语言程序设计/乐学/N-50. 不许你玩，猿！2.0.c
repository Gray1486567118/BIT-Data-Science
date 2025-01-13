#include <stdio.h>

int swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int pos(int *seq, int i, int n)
{
	int position;
	for (position = i + 1; position < n; position ++)
	{
		if (seq[position] == i + 1)
		break;
	}
	return position;
}


int count(int *seq, int n)
{
	int i, j, inversion = 0;
	for (i = 0; i < n; i ++)
	{
		if (seq[i] == i + 1)
		{
			continue;
		} else
		{
			int position = pos(seq, i, n);
			swap(&seq[i], &seq[position]);
			inversion ++;
		}
	 } 
	
	return inversion;
}

int main()
{
	int n;
	scanf("%d", &n);
	int seq[n], i;
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &seq[i]);
	}
	
	int inversion = count(seq, n);
	printf("%d\n", inversion);
	return 0;
}

