#include <stdio.h>  
#include <math.h>  
  
int main()  
{  
    int max, n, div, biggest_prime, is_prime;  
    scanf("%d", &max);  
      
    for (n = 2; n <= max; n ++)  
    {  
        for (div = 2, is_prime = 1; div < sqrt(n); div ++)  
        {  
            if (n % div == 0)  
            {  
                is_prime = 0;  
                break;  
            }  
        }  
        if (is_prime) biggest_prime = n;  
    }  
      
    printf("The max prime number is %d.\n", biggest_prime);  
    return 0;  
}
