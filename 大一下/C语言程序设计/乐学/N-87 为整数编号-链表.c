#include <stdio.h>    
struct nn  
{  
    int no;  
    int num;  
};  

typedef struct nn DATA;  
  
int number(char*, DATA[]);  
  
int main()  
{  
    DATA b[100];  
    char sa[500];  
    int i, n;  
    gets(sa);  
    n = number(sa, b);  
    for (i = 0; i < n; i++)  
        printf("%d %d\n", b[i].num, b[i].no);  
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
  
int number(char* str, DATA a[])  
{  
    int n = 0;  
    int i, k; 
    for (i = 0; str[i] != '\0';) {  
        int temp = 0;  
        if (i > 0) i++;  
        while (str[i] != ' ' && str[i] != '\0') {  
            temp = temp * 10 + (int)str[i] - (int)'0';  
            i++;  
        }  
        a[n].num = temp;  
        a[n].no = n + 1;  
        for (k = 0; k < n; k++) {  
            if (a[k].num > a[n].num) {  
                a[k].no++;  
                a[n].no--;  
            }  
        }  
        n++;  
    }  
    return n;  
}

