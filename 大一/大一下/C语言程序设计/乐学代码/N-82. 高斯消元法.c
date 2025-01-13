#include <stdio.h>    
#include <stdlib.h>    
#include <math.h>    
    
const double eps = 1e-9;    
    
double calculateDet(double** M, int n) {    
    int* P = (int*)malloc(n * sizeof(int));    
    for (int i = 0; i < n; i++) {    
        P[i] = i;    
    }    
    double det = 1.0;    
    
    for (int i = 0; i < n; i++) {    
        int maxIndex = i;    
        double maxValue = abs(M[i][i]);    
        for (int j = i + 1; j < n; j++) {    
            if (abs(M[j][i]) > maxValue) {    
                maxValue = abs(M[j][i]);    
                maxIndex = j;    
            }    
        }    
    
        if (maxIndex != i) {    
            int temp = P[i];    
            P[i] = P[maxIndex];    
            P[maxIndex] = temp;    
    
            double* tempRow = M[i];    
            M[i] = M[maxIndex];    
            M[maxIndex] = tempRow;    
    
            det = -det;    
        }    
    
        det *= M[i][i];    
        if (fabs(M[i][i]) < eps) {    
            det = 0.00;    
            break;    
        }    
    
        for (int j = i + 1; j < n; j++) {    
            M[j][i] /= M[i][i];    
            for (int k = i + 1; k < n; k++) {    
                M[j][k] -= M[j][i] * M[i][k];    
            }    
        }    
    }    
    
    free(P);    
    return det;    
}    
    
int calculateRank(double** M, int row, int col) {    
    int rank = col;    
    for (int r = 0; r < rank; r++) {    
        if (fabs(M[r][r]) > eps) {    
            for (int c = 0; c < row; c++) {    
                if (c != r) {    
                    double mult = M[c][r] / M[r][r];    
                    for (int i = 0; i < rank; i++) {    
                        M[c][i] -= mult * M[r][i];    
                            
                    }    
                }    
            }    
        }    
        else {    
            char reduce = 1;    
            for (int i = r + 1; i < row; i++) {    
                if (fabs(M[i][r]) > eps) {    
                    double* temp = M[r];    
                    M[r] = M[i];    
                    M[i] = temp;    
                    reduce = 0;    
                    break;    
                }    
            }    
            if (reduce) {    
                rank--;    
                for (int i = 0; i < row; i++)    
                    M[i][r] = M[i][rank];    
            }    
            r--;    
        }    
            
    }    
        
    return rank;    
}    
    
int main() {    
    int N, T;    
    scanf("%d", &T);    
    double** A1, **A2;    
    
    for (int I = 0; I < T; I++) {    
        scanf("%d", &N);    
        A1 = (double**)malloc(N * sizeof(double*));    
        for (int i = 0; i < N; i++)    
            A1[i] = (double*)malloc(N * sizeof(double));    
        A2 = (double**)malloc(N * sizeof(double*));    
        for (int i = 0; i < N; i++)    
            A2[i] = (double*)malloc(N * sizeof(double));    
    
        for (int i = 0; i < N; i++)    
            for (int j = 0; j < N; j++) {    
                scanf("%lf", &A1[i][j]);    
                A2[i][j] = A1[i][j];    
            }    
    
        double det = calculateDet(A1, N);    
        int rank = calculateRank(A2, N, N);    
        printf("%.2lf %d %d\n", det, rank, N - rank);    
    
        for (int i = 0; i < N; i++) {    
            free(A1[i]);    
            free(A2[i]);    
        }    
        free(A1);    
        free(A2);    
    }    
}
