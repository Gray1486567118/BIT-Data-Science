#include <stdio.h>  
#include <math.h>  
  
int main()  
{  
    int a, b, c, dis;  
    double x1, x2, real, imag;  
    scanf("%d %d %d", &a, &b, &c);  
      
    if (a == 0 && a == b)  
    {  
        printf("Input error!\n");  
    } else if (a == 0)  
    {  
        x1 = (double)(-c) / b;  
        printf("x=%f\n", x1);  
    } else  
    {  
        dis = b * b - 4 * a * c;  
        if (dis == 0)  
        {  
            x1 = (double)(-b) / (2 * a);  
            printf("x1=x2=%f\n", x1);  
        } else if (dis > 0)  
        {  
            x1 = (double)(-b + sqrt(dis)) / (2 * a);  
            x2 = (double)(-b - sqrt(dis)) / (2 * a);  
            printf("x1=%f\nx2=%f\n", x1, x2);  
        } else  
        {  
            real = (double)(-b) / (2 * a);  
            imag = (double)sqrt(-dis) / (2 * a);  
            if (real == 0)  
            {  
                printf("x1=%fi\nx2=-%fi\n", imag, imag);  
            } else  
            {  
                printf("x1=%f+%fi\nx2=%f-%fi\n", real, imag, real, imag);  
            }  
        }  
    }  
      
    return 0;  
}  
