#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int         data;  
    struct node * next;  
} NODE;  
  
void output( NODE *, int );  
void change( int, int, NODE * );  
  
void output( NODE * head, int kk )  
{   int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<kk )  
    {   printf("%d", head->next->data );  
        head = head->next;  
        k ++;  
    }  
    printf("\n");  
}  
  
int main()  
{   int n, m, k;  
    NODE * head;  
  
    scanf("%d%d%d", &n, &m, &k);  
    head = (NODE *)malloc( sizeof(NODE) );  
    head->next = NULL;  
    head->data = -1;  
    change( n, m, head );  
    output( head,k );  
    return 0;  
}  

#include <unordered_map>

void change(int n, int m, NODE *head) {
    NODE *curr = head;
    std::unordered_map<int, NODE*> n_map;
    int remainder = n;

    n *= 10;
    while (remainder != 0 && n_map.find(n) == n_map.end()) {
        int digit = n / m;

        NODE* p = (NODE*) malloc(sizeof(NODE));
        p->data = digit;
        p->next = nullptr;
        curr->next = p;
        curr = p;

        n_map[n] = p;

        remainder = n % m;
        n = remainder * 10;
    }

    if (remainder != 0) {
        curr->next = n_map[n];
    }
}

// int gcd(int a, int b) {
//     return b == 0 ? a : gcd(b, a % b);
// }

// bool is_circ_decimal(int n, int m) {
//     int g = gcd(n, m);

//     m /= g;

//     while (m % 2 == 0) {
//         m /= 2;
//     }

//     while (m % 5 == 0) { 
//         m /= 5;
//     }

//     return m != 1;
// }

// void change(int n, int m, NODE * head) {
//     NODE* curr = head;
//     double result = (double)n / m;

//     if (is_circ_decimal(n, m)) {
//         std::unordered_map<int, NODE*> n_map;
//         n *= 10;
        
        
//         while (n_map.find(n) == n_map.end()) {
//             int digit = n / m;

//             NODE* p = (NODE*) malloc(sizeof(NODE));
//             p->data = digit;
//             p->next = nullptr;
//             curr->next = p;
//             curr = p;

//             n_map[n] = p;

//             n %= m;
//             n *= 10;
//         }

//         curr->next = n_map[n];

//     } else {
//         while (result > 0) {
//             result *= 10;
//             int int_part = (int)result;
//             result -= int_part;

//             NODE * p = (NODE *)malloc(sizeof(NODE));
//             p->data = int_part;
//             p->next = nullptr;
//             curr->next = p;
//             curr = p;
//         }
//     }
// }