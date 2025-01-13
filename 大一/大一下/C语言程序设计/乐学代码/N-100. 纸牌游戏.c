#include <stdio.h>
#include <stdlib.h>

struct player {
	int blood;
	int card[3];  // K D F 
};


typedef struct card_pile {
	char card;
	struct card_pile *next;
} Pile;


void init(int *card, char *init_card);
void init_cardpile(Pile *head, char *cardpile, int n);
Pile* draw(Pile *head, int card[], int *n);
void add_cards(int card[], char c);
void duel(int card0[], int card1[], int *blood0, int *blood1);
void kill(int card0[], int card1[], int *blood1);
void gameover(int card[], int blood);


int game_over = 0;  // end of game

int main() {
	int n;
	scanf("%d", &n);
	
	// initialize
	struct player P[2];
	P[0].blood = 4;  
	P[1].blood = 4;
	char init_card0[5], init_card1[5], cardpile[n + 1];
	scanf("%s", &init_card0);
	scanf("%s", &init_card1);
	scanf("%s", &cardpile);
	
	init(P[0].card, init_card0);
	init(P[1].card, init_card1);
	
	Pile *head = NULL;
	head = (Pile*) malloc(sizeof(Pile));
	head->next = NULL;
	init_cardpile(head, cardpile, n);
	
	// play
	int curr = 0;
	
	while (1) {
		// draw cards
		if (n > 0) {
			draw(head, P[curr].card, &n);	
		} else {
			if (P[curr].card[0] == 0 && P[curr].card[2] == 0 && P[1-curr].card[0] == 0 && P[1-curr].card[2] == 0) {
				break;
			}
		}
		
		// duel
		while (P[curr].card[2] > 0) {
			duel(P[curr].card, P[1 - curr].card, &P[curr].blood, &P[1-curr].blood);
			if (game_over== 1)  break;
		}
		if (game_over == 1)  break;
		
		
		// kill 
		if (P[curr].card[0] > 0) {
			kill(P[curr].card, P[1 - curr].card, &P[1-curr].blood);
		}
		if (game_over == 1)  break;
		
		curr = 1 - curr;
	}


	// end
	if (P[0].blood == 0) {
		printf("Jerry win!\n");
	} else if (P[1].blood == 0) {
		printf("Tom win!\n");
	} else {
		printf("Tied!\n");
	}
	gameover(P[0].card, P[0].blood);
	gameover(P[1].card, P[1].blood);

	return 0;
}


void init(int *card, char *init_card) {
	int i;
	for (i = 0; i < 3; i ++) {
		card[i] = 0;
	}
	for (i = 0; i < 4; i ++) {
		add_cards(card, init_card[i]);
	}
}

void init_cardpile(Pile *head, char *cardpile, int n) {
	Pile *p;
	while (n > 0) {
		p = (Pile*) malloc(sizeof(Pile));
		p->card = cardpile[n - 1];
		p->next = head->next;
		head->next = p;
		n --;
	}
}

int end(int blood0, int blood1) {
	if (blood0 == 0 || blood1 == 0) {
		return 1;
	} else {
		return 0;
	}
}

Pile* draw(Pile *head, int card[], int *n) {
	Pile *p;
	
	if (*n >= 2) {
		*n -= 2;
		p = head->next;
		add_cards(card, p->card);
		add_cards(card, p->next->card);
		head->next = p->next->next;
		free(p->next);
		free(p);
	} else {
		*n -= 1;
		p = head->next;
		add_cards(card, p->card);
		free(p);
	}
	return head;
}

void add_cards(int card[], char c) {
	if (c == 'K') {
		card[0] ++;
	} else if (c == 'D') {
		card[1] ++;
	} else if (c == 'F') {
		card[2] ++;
	}
}

void duel(int card0[], int card1[], int *blood0, int *blood1) {
	card0[2] --;
	if (card0[0] >= card1[0]) {
		(*blood1) --;
		card0[0] -= card1[0];
		card1[0] = 0;
	} else {
		(*blood0) --;
		card1[0] = card1[0] - 1 - card0[0];
		card0[0] = 0;
	}
	
	game_over = end(*blood0, *blood1);
}

void kill(int card0[], int card1[], int *blood1) {
	card0[0] --;
	if (card1[1] == 0) {
		(*blood1) --;
	} else {
		card1[1] --;
	}
	game_over = end(1, *blood1);
}

void gameover(int card[], int blood) {
	if (blood == 0) {
		printf("0\nDEAD\n");
	} else {
		printf("%d\n", blood);
		int i, j;
		for (i = 0; i < 3; i ++) {
			for (j = 0; j < card[i]; j ++) {
				if (i == 0) {
					printf("K");
				} else if (i == 1) {
					printf("D");
				} else {
					printf("F");
				}
			}
		}
		printf("\n");
	}
} 




