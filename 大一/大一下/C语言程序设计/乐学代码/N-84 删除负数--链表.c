//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct _node {
//	int value;
//	struct _node *next;
//} Node;
//
//
////typedef struct _list {
////	Node *head;
////} List; 
//
//
//void delete_neg(Node **head);
//void outlist(Node *head); 
//Node* add(Node *head, int num);
//
//int main() {
//	int num = 1;
//	Node *head = NULL;
//	
//	head = (Node*) malloc (sizeof(Node));
//	head -> value = -1;
//	head -> next = NULL;
//	
//	while (num != 0) {
//		scanf("%d", &num);
//		if (num != 0) {
//			head = add(head, num);
//		}
//	}
//	
//	
////	Node *p, *q;
////	for (q = NULL, p = head; p; 
//	delete_neg(&head);
//	outlist(head);
//	
//	
//	
//	return 0;
//}
//
//
////void delete_neg(Node **head) {
////	Node *p = (*head) -> next;
////	Node *q = NULL;
////	
////	while (p) {
////		if (p -> value < 0) {
////			if (q) {
////				q -> next = p -> next;
////			} else {
////				*head = p -> next;
////			} 
////			Node *temp = p;
////			p = p -> next;
////			free(temp);
////		} else {
////			q = p;
////			p = p -> next;
////		}
////	}
////}
//
//Node* add(Node *head, int num) {
//	Node *p;
//	
//	p = (Node*)malloc(sizeof(Node));
//	p -> value = num;
//	p -> next = head -> next;
//	head -> next = p;
//	return head;
//}
//
//
//void outlist(Node *head) {
//	Node *p;
//	p = head -> next;
//	while (p != NULL) {
//		printf("%d\n", p -> value);
//		p = p -> next;
//	}
//	
//}
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
    
struct node    
{  
    int data;    
    struct node * next;    
};    
    
typedef struct node NODE;   
typedef struct node * PNODE;  
   
PNODE constructlist( PNODE head, int num );  
void outlist( PNODE head );  
PNODE deleteneg( PNODE head );   
    
int main ( )    
{   int num=1;    
    PNODE head = NULL;    
    
    head = (PNODE)malloc( sizeof(NODE) );    
    head->next = NULL;    
    head->data = -1;    
    
    while ( num!=0 )    
    {   scanf("%d", &num);    
        if ( num!=0 )    
           constructlist (head, num);    
    }    
    head = deleteneg( head );  
    outlist( head );  
	
	PNODE p;
	PNODE q;
	for (p = head; p; p = q) {
		q = p->next;
		free(p);
	} 
    return 0;    
}    
    
PNODE constructlist( PNODE head, int num )  
{   PNODE p;  
    p = (PNODE)malloc( sizeof(NODE) );   
    p->data = num;  
    p->next = head->next;   
    head->next = p;  
    return head;  
}  
  
void outlist( PNODE head )    
{   PNODE p;    
    p = head;    
    while ( p != NULL )    
    {   printf("%d\n", p->data);    
        p = p->next;    
    }    
}    
    
//This is an example for list. Please programme your code like it.  
PNODE deleteneg( PNODE head )  
{
	NODE *p = head;
	NODE *q = NULL;
	
	while (p != NULL) {
		if ( p->data < 0) {
			if (q != NULL) {
				q->next = p->next;
			} else {
				head = p->next;
			}
			NODE *curr = p;
			p = p->next;
			free(curr);
		} else {
			q = p;
			p = p->next;
		}
	}
	
	return head;
}  
  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
