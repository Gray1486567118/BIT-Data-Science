#include <stdio.h>
#include <math.h>

void schmidt(int n, int d, double vector[][d], double result[][d]);
double dot_pro(double *v1, double *v2, int d);
void print_vector(double *v, int d);

int main()
{
	int n, d;
	scanf("%d %d", &n, &d);
	
	double vector[n][d];    // n行d列 每行一个向量
	int i, j;
	for (i = 0; i < n; i ++){
		for (j = 0; j < d; j ++){
			scanf("%lf", &vector[i][j]);
		}
	}  
	
	double result[n][d];
	
	schmidt(n, d, vector, result);
	
	for (i = 0; i < n; i ++){
		print_vector(result[i], d);
	}
	
	
	 
	return 0;
}



void schmidt(int n, int d, double vector[][d], double result[][d]){
	int i, j, k;
	for (i = 0; i < n; i ++){
		for (j = 0; j < d; j ++){
			result[i][j] = vector[i][j];
		}
		
		// 正交化 
		for (j = 0; j < i; j ++){
			double dp1 = dot_pro(vector[i], result[j], d);
			double dp2 = dot_pro(result[j], result[j], d);
			double dp = dp1 / dp2;
			
			for (k = 0; k < d; k ++){
				result[i][k] -= dp * result[j][k];
			}
		}
		
		// 规范化
		double norm = sqrt(dot_pro(result[i], result[i], d));
		for (j = 0; j < d; j ++){
			result[i][j] /= norm;
		}
	}
	
} 

double dot_pro(double *v1, double *v2, int d){
	double result = 0.0;
	int i; 
	for (i = 0; i < d; i ++){
		result += v1[i] * v2[i];
	}
	
	return result;
}

void print_vector(double *v, int d){
	int i;
	for (i = 0; i < d - 1; i ++){
		printf("%.2lf ", v[i]);
	} 
	
	printf("%.2lf\n", v[i]);
}
