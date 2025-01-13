#include <stdio.h>
#define mod 998244353

int main()
{
	long long int v, t, x, ans;
	scanf("%lld %lld %lld", &v, &t, &x);

	for (ans = v; t > 0; t >>= 1)
	{
		if (t & 1)
		{
			ans *= x;
			ans %= mod;
		}
		
		x *= x;
		x %= mod;
	}
	
	printf("%lld\n", ans);
	return 0;	
}
