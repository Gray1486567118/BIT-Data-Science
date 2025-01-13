#include <stdio.h>    
    
int T, arr[1000], op, N, d;    
    
int S(int N)    
{    
    int ans = 1;    
    d = 2000;    
    for (int i = 0; i < N; i++) {    
        int s = 1, move = arr[i] - i >= 0 ? arr[i] - i : arr[i] - i + N;    
        for (int j = 1; j < N; j++)    
            if (arr[(i + j) % N] - arr[i] == j) s++;    
        if (s > ans) {    
            ans = s;    
            d = move;    
        }    
        else if (s == ans)     
            d = d > move ? move : d;    
    }    
    return ans;    
}    
    
int main()    
{    
    scanf("%d", &T);    
    for (int I = 0; I < T; I++) {    
        scanf("%d%d", &op, &N);    
        if (op == 1) {    
            for (int i = 0; i < N; i++)    
                scanf("%d", &arr[i]);    
            int ANS = S(N);     
            printf("%d %d\n", ANS, d);    
        }    
        else if (op == 2) printf("%d\n", 2 - N % 2);    
    }    
}
