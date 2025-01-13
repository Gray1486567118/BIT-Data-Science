#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int num;
	struct _node *next;	
} Node;

Node* movenode (Node *head, int m);
void setlink (Node *head, int n);
void outlink (Node *head);

int main() {
	int n, m;
	Node *head = NULL;
	
	scanf("%d %d", &n, &m);
	head = (Node*)malloc(sizeof(Node));
	head -> num  = -1;
	head -> next = NULL;
	setlink(head, n);
	
	head = movenode(head, m);
	
	outlink(head);
	printf("\n");		
	return 0;
}


Node* movenode (Node *head, int m) {
	Node *p, *q;
	for (q= NULL, p = head; p; q = p, p = p->next) {
		if (p->num == m){
			if (q != NULL) {				
				q->next = p->next;
				p->next = head->next;
				head->next = p;
			}
			break;
		}
	}
	
	return head;
}


void setlink (Node *head, int n) {
	Node *p;
	
	while (n > 0) {
		p = (Node*)malloc(sizeof(Node));
		p -> num = n;
		p -> next = head -> next;
		head -> next = p;
		n --;
	}
}


void outlink (Node *head) {
	while (head -> next != NULL) {
		head = head -> next;
		printf("%d,", head -> num);
	}
}
