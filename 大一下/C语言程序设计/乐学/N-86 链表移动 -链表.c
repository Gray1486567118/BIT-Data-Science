#include <stdio.h>
#include <stdlib.h>

typedef struct numLink {
	int num;
	struct numLink *next;
} NODE;

NODE* movenode (NODE *head, int m);
void SetLink(NODE *head, int n);
void PrintLink(NODE *head);



int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	 
	NODE *head = NULL;
	head = (NODE*) malloc (sizeof(NODE));
	head->num  = -1;
	head->next = NULL;
	
	SetLink(head, n);
	head = movenode(head, m);
	PrintLink(head);
	
	return 0;
}

void SetLink(NODE *head, int n) {
	NODE *p;
	while (n > 0) {
		p = (NODE*) malloc (sizeof(NODE));
		p->num = n;
		p->next = head->next;
		head->next = p;
		n --;
	}
}

void PrintLink(NODE *head) {
	while (head->next != NULL) {
		head = head->next;
		printf("%d ", head->num);
	}
	printf("\n");
}

NODE* movenode(NODE *head, int m) {
	NODE *p, *q, *pm, *last;
	int no_move = 0; 
	for (p = head->next; p; p = p->next) {
		if (p->num == m) {
			if (p->next != NULL) {
				q = p->next;
				pm = p;
			} else {
				no_move = 1;
			}
		}
		
		if (p->next == NULL) {
			last = p;
		}
	}
	
	if (no_move == 0) {
		last->next = head->next;
		head->next = q;
		pm->next = NULL;
	}
	
	return head;
}
