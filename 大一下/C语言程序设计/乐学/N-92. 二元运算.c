#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>    
    
char G[3000] = { 0 }, lamda, input[100];    
int num = 0, arr[100];    
    
int F(int a, int b, char l)    
{    
    if (l == '^') return a ^ b;    
    if (l == '|') return a | b;    
}    
    
int main()    
{    
    gets(input);    
    for (int i = 0; i < strlen(input); i++) {    
        if (input[i] == '-') break;    
        int temp = 0;    
        while (input[i] >= '0' && input[i] <= '9') {    
            temp = temp * 10 + input[i] - '0';    
            i++;    
        }    
        G[temp] = 1;    
        arr[num] = temp;    
        num++;    
    }    
    scanf("%c", &lamda);    
    for (int i = 0; i < num; i++)    
        for (int j = 0; j <= i; j++)    
            G[F(arr[i], arr[j], lamda)] = 1;    
    int temp;    
    scanf("%d", &temp);    
    printf("%d", G[temp]);    
    for (; ;) {    
        int temp;    
        if (scanf("%d", &temp) < 0) break;    
        printf(" %d", G[temp]);    
    }    
    puts("");    
}
