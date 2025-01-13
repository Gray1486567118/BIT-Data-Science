#include <stdio.h>  
#include <stdlib.h>  

typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  
  
NODE * find( NODE * , int * );  
void outputring( NODE * );  
void change( int , int , NODE * );  
void outputring( NODE * pring )  
{   NODE * p;  
    p = pring;  
    if ( p == NULL )  
        printf("NULL");  
    else  
        do  {   printf("%d", p->data);  
            p = p->next;  
        } while ( p != pring );  
    printf("\n");  
    return;  
}  
  
int main()  
{   int n, m;  
    NODE * head, * pring;  
  
    scanf("%d%d", &n, &m);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
  
    change( n, m, head );  
    pring = find( head, &n );  
    printf("ring=%d\n", n);  
    outputring( pring );  
  
    return 0;  
}  
  

#include <unordered_map>
using namespace std;

int length = 0;
bool is_circ = false;
NODE* start_cirl;
unordered_map<int, int> position_n; // 循环节终止长度

void change(int n, int m, NODE *head) {
    NODE *curr = head;
    unordered_map<int, NODE*> n_map;
    int remainder = n;

    n *= 10;
    while (remainder != 0 && n_map.find(n) == n_map.end()) {
        int digit = n / m;

        NODE* p = (NODE*) malloc(sizeof(NODE));
        p->data = digit;
        p->next = nullptr;
        curr->next = p;
        curr = p;

        length ++;
        position_n[n] = length;
        n_map[n] = p;

        remainder = n % m;
        n = remainder * 10;
    }

    if (remainder != 0) {
        curr->next = n_map[n];
        start_cirl = n_map[n];
        length = length - position_n[n] + 1;
        is_circ = true;
    }
}
 
NODE * find( NODE * head, int * n ) { 
    if (is_circ) {
        *n = length;
        return start_cirl;
    } else {
        *n = 0;
        return NULL;
    }
} 
