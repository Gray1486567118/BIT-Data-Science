#include <stdio.h>    
    
int index = 0;    
    
typedef struct {    
    int id;    
    int left;    
    int right;    
} Interval;    
    
void getA(int id, int l, int r, int L, int R, Interval result[]) {    
    if (L > R || l > r) {    
        return;    
    }    
    if (l == L && r == R) {    
        result[index].id = id;    
        result[index].left = l;    
        result[index].right = r;    
        index++;    
        return;    
    }    
    int m = (l + r) / 2;    
    if (R <= m) {    
        getA(2 * id, l, m, L, R, result);    
    }    
    else if (L > m) {    
        getA(2 * id + 1, m + 1, r, L, R, result);    
    }    
    else {    
        getA(2 * id, l, m, L, m, result);    
        getA(2 * id + 1, m + 1, r, m + 1, R, result);    
    }    
}    
    
int main() {    
    int N, L, R;    
    scanf("%d %d %d", &N, &L, &R);    
    
    Interval result[1000];    
    
    getA(1, 1, N, L, R, result);    
    
    for (int i = 0; i < index; i++)    
        printf("%d %d %d\n", result[i].id, result[i].left, result[i].right);    
    
} 
