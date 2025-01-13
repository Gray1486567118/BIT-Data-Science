#include <stdio.h>

int cd[5], last_s;

int if_cd(int s)
{
	if(!cd[s] && last_s != s)
	{
		cd[s] = s;
		last_s = s;
		return 1;
	}
	else
		return 0;
}

int main()
{
	char s[52] = {0};
	scanf("%s", s);
	int count, i, j, k, selection;
	char *p = s;
	while(*p != '\0')
	{
		if(*p == 'A')
			selection = 1;
		if(*p == 'Q')
			selection = 2;
		if(*p == 'E')
			selection = 3;
		if(*p == 'W')
			selection = 4;
		count += if_cd(selection);	
		for(i = 1; i <= 4; i++)
			if(cd[i])
				cd[i]--;		
		*p++;
	}
	printf("%d ", count>6?6:count);
	if(count >= 6)
		printf("Y\n");
	else
		printf("N\n");
	return 0;
}