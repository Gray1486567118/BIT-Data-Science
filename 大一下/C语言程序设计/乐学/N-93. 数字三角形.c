#include <stdio.h>    
    
int arr[2000][2000], N, ans;    
    
int main()    
{    
    scanf("%d", &N);    
    for (int i = 0; i < N; i++)    
        for (int j = 0; j <= i; j++)    
            scanf("%d", &arr[i][j]);    
    for (int i = N - 2; i >= 0; i--)    
        for (int j = 0; j <= i; j++)    
            arr[i][j] += (arr[i + 1][j] > arr[i + 1][j + 1]) ? arr[i + 1][j] : arr[i + 1][j + 1];    
    printf("%d\n", arr[0][0]);    
}
