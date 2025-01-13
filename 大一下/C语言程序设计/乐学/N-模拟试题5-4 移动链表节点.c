#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct numLink  
{  
    int no;  
    struct numLink *next;  
}NODE;  
  
void movenode( NODE *head);  
  
void SetLink( NODE *h, int n )  
{  
    NODE *p=NULL, *q=NULL;  
    int i;  
    for( i=0; i<n; i++)  
    {  
        p = (NODE *)malloc(sizeof(NODE));  
        p->no = i+1;  
        p->next = NULL;  
        if( h->next == NULL )  
        {  
            h->next = p;  
            q = p;  
        }  
        else  
        {  
            q->next = p;  
            q = q->next;  
        }  
    }  
    return;  
}  
  
int main( )  
{  
    int n;  
    NODE *head=NULL, *q=NULL;  
    scanf("%d",&n);  
  
    head = (NODE *)malloc(sizeof(NODE));  
    head->no = -1;  
    head->next = NULL;  
  
    SetLink( head, n );  
    movenode( head );  
  
    q = head;  
    while (q->next){  
        printf("%d ",q->next->no);  
        q = q->next;  
    }   
    printf("\n");  
      
    system("pause");  
    return 0;  
} 


void movenode(NODE *head) {
	int n = 1, i;
	NODE *end;
	if (head->next != NULL) {
		end = head->next;
		while (end->next != NULL){
			end = end->next;
			n ++;
		}	
	}

	
	if (n > 2) {
		NODE *p, *q;
		for (p = head->next, q = NULL, i = 0; i < n; i ++) {
			if (p->no % 2 == 0) {
				q->next = p->next;
				end->next = p;
				end = end->next;
				end->next = NULL;
				p = q->next;
				
			} else {
				q = p;
				p = p->next;
			}
		} 	
	}
	
}
