#include <stdio.h>    
    
int arr[300], n, t;    
unsigned long long int IDarray[300];    
    
int main()    
{    
    scanf("%d %d", &n, &t);    
    for (int i = 0; i < n; i++) {    
        unsigned long long int temp1; int temp2;    
        scanf("%lld %d", &temp1, &temp2);    
        int j = i - 1;    
        while (j >= 0 && IDarray[j] > temp1) {    
            IDarray[j + 1] = IDarray[j];    
            arr[j + 1] = arr[j];    
            j--;    
        }    
        IDarray[j + 1] = temp1;    
        arr[j + 1] = temp2;    
    }    
    for (int i = 0; i < t; i++) {    
        unsigned long long int id, L = 0, R = n - 1, m = (L + R) / 2;    
        int num, point = -1;    
        scanf("%lld %d", &id, &num);    
        while (L <= R) {    
            if (id < IDarray[m]) R = m - 1;    
            else if (id > IDarray[m]) L = m + 1;    
            else { point = m; break; }    
            m = (L + R) / 2;    
        }    
        if (point < 0)     
            printf("ERR\n");    
        else if (arr[point] >= num) { arr[point] -= num; printf("Succeeded\n"); }    
        else printf("Failed\n");    
    }    
}
