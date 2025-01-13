#include <stdio.h>

int main()
{
	unsigned long long n1, n2;
	scanf("%llu %llu", &n1, &n2);
	
	unsigned long long an1 = 34ULL + 18ULL * (n1 - 4ULL) + 2ULL * (n1 - 4ULL) * (n1 - 5ULL);
	unsigned long long an2 = 34ULL + 18ULL * (n2 - 4ULL) + 2ULL * (n2 - 4ULL) * (n2 - 5ULL);
	printf("%llu %llu\n", an1, an2);
	return 0;
}
