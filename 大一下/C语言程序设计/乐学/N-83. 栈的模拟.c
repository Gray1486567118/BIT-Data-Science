#include <stdio.h>    
int stack[3000], all[3000], num1 = 0, num2 = 0;    
    
int main()    
{    
    for (int I = 0; I < 3000; I++) {    
        char str[10];    
        if (scanf("%s", str) < 0) break;    
        if (str[1] == 'o' && num1 > 0) {    
            num1--;    
            all[num2] = stack[num1];    
            num2++;    
        }    
        else if (str[1] == 'e') {    
            if (num1 > 0) printf("%d", stack[0]);    
            for (int i = 1; i < num1; i++)    
                printf(" %d", stack[i]);    
            printf("\n");    
        }    
        else if (str[1] == 'u') {    
            int temp = 0, i0 = 5;    
            if (str[i0] == '-') i0++;    
            for (int i = i0; str[i] >= '0' && str[i] <= '9'; i++)    
                temp = temp * 10 + (int)str[i] - (int)'0';    
            stack[num1] = i0 == 6 ? -temp : temp;    
            num1++;    
        }    
    }    
    if (num2 > 0) {    
        printf("%d", all[0]);    
        for (int i = 1; i < num2; i++)    
            printf(" %d", all[i]);    
        for (int i = num1 - 1; i >= 0; i--)    
            printf(" %d", stack[i]);    
        printf("\n");    
    }    
    else if (num1 > 0) {    
        printf("%d", stack[num1 - 1]);    
        for (int i = num1 - 2; i >= 0; i--)    
            printf(" %d", stack[i]);    
        printf("\n");    
    }    
}
