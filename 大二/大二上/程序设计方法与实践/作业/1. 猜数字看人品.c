#include <stdio.h>
#include <string.h>

int main() {
	int input;
	char s[10];
	char low[10] = "too low";
	char high[10] = "too high";
	int small = -1;
	int big = 11;
	int cheat = 0;
	
	scanf("%d", &input);
	getchar();
	
	while (input != 0) {
		gets(s);
		
		if (strcmp(s, low) == 0) {
			if (input > small) {
				small = input;	
			}
			if (small >= big) {
				cheat = 1;
			}
		} else if (strcmp(s, high) == 0) {
			if (input < big) {
				big = input;	
			}
			if (big <= small) {
				cheat = 1;
			}
		} else {
			if (input <= small || input >= big) {
				cheat = 1;
			}
			
			if (cheat == 0) {
				printf("Tom may be honest\n");
			} else {
				printf("Tom is dishonest\n");
			}
			
			small = -1;
			big = 11;
			cheat = 0;
		}
		
		
		scanf("%d", &input);
		getchar();
	}
}
