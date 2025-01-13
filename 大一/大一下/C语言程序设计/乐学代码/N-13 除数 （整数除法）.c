#include <stdio.h>  
  
int main()  
{  
    int n, m, counter, down, up;  
    scanf("%d %d", &n, &m);  
      
    if (n / m == 1)  
    {  
        counter = n / 2;  
    } else  
    {  
        down = n / (n / m + 1) ;  
        up = n / (n / m) + 1;  
        counter = up - down - 1;  
    }  
      
    printf("%d\n", counter);  
    return 0;  
}
