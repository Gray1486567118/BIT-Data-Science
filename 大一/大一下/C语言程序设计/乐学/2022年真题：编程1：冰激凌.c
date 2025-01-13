#include <stdio.h>

void printchar(char ch, int num);



int main()
{
	int layer, width, height;
	scanf("%d %d %d", &layer, &width, &height);
	
	// head
	int num_space = (layer - 1) * 2 + (width + 1) / 2 - 1;
	printchar(' ', num_space);
	printf("*\n");
	printchar(' ', --num_space);
	printchar('*', 3);
	printf("\n");
	
	// layers
	int i;
	num_space = num_space - (width - 3) / 2;
	for (i = 0; i < layer; i ++)
	{
		int j;
		for (j = 0; j < height; j ++)
		{
			printchar(' ', num_space);
			printchar('*', width);
			printf("\n");	
		}

		width += 4;
		num_space -= 2;
	}
//	printf("%d", width);
	
	// bottom
	int wid_bottom = width - 4;
	int num_space1 = 0;
	num_space = wid_bottom - 2;
	for (i = 0; i < wid_bottom / 2; i ++)
	{
		printchar(' ', num_space1);
		printf("*");
		printchar(' ', num_space);
		printf("*\n");
		num_space -= 2;
		num_space1 += 1;
	}
	printchar(' ', num_space1);
	printf("*\n");
	return 0;
}



void printchar(char ch, int num)
{
	int i;
	for (i = 0; i < num; i ++)
	{
		printf("%c", ch);
	}
}
