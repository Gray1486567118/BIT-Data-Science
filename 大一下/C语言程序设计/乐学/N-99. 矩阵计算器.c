void matrix_add(double matrix[3][3], double other[3][3])         
{         
    int i, j;         
    for (i = 0; i < 3; i++)         
        for (j = 0; j < 3; j++)         
            matrix[i][j] += other[i][j];         
}         
void matrix_subtract(double matrix[3][3], double other[3][3])         
{         
    int i, j;         
    for (i = 0; i < 3; i++)         
        for (j = 0; j < 3; j++)         
            matrix[i][j] -= other[i][j];         
}         
void matrix_multiply(double matrix[3][3], double other[3][3])         
{         
    double result[3][3] = {0};       
    int i, j, k;         
    for (i = 0; i < 3; i++)         
        for (j = 0; j < 3; j++)         
            for (k = 0; k < 3; k++)         
                result[i][j] += matrix[i][k] * other[k][j];      
    matrix_copy(matrix, result);         
} void matrix_power(double matrix[3][3], int left_index) {    
    double result[3][3] = {0};    
    double base[3][3];    
    for (int i = 0; i < 3; i++) {    
        result[i][i] = 1;    
    }    
    matrix_copy(base, matrix);    
    while (left_index > 0) {    
        if (left_index % 2 == 1) {    
            matrix_multiply(result, base);    
        }    
        matrix_multiply(base, base);    
        left_index /= 2;    
    }    
    matrix_copy(matrix, result);    
}    
void matrix_inverse(double matrix[3][3])         
{         
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -       
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +       
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);      
    double inv[3][3];       
    inv[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) / det;       
    inv[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / det;       
    inv[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / det;       
    inv[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / det;       
    inv[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / det;       
    inv[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) / det;       
    inv[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) / det;       
    inv[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) / det;       
    inv[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / det;     
    matrix_copy(matrix, inv);       
} 
