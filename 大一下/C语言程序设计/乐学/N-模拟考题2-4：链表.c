#include<stdio.h>  
#include<stdlib.h>  
typedef struct Node {  
    int value;  
    struct Node* next;  
}Node;  
Node* head = NULL;  
void charu(int x, int y)//����  
{  
    Node* newNode = (Node*)malloc(sizeof(Node));  
    if (newNode == NULL) {  
        printf("Memory allocation failed.\n");  
        exit(1);  
    }  
    newNode->value = y;  
    Node* p = head;  
    while (p != NULL&&p->value !=x) {//������ǿ��������Ѱ��x��λ��  
        p = p->next;  
    }  
    if (p->value != NULL) {//����ҵ���  
        newNode->next = p->next;  
        p->next = newNode;  
    }  
}  
int chaxun(int x);  
  
void shanchu(int x)  
{  
    Node* p = head;  
    while (p != NULL && p->value != x) //������ǿ��������Ѱ��x��λ��  
        p = p->next;  
    if (p != NULL && p->next != NULL) {  
        Node* q = p->next;  
        p->next = q->next;//ɾ��  
        free(q);//�ռ��ͷ�  
    }  
}  
int main()  
{  
    head = (Node*)malloc(sizeof(Node));  
    head->value = 1;//��ĿҪ���һ��Ϊ1  
    head->next = NULL;//��ʼ��  
    int n;  
    scanf("%d", &n);  
    while (n--) {  
        int m, x, y;  
        scanf("%d%d", &m, &x);  
        switch (m)  
        {  
        case 1://Ԫ�ز���  
            scanf("%d", &y);  
            charu(x, y);  
            break;  
        case 2://Ԫ�ز���  
            printf("%d\n", chaxun(x));  
            break;  
        case 3://Ԫ��ɾ��  
            shanchu(x);  
            break;  
        default:printf("Invalid operation.\n");  
        }  
    }  
    return 0;  
}  
int chaxun(int x)  
{  
    Node* p = head;  
    while (p != NULL && p->value != x) //������ǿ��������Ѱ��x��λ��  
        p = p->next;  
    if (p != NULL && p->next != NULL) {//�����û�г��������ȵĻ����ҵ���ѯ��������  
        return p->next->value;  
    }  
    else return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
