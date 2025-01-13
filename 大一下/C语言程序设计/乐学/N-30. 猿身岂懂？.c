//#include <stdio.h>
//#include <math.h>
//
//int weiyu(int low, int up);
//
//int main()
//{
//	int n, counter, low, up, output;
//	scanf("%d", &n);
//	
//	for (counter = 0; counter < n; counter ++)
//	{
//		scanf("%d %d", &low, &up);
//		output = weiyu(low, up);
//		printf("%d\n", output);
//	}
//	return 0;
//}
//
//
//int weiyu(int low, int up)
//{
//	long long int two_n = 1; // 2 ^ n
//	int i = 1;
//	while (two_n <= up)
//	{
//		two_n *= 2;
//		i ++;
//	}
//	two_n /= 2;
//	i --;
//		
//	if (two_n > low)
//	{
//		return 0;
//	} else
//	{
//		int first_digit = (int) pow(2, i - 1);
//		low = low % first_digit;
//		up = up % first_digit;
//		return first_digit + weiyu(low, up);
//	}
//}

#include <stdio.h>

int commonPrefix(int x, int y) {
    int shift = 0;
    while (x != y) {
        x >>= 1;
        y >>= 1;
        shift++;
    }
    return (x << shift);
}

int main() {
    int n;
    scanf("%d", &n); // 读取测试用例数量

    while (n--) {
        int L, R;
        scanf("%d %d", &L, &R); // 读取范围[L, R]

        int result = commonPrefix(L, R);

        printf("%d\n", result); // 输出结果
    }

    return 0;
}

