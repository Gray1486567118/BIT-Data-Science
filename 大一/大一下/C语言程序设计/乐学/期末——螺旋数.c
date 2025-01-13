#include <stdio.h>

int main() {
	int h, w;
	scanf("%d %d", &h, &w);
	
	int A[h][w];
	int i, j;
	for (i = 0; i < h ; i ++) {
		for(j = 0; j < w; j ++) {
			A[i][j] = -1;
		}
	}
	
	int dire[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
	int num = 0;
	int next = 0;
	int printed = 0;
	
	for (i = 0, j = 0; printed < h * w; i += dire[next][0], j += dire[next][1], printed ++) {
		A[i][j] = num;
		
		int next_i = i + dire[next][0];
		int next_j = j + dire[next][1];
		
		if (next_i >= h || next_j >= w || next_i < 0 || A[next_i][next_j] != -1) {
			num ++;
			next += 1;
			next %= 4;
		}
	}
	
	
	for (i = 0; i < h; i ++) {
		for (j = 0; j < w; j ++) {
			printf("%3d", A[i][j]);
		}
		printf("\n");
	}
	
	
	
	return 0;
}
