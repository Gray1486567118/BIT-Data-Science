/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
# include <stdio.h>  
# include <string.h>  
# include <stdlib.h>  
  
typedef struct node {  
    int value;    
    char ch;  
    struct node  * link;  
}NODE;  
// 定义链表中每一个节点的内容；  
  
NODE * phead;  
// 生成正序的带有头节点的链表，并对于每一个节点分别读入整型数字与字符；  
  
void Creat(int n){  
    NODE * p,*q;  
    int v; char c;  
    q =(NODE *) malloc(sizeof(NODE));  
    q->link = NULL;  
    phead = q;  
    int i;  
    for(i=1; i<=n;i++){  
        scanf("%d %c",&v,&c);  
        p = (NODE *)malloc(sizeof(NODE));  
        p->value = v;  
        p->ch = c;  
        p->link = NULL;  
        q->link = p;   
        q = q->link;  
    }          
}  
  
// 删除不符合要求的节点-------需要补全  
void Delete(void);  
  
// 打印链表中节点内容；  
void PrintNode(NODE * h){  
    // printf("Print Node\n");  
    NODE * q=h;  
    q=q->link;  
    while(q!=NULL){  
        printf("%d %c\n",q->value,q->ch);  
        q=q->link;  
    }  
}  
  
int main(){  
    int n,i,value,c;  
    scanf("%d",&n);  
    Creat(n);  
      
    Delete();  
    PrintNode(phead);  
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

void Delete(void) {
	NODE *p, *q;
	
	for (p = phead->link, q = NULL; p != NULL; ) {
		if (p->value % 2 == 1 || p->ch == 'a' || p->ch == 'e' || p->ch == 'i' || p->ch == 'o' || p->ch == 'u') {
			if (q == NULL) {
				phead->link = p->link;
				p = p->link;
			} else {
				NODE *curr = p;
				q->link = p->link;
				p = p->link;
				free(curr);
			}
		} else {
			q = p;
			p = p->link;
		}
	}
}  



