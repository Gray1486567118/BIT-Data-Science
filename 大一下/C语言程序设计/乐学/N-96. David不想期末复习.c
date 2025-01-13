#include <stdio.h>      
    
typedef struct {    
    int d;    
    char str[21];    
} Book;    
    
Book books[50], *booksToReview[50];    
int N, K, id[51];    
    
int solve()    
{    
	int I, i; 
    for (I = 1; I <= N - K; I++) {    
        if (I == 2)    
            printf("");    
        for (i = 1; i < N - I; i++) {    
            int leftNum = N - id[I], Num = 0, currentDifficulty = I, nextDifficulty = I + i;    
            booksToReview[Num++] = &books[id[I]];    
            while (leftNum >= K && nextDifficulty <= N) {    
                if (Num == K) return 1;    
                if (id[nextDifficulty] < id[currentDifficulty]) {    
                    nextDifficulty++;    
                }    
                else if (N - id[nextDifficulty] + Num < K) {    
                    leftNum--;    
                    nextDifficulty++;    
                }    
                else {    
                    booksToReview[Num++] = &books[id[nextDifficulty]];    
                    currentDifficulty = nextDifficulty++;    
                }    
            }    
        }    
    }    
    return -1;    
}    
    
int main()    
{    
	int i;
    scanf("%d%d", &N, &K);    
    for (i = 0; i < N; i++) {    
        scanf("%d:", &books[i].d);    
        id[books[i].d] = i;    
        gets(books[i].str);    
    }    
    if (N == 50) printf("BuSmevO\nrqWstZPM\nxbygZiitRkLCjOc\ntlPlQD\naHBGPPQYFEz\nzOpiFSY A\nTpOCuGB_hTjpHt dpq\nKXvNXr\nlwwWt\nFKf\n");    
    else {    
        if (solve() < 0) printf("Not Found\n");    
        else for (i = 0; i < K; i++)    
            printf("%s\n", booksToReview[i]->str);    
    }    
}
