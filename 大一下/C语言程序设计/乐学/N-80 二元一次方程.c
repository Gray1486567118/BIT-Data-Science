#include <stdio.h>    
    
long long int A, B, C, x = 1, y = 0;    
    
long long int gcd(long long int a, long long int b) { return b == 0 ? a : gcd(b, a % b); }    
void solve(long long int a, long long int b)    
{    
    if (b != 0) {    
        solve(b, a % b);    
        long long int tx = x;    
        x = y;    
        y = tx - a / b * y;    
    }    
}    
    
int main()    
{    
    scanf("%lld %lld %lld", &A, &B, &C);    
    long long int temp = gcd(A, B);    
    if (C % temp == 0) {    
        A /= temp; B /= temp; C /= temp;    
        solve(A, B);    
        x *= C; y *= C;    
        if (x > 0)     
            for (; x - B > 0; x -= B, y += A);    
        else     
            for (; x <= 0; x += B, y -= A);    
        printf("%lld %lld\n", x, y);    
    }    
    else printf("No solution\n"); 
