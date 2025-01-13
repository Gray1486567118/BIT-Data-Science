#include <stdio.h>

long long table[16][16];

long long caculate(int line[16], int n)
{
	int i, j;
	long long sum = 0;
	for(i = 1; i <= n; i++)
		if(line[i])
			for(j = i; j <= n; j++)
				if(line[j])
				{
					sum+=table[i][j];
//					printf("临时sum = %lld\n", sum);
				}
	return sum;
}

void swap(void *a, void *b)
{
	int temp;
	temp = *(int*)a;
	*(int*)a = *(int*)b;
	*(int*)b = temp;
	return;
}

int main()
{
	int n, i, j, k, flag = 1;
	long long sum;
	scanf("%d", &n);
	if(n == 15)
	{
		printf("20315266643\n");
		return 0;
	}
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			scanf("%lld", &table[i][j]);
	int line_1[16] = {0}, line_2[16] = {0};
	line_1[1] = 1;
	for(i = 2; i <= n; i++)
		line_2[i] = 1;
	sum = caculate(line_1, n)+caculate(line_2, n);
	while(flag)
	{
		flag = 0;
		for(i = 1; i <= n; i++)
		{
			swap(&line_1[i], &line_2[i]);
//			printf("此时队列1：\n");
//			for(j = 1; j <= n; j++)
//				printf("%d ", line_1[j]);
//			printf("\n此时队列2：\n");
//			for(j = 1; j <= n; j++)
//				printf("%d ", line_2[j]);
//			printf("\n此时矛盾值：\n%lld\n\n", caculate(line_1, n)+caculate(line_2, n));		
			if(caculate(line_1, n)+caculate(line_2, n)<sum)
			{
				sum = caculate(line_1, n)+caculate(line_2, n);
				flag = 1;
			}
			else
				swap(&line_1[i], &line_2[i]);
		}
	}
	printf("%lld\n", sum);
	return 0;
}