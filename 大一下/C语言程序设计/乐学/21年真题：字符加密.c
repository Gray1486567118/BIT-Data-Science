#include <stdio.h>
#include <string.h>

int Calrome(char *rome);
int Calseed(int arab);
void code(char *s, int move);

int main() {
	char rome[30];
	scanf("%s", rome);
	
	int arab = Calrome(rome);
	int seed = Calseed(arab);
	
	int num[25], i, j;
	for (i = 0; i < 25; i ++)  scanf("%d", &num[i]);

	for (i = 0; i < 25; i ++) {
		for (j = 0; j < 25 - i - 1; j ++) {
			if (num[j] > num [j + 1]) {
				int temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	
	int key = num[seed - 1];
	int move = key % 26;
	
	char s[1000];
	getchar();
	gets(s);
	
	code(s, move);
	
//	printf("%d", seed);
	
	return 0;
}

int Calrome(char *rome) {
	int n = 0, i;
	int len = strlen(rome);
	
	// M D C L X V I
	for (i = 0; i < len; i ++) {
		if (rome[i] == 'M') {
			n += 1000;
		} else if (rome[i] == 'D') {
			n += 500;
		} else if (rome[i] == 'C') {
			if (i + 1 < len) {
				if (rome[i + 1] == 'M') {
					n += 900;
					i ++;
				} else if (rome[i + 1] == 'D') {
					n += 400;
					i ++;
				} else {
					n += 100;
				}
			} else {
				n += 100;
			}
		} else if (rome[i] == 'L') {
			n += 50;
		} else if (rome[i] == 'X') {
			if (i + 1 < len) {
				if (rome[i + 1] == 'L') {
					n += 40;
					i ++;
				} else if (rome[i + 1] == 'C') {
					n += 90;
					i ++;
				} else {
					n += 10;
				}
			} else {
				n += 10;
			}
		} else if (rome[i] == 'V') {
			n += 5;
		} else if (rome[i] == 'I') {
				if (i + 1 < len) {
				if (rome[i + 1] == 'V') {
					n += 4;
					i ++;
				} else if (rome[i + 1] == 'X') {
					n += 9;
					i ++;
				} else {
					n += 1;
				}
			} else {
				n += 1;
			}
		}
	}
	return n;
}

int Calseed(int arab) {
	while (arab >= 10) {
		int n = arab;
		int digit_sum = 0;
		
		while (n > 0) {
			digit_sum += n % 10;
			n /= 10;
		}
		
		arab = digit_sum;
	}
	
	return arab;
}

void code(char *s, int move) {
	int len = strlen(s);
	int i;
	
	for (i = 0; i < len; i ++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			if (s[i] + move > 'z') {
				s[i] += move - 26;
			} else {
				s[i] += move;
			}
		}
	} 
	
	printf("%s\n", s);
}
