#include <stdio.h>  
#include <stdlib.h>  
#define N 100010 
 
typedef struct Edge{  
    int to;  
    struct Edge* nxt;  
}EDGE;  

EDGE* head[N];  
void Add_Edge(int u, int v);  
void Print(EDGE* head);  

int main()  
{  
    int n, m;  
    scanf("%d%d", &n, &m);  
    for(int i = 1; i <= n; ++i) head[i] = NULL;  
    for(int i = 1; i <= m; ++i){  
        int u, v;  
        scanf("%d%d", &u, &v);  
        Add_Edge(u, v);  
    }  
    for(int i = 1; i <= n; ++i)  
        printf("%d: ", i), Print(head[i]);  
    return 0;  
}  
