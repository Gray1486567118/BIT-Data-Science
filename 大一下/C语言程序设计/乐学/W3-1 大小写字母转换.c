#include <stdio.h>  
  
int main()  
{  
    char c;  
    scanf("%c", &c);  
    int ascll = (int)c;  
    int swapper = 'a' - 'A';  
      
    if (ascll >= 65 && ascll <= 90)  
    {  
        c = c + swapper;  
    } else if (ascll >= 97 && ascll <= 122)  
    {  
        c = c - swapper;  
    }   
      
    printf("%c\n", c);  
      
    return 0;  
}  
