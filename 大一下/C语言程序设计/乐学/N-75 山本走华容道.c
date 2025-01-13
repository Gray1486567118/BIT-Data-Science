#include <stdio.h>    
    
int main()     
{    
    int t;    
    scanf("%d", &t);    
    for (int i = 0; i < t; i++) {    
        int m, n, x, y, win = 0;    
        scanf("%d %d %d %d", &m, &n, &x, &y);    
        int a = x - 1, b = m - x, c = y - 1, d = n - y;    
        int ans = a ^ b ^ c ^ d;    
        ans ? printf("win\n") : printf("lose\n");    
    }    
}
