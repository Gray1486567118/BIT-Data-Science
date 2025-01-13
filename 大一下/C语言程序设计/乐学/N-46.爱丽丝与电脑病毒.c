#include <stdio.h>
#include <string.h>

int main()
{
	char s[100001];
	fgets(s, sizeof(s), stdin);
	
	char *enter = strchr(s, '\n');
	*enter = '\0';
	
	printf("#include<stdio.h>\n");
	printf("int main()\n{\n");
	printf("    int n,i;\n");
	printf("    scanf(\"%%d\",&n);\n");
	printf("    for(i=0;i<n;i++){\n");
	printf("        printf(\"%s\\n\");\n", s);
	printf("    }\n}\n");
	
	return 0;
}

