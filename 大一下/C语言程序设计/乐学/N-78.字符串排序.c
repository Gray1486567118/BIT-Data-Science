#include <stdio.h>    
#include <string.h>    
    
char str[10][51];    
int n = 0;    
    
int main()    
{    
    for (int i = 0; i < 10; i++, n++) {    
        char temp[50];    
        if (scanf("%s", temp) < 0) break;    
        for (int j = 0; j < strlen(temp); j++) {    
            int k = j - 1;    
            while (k >= 0 && (int)str[i][k] > (int)temp[j]) {    
                str[i][k + 1] = str[i][k];    
                k--;    
            }    
            str[i][k + 1] = temp[j];    
        }    
        str[i][strlen(temp)] = '\0';    
    }    
    for (char a = 'z'; (int)a >= (int)'A'; a--) {    
        for (int i = 0; i < n; i++)    
            if (str[i][0] == a) printf("%s\n", str[i]);    
        if (a == 'a') a = (char)((int)'Z' + 1);    
    }    
}
