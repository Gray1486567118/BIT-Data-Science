#include <stdio.h>

void swap(int *a, int *b);
int Josephus(int n, int k, int people[][3]);

int main()
{
	int n, k, direction;
	scanf("%d %d %d", &n, &k, &direction);
	
	int people[n][3], i;            // 第一列状态，第二列号码，第三列年龄 
	for (i = 0; i < n; i ++){
		people[i][0] = 1;
		scanf("%d %d", &people[i][1], &people[i][2]);
	}
	
	if (direction == 1){
		for (i = 1; i <= n / 2; i ++){
			swap(&people[i][1], &people[n - i][1]);
			swap(&people[i][2], &people[n - i][2]);
		} 
	}
	
	int alive = Josephus(n, k, people);
	int original_num;
	if (direction == 0){
		original_num = alive + 1;
		printf("%d,%d,%d\n", original_num, people[alive][1], people[alive][2]);
	} else{
		if (alive == 0){
			original_num = alive + 1;
		} else{
			original_num = n - alive;
		}
		printf("%d,%d,%d\n", original_num, people[alive + 1][1], people[alive + 1][2]);
	}
	
	 
	return 0;
}


void swap(int *a, int *b){
	int t = *a; 
	*a = *b;
	*b = t;
}


int Josephus(int n, int k, int people[][3]){
	int remain = n;
	int current = 0;
	
	while (remain > 1){
		int count = 0;
		
		while (count < k){
			if (people[current][0] == 1){
				count ++;
			}
			
			if (count == k){
				people[current][0] = 0;
				remain --;
			}
			
			current = (current + 1) % n;
		}
	} 
	
	int i;
	for (i = 0; i < n; i ++){
		if (people[i][0] == 1){
			return i;
		}
	}
}
