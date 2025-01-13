#include <stdio.h>    
    
int A[201307], gAddition = 0;    
    
int main()     
{    
    int N, M;    
    scanf("%d %d", &N, &M);    
    for (int i = 0; i < N; i++)     
        scanf("%d", &A[i]);    
    for (int i = 0; i < M; i++) {    
        int t, x;    
        scanf("%d %d", &t, &x);    
        if (t == 0)    
            gAddition += x;    
        else if (t == 1)    
            A[x - 1] = -A[x - 1] - 2 * gAddition;    
    }    
    for (int i = 0; i < N; i++)    
        printf("%d\n", A[i] + gAddition);    
}
