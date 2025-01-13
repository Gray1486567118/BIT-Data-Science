#include <stdio.h>

int main() {
	FILE *fp;
	char fn[100], s[20];
	int line, i;
	scanf("%s%d", &fn, &line);
	
	fp = fopen(fn, "r");
	if (fp == NULL) {
		printf("File Name Error.\n");
		fclose(fp);
		return 0;
	} else {
		for (i = 0; i < line; i ++) {
			if (fgets(s, 20, fp) == NULL) {
				printf("Line No Error.\n");	
				fclose(fp);
				return 0;		
			}
		}
	}
	
	printf("%s\n", s);
	fclose(fp);
	return 0;
}
