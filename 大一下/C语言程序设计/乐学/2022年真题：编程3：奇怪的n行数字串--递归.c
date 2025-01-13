#include <stdio.h>  
#include <math.h>  
  
int main() {  
    int n, k;  
    scanf("%d %d", &n, &k);  
      
    printf("%d\n", num(n, k));    
    return 0;  
}  
  
  
int num(int n, int k) {  
    if (n == 1) {  
        return 1;  
    } else if (n == 2) {  
        if (k == 1) {  
            return 0;  
        } else {  
            return 1;  
        }  
    }  
      
    int half = pow(2, n - 2);  
    if (k > half) {  
        return 1 - num(n - 1, k - half);  
    } else {  
        return num(n - 1, k);  
    }  
}  
