#include <stdio.h>  
#include <math.h>  
  
int spec_num(int num, int n)  
{  
    int num_store = num;  
    int sum = 0;  
    int last_dig;  
    while (num > 0)  
    {  
        last_dig = num % 10;  
        sum += pow(last_dig, n);  
        num /= 10;  
    }  
      
    if (sum == num_store)  
    {  
        return 1;  
    } else   
    {  
        return 0;   
     }   
}  
  
int main()  
{  
    int n;  
    int have_output = 0;  
    scanf("%d", &n);  
    int num = pow(10, n-1);  
      
    while (num < pow(10, n))  
    {  
        if (spec_num(num, n))  
        {  
            printf("%d\n", num);  
            have_output = 1;  
        }  
        num ++;  
    }  
      
    if (have_output == 0)  
    {  
        printf("No output.\n");  
    }  
       
    return 0;  
}
