#include <stdio.h>  
#include <math.h>  
  
long long count_routes(int m, int n);  
void print_shortest_route(int x, int y, int m, int n);   
  
int main() {  
    int m, n, p, q;  
    scanf("%d %d %d %d", &m, &n, &p, &q);  
      
    long long r_pq = count_routes(p, q);  
    long long r_mn = count_routes(abs(m - p), abs(n - q));  
      
    printf("%lld\n", r_pq * r_mn);   
    print_shortest_route(m, n, p, q);  
    return 0;  
}  
  
  
long long count_routes(int m, int n) {  
 
    int i;  
    long long ans = 1;  
    for (i = m + n; i >= (m + 1); i --) {  
        ans *= i;  
    }  
      
    for (i = n; i >= 1; i --) {  
        ans /= i;  
    }  
      
    return ans;  
}  
  
  
void print_shortest_route(int m, int n, int p, int q) {  
    int i, j;  
      
    // (0,0)-(p,q)  
    for (i = 0; i < p; i ++) {  
        printf("(%d,0)", i);  
    }  
      
    for (j = 0; j < q; j ++) {  
        printf("(%d,%d)", p ,j);  
    }  
      
    // (p,q)-(m,n)  
    if (n > q) {  
        if (m - p > 0) {  
            for (i = p; i < m; i ++) {  
                printf("(%d,%d)", i, q);  
            }  
        } else if (m - p < 0) {  
            for (i = p; i > m; i --) {  
                printf("(%d,%d)", i, q);  
            }  
        }  
          
        for (j = q; j <= n; j ++) {  
            printf("(%d,%d)", m ,j);  
        }  
    } else if (n < q) {  
        for (j = q; j > n; j --) {  
            printf("(%d,%d)", p ,j);  
        }  
          
        if (m - p > 0) {  
            for (i = p; i <= m; i ++) {  
                printf("(%d,%d)", i, n);  
            }  
        } else if (m - p < 0) {  
            for (i = p; i >= m; i --) {  
                printf("(%d,%d)", i, n);  
            }  
        }     
    } else {  
        if (m - p > 0) {  
            for (i = p; i < m; i ++) {  
                printf("(%d,%d)", i, q);  
            }  
        } else if (m - p < 0) {  
            for (i = p; i > m; i --) {  
                printf("(%d,%d)", i, q);  
            }  
        }  
          
        printf("(%d,%d)", m, n);      
    }  
      
    printf("\n");  
}
