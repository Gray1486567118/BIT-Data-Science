#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct identifier {
	char name[1000];
	int num;
};


int main() {
	char s[1001];
	gets(s);
	
	struct identifier I[1001];
	int i;
	for (i = 0; i < 1001; i ++) {
		I[i].num = 0;
	}
	
	int have_identifier = 0;
	int count_identifier = 0;
	int max = 0;
	char max_i[1001];
	
	char *token = strtok(s, " ,.;");
	while (token != NULL) {
		if (isalpha(token[0]) || token[0] == '_') {
			have_identifier = 1;
			int found = 0;
			for (i = 0; i < count_identifier; i ++) {
				if (strcmp(I[i].name, token) == 0) {
					I[i].num ++;
					found = 1;
					if (I[i].num > max) {
						max = I[i].num;
						strcpy(max_i, I[i].name);
					}
					break;
				}
			}
			
			if (found == 0) {
				strcpy(I[count_identifier].name, token);
				I[count_identifier].num ++;
				
				if (I[count_identifier].num > max) {
					max = I[count_identifier].num;
					strcpy(max_i, I[count_identifier].name);
				}
				
				count_identifier ++;
			}
		}
		token = strtok(NULL, " ,.;");
	}
	
	if (have_identifier == 1) {
		printf("%s\n", max_i);
	} else {
		printf("No identifier!\n");
	}
	
	
	return 0;
}
