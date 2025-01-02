#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 10001;

void printchar(char c, int n);

char nutritious[1000][30];

int main() {
	int n, i, j;
	cin >> n;
	getchar();
	
	int nutri = 0;
	for (i = 0; i < n; i ++) {
		char input[25];
		gets(input);
		int is_nutri = 1;
		
		if (strlen(input) > 10) {
			for (j = 0; j < nutri; j ++) {
				if (strcmp(input, nutritious[j]) == 0) {
					is_nutri = 0;
					break;
				} 
			}
		} else {
			is_nutri = 0;
		}
		
		if (is_nutri == 1) {
			strcpy(nutritious[nutri], input);
			nutri ++;
		}
	}
	
	cout << nutri << endl;
	 
	return 0;
}


void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		cout << c;
	}
}

