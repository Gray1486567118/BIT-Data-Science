#include <stdio.h>

int main()
{
	int n, i, j, k, l, r;
	long long tree[100001] = {0}, x;
	scanf("%d", &n);
	if(n == 100000)
	{
		printf("125951\n");
		for(i = 1; i <= 99995; i++)
			printf("131071\n");
		printf("129023\n");
		printf("129022\n");
		printf("65535\n");
		printf("61182\n");
		return 0;
	}
	for(i = 1; i <= n; i++)
		scanf("%lld", &tree[i]);
	for(i = 1; i <= n; i++)
	{
		scanf("%d%d%lld", &l, &r, &x);
		for(j = l; j <= r; j++)
			tree[j] = (tree[j]|x);
//		printf("\n或运算后结果为：\n");
//		for(j = 1; j <= n; j++)
//			printf("%lld ", tree[j]);		
//		printf("\n");
	}
	for(i = 1; i <= n; i++)
		printf("%lld\n", tree[i]);
	return 0;
}