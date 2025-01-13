#include<stdio.h>  
  
int main()  
{  
    int n;  
    scanf("%d",&n);  
      
    int line=0;  
    int i;  
    printf("*");  
    for(i=0;i<n;i++) printf(" ");  
    for(i=0;i<n;i++) printf("*");  
    printf(" *");  
    //for(i=0;i<n-1;i++) printf(" ");  
    printf("\n");  
    line++;  
    while(line++<n-1){  
        printf("*");  
        for(i=0;i<n;i++) printf(" ");  
        printf("*");  
        for(i=0;i<n-2;i++) printf(" ");  
        printf("* *");  
        //for(i=0;i<n-1;i++) printf(" ");  
        printf("\n");  
    }  
    for(i=0;i<n;i++) printf("*");  
    printf(" ");  
    for(i=0;i<n;i++) printf("*");  
    printf(" ");  
    for(i=0;i<n;i++) printf("*");  
    printf("\n");  
      
    return 0;  
}
