#include <stdio.h>    
#include <malloc.h>    
    
int N, M, max[201308] = { 0 }, len[201308] = { 0 }, * ptr[201308] = { NULL };    
    
int main()    
{    
    scanf("%d %d", &N, &M);    
    for (int i = 1; i <= N; i++) {    
        ptr[i] = malloc(sizeof(int) * ++max[i]);    
        len[i] = 1;    
        ptr[i][0] = i;    
    }    
    for (int I = 0; I < M; I++) {    
        int v, a, p;    
        scanf("%d %d %d", &v, &a, &p);    
        if (++len[v] >= max[v]){    
            max[v] *= 2;    
            int arr[max[v]];    
            for (int i = 0; i < len[v] - 1; i++)    
                arr[i] = ptr[v][i];    
            free(ptr[v]);    
            ptr[v] = malloc(sizeof(int) * max[v]);    
            for (int i = 0; i < len[v] - 1; i++)    
                ptr[v][i] = arr[i];    
        }    
        ptr[v][len[v] - 1] = a;    
        printf("%d\n", ptr[v][p - 1]);    
    }    
    for (int i = 1; i <= N; i++)    
        free(ptr[i]);    
}
