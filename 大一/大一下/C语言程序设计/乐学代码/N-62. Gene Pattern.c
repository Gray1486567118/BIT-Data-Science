#include<stdio.h>  
void _remove();  
int if_same();  
  
int n;  
int main()  
{  
    scanf("%d", &n);  
      
    int a[101][n];  
    int j=0;  
    while(scanf("%d",&a[j][0])!=EOF){  
        for(int i=1;i<n;i++){  
            scanf("%d",&a[j][i]);  
        }  
        j++;  
    }  
      
    int copy[j][n];  
    int count=0, found;  
    for(int k=0;k<n;k++){  
        for(int i1=0;i1<j;i1++){  
            for(int i2=0;i2<n;i2++){  
                copy[i1][i2]=a[i1][i2];  
            }  
        }  
        _remove(copy, j, k);  
        if(if_same(copy, j)) {  
            found=a[0][k];  
            count++;  
        }  
    }  
      
    if(count==1) printf("%d\n", found);  
    else printf("-1\n");  
      
    return 0;  
}  
      
      
void _remove(int (*a)[n],int lines, int k)  
{  
    for(int i=1;i<lines;i++){  
        for(int j=0;j<n;j++){  
            if(a[i][j]==a[0][k]){  
                for(int i1=j;i1<n-1;i1++) a[i][i1]=a[i][i1+1];  
                break;  
            }  
        }  
        a[i][n-1]=0;  
    }  
      
    for(int i=k;i<n-1;i++) a[0][i]=a[0][i+1];  
    a[0][n-1]=0;  
}  
  
int if_same(int (*a)[n], int lines)  
{  
    int i1, i2;  
    for(i1=1;i1<lines;i1++){  
        for(i2=0;i2<n;i2++){  
            if(a[0][i2]!=a[i1][i2]) return 0;  
        }  
    }  
    return 1;  
}
