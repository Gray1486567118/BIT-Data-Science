#include<stdio.h>  
  
int m, n, t, p, q, num;  
  
void dfs(int a,int b);  

int main() {  
    scanf("%d", &num);  
    int i;
    for(i = 1; i <= num; i ++) {  
        t = 0;  
        scanf("%d%d%d%d", &n, &m, &p, &q);  
        dfs(p, q);  
        printf("%d\n", t);  
    }  
    return 0;  
}

void dfs(int a,int b) {
	if (a == n && b == m) {
		t ++;
	}
	
	// срио 
	if (a + 2 <= n && b + 1 <= m)    dfs(a + 2, b + 1);
	if (a + 1 <= n && b + 2 <= m)    dfs(a + 1, b + 2);
	
	// сроб 
	if (a - 1 >= 0 && b + 2 <= m)    dfs(a - 1, b + 2);
	if (a - 2 >= 0 && b + 1 <= m)    dfs(a - 2, b + 1);
}
