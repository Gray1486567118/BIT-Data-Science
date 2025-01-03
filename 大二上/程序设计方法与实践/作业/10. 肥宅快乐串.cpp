#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 1010;

char input[N];
const char* beacon = "fattyhappy";
bool same[10] = {true};

void printchar(char c, int n);
void find_sub(char *input, int len);
void bool_init(bool *a, int len);


int main() {
	int t, i;
	cin >> t;
	
	for (i = 0; i < t; i ++) {
		scanf("%s", input);
		int len = strlen(input);
		bool_init(same, 10);
		find_sub(input, len);
	}
	return 0;
}


void find_sub(char *input, int len) {
	int i, j;
	int have_solution = 0;
	
	for (i = 0; i < len - 9; i ++) {
		int diff = 0;
		for (j = 0; j < 10; j ++) {
			if (input[i + j] != beacon[j]) {
				diff ++;
				same[j] = 0;
			} 
			
			if (diff == 3) {
				break;
			}
		}
		
		
		int k;
		
		if (diff == 0) {
			have_solution = 1;
			printf("%d %d\n", i + 3, i + 4);
		} else if (diff == 1) {
			char diff_char;
			int switch_position;
			for (k = 0; k < 10; k ++) {
				if (same[k] == 0) {
					diff_char = beacon[k];
					switch_position = i + k + 1;
					break;
				}
			}
			
			for (k = 0; k < i; k ++) {
				if (input[k] == diff_char) {
					have_solution = 1;
					printf("%d %d\n", k + 1, switch_position);
					break;
				}
			}
			
			if (have_solution != 1) {
				for (k = i + 10; k < len; k ++) {
					if (input[k] == diff_char) {
					have_solution = 1;
					printf("%d %d\n", switch_position, k + 1);
					break;
					}
				}
			}
			
		} else if (diff == 2) {
			int diff_1, diff_2;
			int diffs = 0;
			for (k = 0; k < 10; k ++) {
				if (same[k] == false) {
					if (diffs == 0) {
						diff_1 = k;
						diffs ++;
					} else {
						diff_2 = k;
						break;
					}
				}
			}
			
			if (input[i + diff_1] == beacon[diff_2] && input[i + diff_2] == beacon[diff_1]) {
				printf("%d %d\n", i + diff_1 + 1, i + diff_2 + 1);
				have_solution = 1;
			}	
		}

		if (have_solution == 1) {
			break;
		}
		
		// reset
		diff = 0;
		bool_init(same, 10);
	}
	
	if (have_solution == 0) {
		printf("-1\n");
	}
}

void bool_init(bool *a, int len) {
	int i;
	for (i = 0; i < len; i ++) {
		a[i] = true;
	}
}


void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		cout << c;
	}
}

