/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node  
{   int    coef, exp;  
    struct node  *next;  
} NODE;  
  
void multiplication( NODE *, NODE * , NODE * );  
void input( NODE * );  
void output( NODE * );  
  
void input( NODE * head )  
{   int flag, sign, sum, x;  
    char c;  
  
    NODE * p = head;  
  
    while ( (c=getchar()) !='\n' )  
    {  
        if ( c == '<' )  
        {    sum = 0;  
             sign = 1;  
             flag = 1;  
        }  
        else if ( c =='-' )  
             sign = -1;  
        else if( c >='0'&& c <='9' )  
        {    sum = sum*10 + c - '0';  
        }  
        else if ( c == ',' )  
        {    if ( flag == 1 )  
             {    x = sign * sum;  
                  sum = 0;  
                  flag = 2;  
          sign = 1;  
             }  
        }  
        else if ( c == '>' )  
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
             p->next->coef = x;  
             p->next->exp  = sign * sum;  
             p = p->next;  
             p->next = NULL;  
             flag = 0;  
        }  
    }  
}  
  
void output( NODE * head )  
{  
    while ( head->next != NULL )  
    {   head = head->next;  
        printf("<%d,%d>,", head->coef, head->exp );  
    }  
    printf("\n");  
}  
  
int main()  
{   NODE * head1, * head2, * head3;  
  
    head1 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head1 );  
  
    head2 = ( NODE * ) malloc( sizeof(NODE) );  
    input( head2 );  
  
    head3 = ( NODE * ) malloc( sizeof(NODE) );  
    head3->next = NULL;  
    multiplication( head1, head2, head3 );  
  
    output( head3 );  
    return 0;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

// void multiplication(NODE* h1, NODE* h2, NODE* h3) { 
//     NODE *p1, *p2, *p3;

//     p1 = h1->next;
//     p2 = h2->next; 

//     while (p1 != NULL) { 
//         p3 = h3; 
 
//         while (p2 != NULL) { 
//             int coef = p1->coef * p2->coef;
//             int exp = p1->exp + p2->exp;
 
//             if (coef != 0) { 
//                 while (p3->next != NULL && p3->next->exp < exp) { 
//                     p3 = p3->next; 
//                 } 
 
//                 if (p3->next != NULL && p3->next->exp == exp) { 
//                     p3->next->coef += coef; 
//                 } else { 
//                     NODE* new_node = (NODE*)malloc(sizeof(NODE)); 
//                     new_node->coef = coef; 
//                     new_node->exp = exp; 
//                     new_node->next = p3->next; 
//                     p3->next = new_node; 
//                 } 
//             } 
//             p2 = p2->next;
//         } 
//         p1 = p1->next;
//     } 
 
//     p3 = h3; 

//     while (p3->next != NULL) { 
//         if (p3->next->coef == 0) { 
//             NODE* temp = p3->next; 
//             p3->next = temp->next; 
//             free(temp); 
//         } else { 
//             p3 = p3->next; 
//         } 
//     } 


//     if (h3->next == NULL) { 
//         NODE* new_node = (NODE*)malloc(sizeof(NODE)); 
//         new_node->coef = 0; 
//         new_node->exp = 0; 
//         new_node->next = NULL; 
//         h3->next = new_node; 
//     } 
// }  

void multiplication(NODE* h1, NODE* h2, NODE* h3)  {
    NODE *p1 = h1->next;
    
    while (p1 != NULL) {
        NODE *p2 = h2->next;
        NODE *p3 = h3;

        while (p2 != NULL) {
            int newCoef = p1->coef * p2->coef;
            int newExp = p1->exp + p2->exp;

            if (newCoef != 0) {
                while (p3->next != NULL && p3->next->exp < newExp) {
                    p3 = p3->next;
                }

                if (p3->next != NULL && p3->next->exp == newExp) {
                    p3->next->coef += newCoef;
                } else {
                    NODE* newNode = (NODE*)malloc(sizeof(NODE));
                    newNode->coef = newCoef;
                    newNode->exp = newExp;
                    newNode->next = p3->next;
                    p3->next = newNode;
                }
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    NODE *current = h3;
    while (current->next != NULL) {
        if (current->next->coef == 0) {
            NODE* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    if (h3->next == NULL) {
        NODE* zeroNode = (NODE*)malloc(sizeof(NODE));
        zeroNode->coef = 0;
        zeroNode->exp = 0;
        zeroNode->next = NULL;
        h3->next = zeroNode;
    }
}


// void multiplication(NODE* h1, NODE* h2, NODE* h3) 
// {
// 	NODE *p1 = h1->next;
//     NODE *p2 = h2->next;
//     NODE *p3;
	
// 	while(p1 != NULL) {
// 		p3 = h3;
		
// 		while (p2 != NULL)
// 		{
// 			int coef = p1->coef * p2->coef;
// 			int exp = p1->exp + p2->exp;
			
// 			if (coef != 0)
// 			{
// 				while(p3 != NULL && p3->next->exp < exp)
// 				{
// 					p3 = p3->next;
// 				} 
				
// 				if(p3 != NULL && p3->next->exp == exp)
// 				{
// 					p3->next->coef += coef;
// 				} else {
// 				    NODE* new_node = (NODE*)malloc(sizeof(NODE));
//                     new_node->coef = coef;
//                     new_node->exp = exp;
//                     new_node->next = p3->next;
//                     p3->next = new_node;
// 				}
// 			}
// 		    p2 = p2->next;
// 		}
// 	    p1 = p1->next;
// 	}
	
// 	p3 = h3;

// 	while(p3->next != NULL) {
// 		if(p3->next->coef == 0)
// 		{
// 			NODE* temp = p3->next;
// 			p3->next = temp->next;
// 			free(temp);
// 		}
// 		else 
// 		{
// 			p3 = p3->next;
// 		}
// 	}

// 	if (h3->next == NULL) 
// 	{
//         NODE* new_node = (NODE*)malloc(sizeof(NODE));
//         new_node->coef = 0;
//         new_node->exp = 0;
//         new_node->next = NULL;
//         h3->next = new_node;
//     }
// }


