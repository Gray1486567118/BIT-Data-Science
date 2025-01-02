#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 100100;


void printchar(char c, int n);
void input_reverse(int a[]);
void printnum(int num[], int len);

int num1[N], num2[N], ans[N];
char input[N];

int main() {
	int t, i, j;
	cin >> t;
	
	for (i = 0; i < t; i ++) {
		// init
		memset(num1, 0, sizeof(num1));
		memset(num2, 0, sizeof(num2));
		memset(ans, 0, sizeof(ans));
		
		// input
		input_reverse(num1);
		input_reverse(num2);
		
		// compute
		int len = num1[0] > num2[0] ? num1[0] : num2[0];
		
		for (j = 1; j <= len; j ++) {
			ans[j] += num1[j] + num2[j];
			if (ans[j] >= 2) {
				ans[j] -= 2;
				ans[j + 1] ++;
			}
		}
		
		if (ans[len + 1] != 0) {
			len ++;
		}
		
		
		// output
		printchar(' ', len - num1[0] + 2);  
		printnum(num1, num1[0]);            
		printf("\n");
		
		printf("+");
		printchar(' ', len - num2[0] + 1);
		printnum(num2, num2[0]); 
		printf("\n");
		
		printchar('-', len + 2);
		printf("\n");
		
		printchar(' ', 2);
		printnum(ans, len); 
		printf("\n");

	}
	
	return 0;
}


void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		cout << c;
	}
}

void input_reverse(int a[]) {
	scanf("%s", input);
	int len = strlen(input);
	a[0] = len;
	int i;
	
	for (i = 1; i <= len; i ++) {
		a[i] = input[len - i] - '0';
	}
}

void printnum(int num[], int len) {
	int i;
	for (i = len; i >= 1; i --) {
		printf("%d", num[i]);
	}
}
