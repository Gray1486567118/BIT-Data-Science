#include <stdio.h>    
#include <stdlib.h>    
    
typedef struct {    
    int x, y;    
} Pos;    
    
typedef struct {    
    int x, y;    
    char direction;    
} Node;    
    
char map[1000][1000], prev_dir[1000][1000], result1[2000], result2[2000], dir_chars[4] = { 'D', 'L', 'R', 'U' };    
int n, m, prev[1000][1000], directions[4][2] = { {1, 0}, {0, -1}, {0, 1}, {-1, 0} }, visited[1000][1000];    
Pos start, end1, end2;    
    
void solve(Pos end, char* result) {    
    int head = 0, tail = 0;    
    Node* queue = malloc(sizeof(Node) * 1000000);    
    
    memset(visited, 0, sizeof(visited));    
    memset(prev, -1, sizeof(prev));    
    memset(prev_dir, 0, sizeof(prev_dir));    
    
    queue[tail++] = (Node){ start.x, start.y, '\0' };    
    visited[start.x][start.y] = 1;    
    
    while (head < tail) {    
        Node node = queue[head++];    
        if (node.x == end.x && node.y == end.y) {    
            int len = 0;    
            for (Pos p = end; prev[p.x][p.y] != -1; p = (Pos){ prev[p.x][p.y] / m, prev[p.x][p.y] % m }) {    
                result[len++] = prev_dir[p.x][p.y];    
            }    
            result[len] = '\0';    
            for (int i = 0; i < len / 2; ++i) {    
                char temp = result[i];    
                result[i] = result[len - 1 - i];    
                result[len - 1 - i] = temp;    
            }    
            return;    
        }    
        for (int i = 0; i < 4; ++i) {    
            int newX = node.x + directions[i][0];    
            int newY = node.y + directions[i][1];    
            if (newX >= 0 && newX < n && newY >= 0 && newY < m && map[newX][newY] != '#' && !visited[newX][newY]) {    
                visited[newX][newY] = 1;    
                queue[tail++] = (Node){ newX, newY, dir_chars[i] };    
                prev[newX][newY] = node.x * m + node.y;    
                prev_dir[newX][newY] = dir_chars[i];    
            }    
        }    
    }    
    strcpy(result, "-1");    
    free(queue);    
}    
    
int main() {    
    scanf("%d%d", &n, &m);    
    getchar();    
    for (int i = 0; i < n; i++) {    
        for (int j = 0; j < m; j++) {    
            scanf("%c", &map[i][j]);    
            if (map[i][j] == 'S') start = (Pos){ i, j };    
            if (map[i][j] == '1') end1 = (Pos){ i, j };    
            if (map[i][j] == '2') end2 = (Pos){ i, j };    
        }    
        getchar();    
    }    
    solve(end1, result1);    
    solve(end2, result2);    
    printf("%s\n%s\n", result1, result2);    
} 
