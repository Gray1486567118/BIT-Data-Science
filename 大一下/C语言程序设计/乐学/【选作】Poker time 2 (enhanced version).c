#include <stdio.h>
#include <string.h>
#define size 5

int cmp(char *card1, char *card2); 
int valid(char *card);
int p(int *array, char card, int len);
int power(char *c1, char *c2, char *c3);
void swap(char *card1, char *card2);
void sort(char *card1, char *card2, char *card3);
void same_card_type(char *a1, char *a2, char *a3, char *b1, char *b2, char *b3);


int main()
{
	char a1[size], a2[size], a3[size], b1[size], b2[size], b3[size]; 
	scanf("%s %s %s", a1, a2, a3);
	scanf("%s %s %s", b1, b2, b3);

    if ((valid(a1) && valid(a2) && valid(a3) && valid(b1) && valid(b2) && valid(b3))
		 && strcmp(a1, a2) != 0 && strcmp(a1, a3) != 0 && strcmp(a3, a2) != 0 
		 && strcmp(b1, b2) != 0 && strcmp(b1, b3) != 0 && strcmp(b3, b2) != 0)
    {	
	    // sort  H S D C
		sort(a1, a2, a3);
		sort(b1, b2, b3);
	    
	    // card tyoe
		int powerA = power(a1, a2, a3);
		int powerB = power(b1, b2, b3);

		if (powerA > powerB)
		{
			printf("Winner is A!\n");
		} else if (powerA < powerB)
		{
			printf("Winner is B!\n");
		} else
		{
			// same card type
			if (powerA != 2)
			{
				same_card_type(a1, a2, a3, b1, b2, b3);
			} else
			{
				// find the pair
				char pairA[size], pairB[size];
				if (a1[1] == a2[1] || a1[1] == a3[1])
				{
					strcpy(pairA, a1);
				} else
				{
					strcpy(pairA, a2);
				}
				
				if (b1[1] == b2[1] || b1[1] == b3[1])
				{
					strcpy(pairB, b1);
				} else
				{
					strcpy(pairB, b2);
				}
				
				if (cmp(pairA, pairB) == 1)
				{
					printf("Winner is A!\n");
				} else if (cmp(pairA, pairB) == -1)
				{
					printf("Winner is B!\n");
				} else 
				{
					printf("Draw!\n");
				}
			}
		}
		
		
	    printf("A: %s %s %s\n", a1, a2, a3);
	    printf("B: %s %s %s\n", b1, b2, b3);
	    
	} else
	{
		printf("Input Error!\n");
	}

	return 0;
}





int valid(char *card)  // 50 - 58; 74 81 75 65
{
	int check = card[1] ;
	if (check == 65 || check == 74 || check == 75 || check == 81 
		|| (50 <= check && check <= 58) || (check == 49 && card[3] == 0) )
	{
		return 1;
	} else
	{
		return 0;
	}
}


int cmp(char *card1, char *card2) // bigger: 1;  equal: 0;  smaller: -1
{
	int suitOrder[] = {67, 68, 83, 72};
	int numOrder[] = {50, 51, 52, 53, 54, 55, 56, 57, 49, 74, 81, 75, 65};
	int suit1, suit2, num1, num2;
	int len1 = sizeof(suitOrder) / sizeof(suitOrder[0]);
	int len2 = sizeof(numOrder) / sizeof(numOrder[0]);
	
	suit1 = p(suitOrder, card1[0], len1);
	suit2 = p(suitOrder, card2[0], len1);
	num1  = p(numOrder , card1[1], len2);
	num2  = p(numOrder , card2[1], len2);
	
	
	if (num1 > num2)
	{
		return 1;
	} else if (num1 < num2)
	{
		return -1;
	} else
	{
		if (suit1 > suit2)
		{
			return 1;	
		} else if (suit1 < suit2)
		{
			return -1;
		} else
		{
			return 0;
		}
	}
}


int p(int *array, char card, int len) // power of single card, to sort
{
	int i;
	for (i = 0; i < len; i ++)
	{
		if (card == array[i])
		{
			return i;
		}
	}
	return -1;
}


int power(char *c1, char *c2, char *c3)
{
	// st flush > 3 of a kind > st > pair > high    5 4 3 2 1
	int numOrder[] = {50, 51, 52, 53, 54, 55, 56, 57, 49, 74, 81, 75, 65};
	int len = sizeof(numOrder) / sizeof(numOrder[0]);
	int num1, num2, num3;
	
	num1 = p(numOrder , c1[1], len);
	num2 = p(numOrder , c2[1], len);
	num3 = p(numOrder , c3[1], len);
	
	if ( ((c1[0] == c2[0]) && (c1[0] == c3[0]))  &&  
		 ((num1 - num2) == 1) && ((num2 - num3) == 1) )
	{
		return 5;
	} else if ( (num1 == num2) && (num1 == num3) )
	{
		return 4;
	} else if ( ((num1 - num2) == 1) && ((num2 - num3) == 1) )
	{
		return 3;
	} else if ( (num1 == num2) || (num1 == num3) || (num3 == num2))
	{
		return 2;  // pair may not be the biggest
	} else
	{
		return 1;
	}
		 
	
}


void swap(char *card1, char *card2)
{
	char temp[3];
	strcpy(temp, card1);
	strcpy(card1, card2);
	strcpy(card2, temp);
}


void sort(char *card1, char *card2, char *card3)
{
	if (cmp(card1, card2) < 0) swap(card1, card2);
	if (cmp(card2, card3) < 0) swap(card2, card3);
	if (cmp(card1, card2) < 0) swap(card1, card2);
}


void same_card_type(char *a1, char *a2, char *a3, char *b1, char *b2, char *b3)
{
	if (cmp(a1, b1) == 1)
	{
	   	printf("Winner is A!\n");
	} else if (cmp(a1, b1) == -1)
	{
		printf("Winner is B!\n");
	} else
	{
		if (cmp(a2, b2) == 1)
		{
			printf("Winner is A!\n");
		} else if (cmp(a2, b2) == -1)
		{
			printf("Winner is B!\n");
		} else 
		{
			if (cmp(a3, b3) == 1)
			{
				printf("Winner is A!\n");
			} else if (cmp(a3, b3) == -1)
			{
				printf("Winner is B!\n");
			} else
			{
				printf("Draw!\n");
			}
		}
	}
}


