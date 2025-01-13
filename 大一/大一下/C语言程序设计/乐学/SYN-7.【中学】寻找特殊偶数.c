#include <stdio.h>  
  
int main()  
{  
    int min, max, num, num_backup, a, b, c, d;  
    int counter = 0;  
    scanf("%d %d", &min, &max);  
      
    while (min != 0)  
    {  
        if (min < 1000 || max < min)  
        {  
            printf("Error\n");  
        } else  
        {  
            if (min % 2 == 1)  
            {  
                min ++;  
            }  
            for(num = min; num <= max; num += 2)  
            {  
                num_backup = num;  
                a = num_backup % 10;  
                num_backup /= 10;  
                b = num_backup % 10;  
                num_backup /= 10;  
                c = num_backup % 10;  
                num_backup /= 10;  
                d = num_backup % 10;  
                if (a!=b && a!=c && a!=d && b!=c && b!=d && c!=d)  
                {  
                    counter ++;  
                    printf("%d  ", num);  
                }  
            }  
            printf("\ncounter=%d\n", counter);  
        }  
        scanf("%d %d", &min, &max);  
        counter = 0;  
    }  
  
    return 0;  
}
