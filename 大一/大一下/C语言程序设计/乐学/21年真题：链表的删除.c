/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
# include <stdio.h>  
# include <string.h>  
# include <stdlib.h>  
  
typedef struct node {  
    int value;    
    char ch;  
    struct node  * link;  
}NODE;  
// ����������ÿһ���ڵ�����ݣ�  
  
NODE * phead;  
// ��������Ĵ���ͷ�ڵ������������ÿһ���ڵ�ֱ���������������ַ���  
  
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
  
// ɾ��������Ҫ��Ľڵ�-------��Ҫ��ȫ  
void Delete(void);  
  
// ��ӡ�����нڵ����ݣ�  
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



