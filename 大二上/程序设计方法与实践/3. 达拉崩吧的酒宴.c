#include <stdio.h>
#include <math.h>
#define ll long long

int min_mise(ll n);

int main() {
	int i, j, t;
	ll n;
	scanf("%d", &t);
	
	for (i = 0; i < t; i ++) {
		scanf("%lld", &n);
		
		int ans = ceil(log2(n));
		printf("%d\n", ans);
	}
	
	return 0;
}


