#include <stdio.h>

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int a[n][m];
	int i, j;
	int no = 0;
	
	for (i = 0; i < n; i ++) {
		for (j = 0; j < m; j ++) {
			scanf("%d", &a[i][j]);
		}
	}
	
	for (i = 0; i < n; i ++) {
		for (j = 0; j < m; j ++) {
			int larger_in_row = 0;
			int larger_in_col = 0;
			
			int p;
			for (p = 0; p < n; p ++) {
				if (a[p][j] > a[i][j]) {
					larger_in_col = 1;
					break;
				}
			}
			
			for (p = 0; p < m; p ++){
				if (a[i][p] > a[i][j]) {
					larger_in_row = 1;
					break;
				}
			}
			
			if (larger_in_row == 1 && larger_in_col == 1) {
				no = 1;
				break;
			}
		}
		if (no == 1) {
			break;
		}
	}
	
	if (no == 1) {
		printf("NO\n");
	} else {
		printf("YES\n");
	}
	
	return 0;
}
