#include <stdio.h>
#include <string.h>
#define size 10001

void count_char(int num_of_char[27][2], char *s, int len);
void seq(int num_of_char[27][2]);
void swap(int *a, int *b);

int main()
{
	char s[size];
	gets(s);
	int len = strlen(s), i;
	int num_of_char[27][2];
	
	for (i = 0; i < 27; i ++){
		num_of_char[i][0] = 0;
		num_of_char[i][1] = i;
	}
	
	count_char(num_of_char, s, len);
	seq(num_of_char);
	
	int most_char = num_of_char[1][0];
	int print_well[most_char +1];
	
	for (i = 1; i < most_char + 1; i ++){
		print_well[i] = 1;
	}
	
	
	int j = 1;   // 统计字母个数数组的指针
	for (i = most_char; i >= 1; i --){
		if (i < most_char){
			print_well[i] = print_well[i + 1];
		}
		int count = 0;		
		
		while (num_of_char[j + 1][0] == i){
			count ++;
			j ++;
		}
		
		print_well[i] += count;
	}
	
	for (i = 1; i <= most_char; i ++){
		for (j = 1; j <= print_well[most_char - i + 1] && j < 26; j ++){
			printf("# ");
		}
		
		if (print_well[most_char - i + 1] == 26){
			printf("#");
		} else{
			int k = 51 - 2 * (j - 1);
			for (j = 1; j <= k; j ++){
				printf(" ");
			}
		}
		printf("\n");
	} 
	
	for (i = 1; i < 26; i ++){
		printf("%c ", 'A' + num_of_char[i][1] - 1);
	} 
	printf("%c\n", 'A' + num_of_char[i][1] - 1);
	
	
//	printf("%d", most_char);
	
	return 0;
}


void count_char(int num_of_char[27][2], char *s, int len){
	int i;
	for (i = 0; i < len; i ++){
		int char_num;
		if (s[i] >= 'a' && s[i] <= 'z'){
			char_num = s[i] - 'a' + 1;
		} else if (s[i] >= 'A' && s[i] <= 'z'){
			char_num = s[i] - 'A' + 1;
		}
		num_of_char[char_num][0] ++;
	}
}

void seq(int num_of_char[27][2]){
	int i, j;
	for (i = 1; i < 27; i ++){
		for (j = 1; j < 27 - i; j ++){
			if (num_of_char[j][0] < num_of_char[j + 1][0] || 
			    (num_of_char[j][0] == num_of_char[j + 1][0] && 
				 num_of_char[j][1] > num_of_char[j + 1][1])){
				swap(&num_of_char[j][0], &num_of_char[j + 1][0]);
				swap(&num_of_char[j][1], &num_of_char[j + 1][1]);
			}
		} 
	}
}

void swap(int *a, int *b){
	int t = *a;
	*a = *b; 
	*b = t;
}


