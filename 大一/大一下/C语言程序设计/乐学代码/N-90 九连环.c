#include <stdio.h>  

void solve(int pos, int opt);  


int main()  
{  
    int n;  
    scanf("%d", &n);  
    solve(n, 0);  
    puts("");  
    return 0;  
} 


void solve(int pos, int opt) {
	if (opt == 1) {
		if (pos == 1) {
			printf("1 ");
		} else if (pos == 2) {
			printf("1 2 ");
		} else {
			solve(pos - 1, 1);
			solve(pos - 2, 0);
			printf("%d ", pos);
			solve(pos - 2, 1);
		}	
	} else {
		if (pos == 1) {
			printf("1 ");
		} else if (pos == 2) {
			printf("2 1 ");
		} else {
			solve(pos - 2, 0);
			printf("%d ", pos);
			solve(pos - 2, 1);
			solve(pos - 1, 0);
		}
	}
}
