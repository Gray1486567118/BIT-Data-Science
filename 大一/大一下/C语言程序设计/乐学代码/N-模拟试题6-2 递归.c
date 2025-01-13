#include <stdio.h>  
#include <stdlib.h>  

int f(int n, int m);

int main()  
{  
    int n, m;  
    scanf("%d%d",&n,&m);  
    printf("%d\n",f(n,m));  
    system("pause");  
}  

int f(int n, int m) {
	if (n > m) {
		if (m > 0 && n < 4) {
			return 1;
		} else if (m > 4 && (m % 2 == 0)) {
			return f(n, m - 1) + f(n, m - 3);
		} else if (m > 4 && (m % 2 == 1)) {
			return f(n, m - 2) + f(n - 4, m);
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}
