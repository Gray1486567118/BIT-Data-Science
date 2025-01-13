/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
#define N 100010
typedef struct Edge{
	int to;
	struct Edge* nxt;
}EDGE;
EDGE* head[N];
void Add_Edge(int u, int v);
void Print(EDGE* head);
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) head[i] = NULL;
	for(int i = 1; i <= m; ++i){
		int u, v;
		scanf("%d%d", &u, &v);
		Add_Edge(u, v);
	}
	for(int i = 1; i <= n; ++i)
		printf("%d: ", i), Print(head[i]);
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

void Add_Edge(int u, int v)
{
	EDGE *p = (EDGE*)malloc(sizeof(EDGE));
	if(p == NULL)
		exit(1);
	p -> to = v;
	p -> nxt = NULL;
	if(head[u] == NULL)
		head[u] = p;
	else
	{
		EDGE *current = head[u];
		p -> nxt = current;
		head[u] = p;
	}
	return;
}

void Print(EDGE* head)
{
	if(head == NULL)
		printf("\n");
	else
	{
		EDGE *current = head;
		if(current -> nxt == NULL)
			printf("%d\n", current -> to);
		else
		{
			printf("%d", current -> to);
			current = current -> nxt;
			while(current -> nxt != NULL)
			{
				printf(" %d", current -> to);
				current = current -> nxt;
			}
			printf(" %d\n", current -> to);
		}
	}
	return;
}

//教训1：链表数组；
//教训2：如何处理没有表头结点的链表？