#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX_TELE 1505
#define MAX_INPUT 25
#define MAX_BITS 250005

typedef unsigned long long ull;
typedef long long ll;

struct dupli {
    int a[2]; 
};


int comp(const void *a, const void *b);
void standardize(char *tmp);
int is_invalid(char *tmp);
int calculate(char *tmp);
void check_and_store(int sum, unsigned char *bit_array, struct dupli *tele, int *tele_count);
void output(int error_flag, struct dupli *tele, int tele_count);

int main() {
    struct dupli tele[MAX_TELE] = {0};    
    unsigned char bit_array[MAX_BITS] = {0};    
    char tmp[MAX_INPUT];   
    int tele_count = 0;     
    int error_flag = 0;     

    printf("Error:\n");
    
    
    while (fgets(tmp, sizeof(tmp), stdin) != NULL) {
        tmp[strcspn(tmp, "\n")] = '\0'; 
        
        
        if (tmp[0] != '3' && tmp[0] != '6') {
            printf("%s\n", tmp);
            error_flag = 1;
            continue;
        }

        
        if (is_invalid(tmp)) {
            printf("%s\n", tmp);
            error_flag = 1;
            continue;
        }

        
        standardize(tmp);

        
        int number = calculate(tmp);

        
        check_and_store(number, bit_array, tele, &tele_count);
    }

    
    if (!error_flag) {
        printf("Not found.\n");
    }

    
    output(error_flag, tele, tele_count);

    return 0;
}


int comp(const void *a, const void *b) {
    return(((struct dupli *)a)->a[0] - ((struct dupli *)b)->a[0]);
}


void standardize(char *tmp) {
    int len = strlen(tmp);
    for (int i = 0; i < len; i++) {
        switch (tmp[i]) {
            case 'A': case 'B': case 'C': tmp[i] = '2'; break;
            case 'D': case 'E': case 'F': tmp[i] = '3'; break;
            case 'G': case 'H': case 'I': tmp[i] = '4'; break;
            case 'J': case 'K': case 'L': tmp[i] = '5'; break;
            case 'M': case 'N': case 'O': tmp[i] = '6'; break;
            case 'P': case 'R': case 'S': tmp[i] = '7'; break;
            case 'T': case 'U': case 'V': tmp[i] = '8'; break;
            case 'W': case 'X': case 'Y': tmp[i] = '9'; break;
        }
    }
}


int is_invalid(char *tmp) {
    int len = strlen(tmp);
    for (int i = 0; i < len; i++) {
        if (tmp[i] == 'Q' || tmp[i] == 'Z') return 1;
    }
    return 0;
}


int calculate(char *tmp) {
    int x = 0, y = 0, tt = 0;
    for (int i = 0; i < strlen(tmp); i++) {
        if (tmp[i] != '-') {
            tt++;
            if (tt < 4) {
                x += (tmp[i] - '0') * pow(10.0, 3 - tt);
            } else {
                y += (tmp[i] - '0') * pow(10.0, 7 - tt);
            }
        }
    }
    return 10000 * x + y;
}


void check_and_store(int sum, unsigned char *bit_array, struct dupli *tele, int *tele_count) {
    int t = sum % (sum < 4000000 ? 3000000 : 6000000);
    int offset = sum < 4000000 ? t : t % 6000000;
    unsigned char *array = sum < 4000000 ? bit_array : bit_array + MAX_BITS / 2;

    if ((array[offset / 4] & (1 << (offset % 4))) != 0) {
        int found = 0;
        for (int j = 0; j < *tele_count; j++) {
            if (tele[j].a[0] == sum) {
                tele[j].a[1]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            tele[*tele_count].a[0] = sum;
            tele[*tele_count].a[1] = 1;
            (*tele_count)++;
        }
    } else {
        array[offset / 4] |= 1 << (offset % 4);
    }
}


void output(int error_flag, struct dupli *tele, int tele_count) {
    if (!error_flag) {
        printf("Not found.\n");
    }
    printf("\nDuplication:\n");
    
    qsort(tele, tele_count, sizeof(struct dupli), comp);
    int duplication_flag = 0;
    
    for (int i = 0; i < tele_count; i++) {
        if (tele[i].a[1] > 0) {
            duplication_flag = 1;
            printf("%03d-%04d %d\n", tele[i].a[0] / 10000, tele[i].a[0] % 10000, tele[i].a[1] + 1);
        }
    }
    
    if (!duplication_flag) {
        printf("Not found.\n");
    }
}

