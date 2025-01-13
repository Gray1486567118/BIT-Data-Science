#include <stdio.h>    
#include <string.h>    
    
void swap(char* a, char* b)    
{    
    char temp[100];    
    for (int i = 0; i <= strlen(a); i++)    
        temp[i] = a[i];    
    for (int i = 0; i <= strlen(b); i++)    
        a[i] = b[i];    
    for (int i = 0; i <= strlen(temp); i++)    
        b[i] = temp[i];    
}    
    
int main()    
{    
    char a[100], b[100];    
    scanf("%s %s", a, b);    
    swap(a, b);    
    printf("%s\n%s\n", a, b);    
}
