#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <malloc.h>  
  
//����ṹ��  
typedef struct list  
{  
    char data;  
    struct list *next;  
}*List,LNode;  
  
//��������  
List init_list(List head);  
int chkPalindrome(List head);  
  
int main()  
{  
    List head;    
    head = (LNode*)malloc(sizeof(LNode));     
    head->next = NULL;  
    head = init_list(head);   
    if(chkPalindrome(head))   
        printf("���������л��Ľṹ!\n");   
    else      
        printf("���������޻��Ľṹ!\n");  
  
}  
  
//�����ʼ������  
List init_list(List head)  
{  
    int i = 0;    
    List p = head;    
      
    char chain[1000];  
    memset(chain, 0, 1000 * sizeof(char));  
    gets(chain);  
          
    while(chain[i]!='\0')     
    {     
        List s;       
        s = (LNode*)malloc(sizeof(LNode));        
        s->data = chain[i];        
        s->next = NULL;        
        p->next = s;       
        p = p->next;       
        i++;          
    }     
    return head->next;     
}

int chkPalindrome(List head) {
	List p;
	char s[1001];
	int i = 0;
	for (p = head; p; p = p->next) {
		s[i] = p->data;
		i ++;
	}
	s[i] = '\0';
	int len = strlen(s);
	
	int left, right;
	for (left = 0, right = len - 1; left < right; left ++, right --) {
		if (s[left] != s[right]) {
			return 0;
		}
	} 
	
	return 1;
	
}

