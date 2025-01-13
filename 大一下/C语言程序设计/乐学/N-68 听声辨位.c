#include<stdio.h>  
int n;  
  
int compare_value();  
void compare_index();  
  
int main(void)  
{  
    scanf("%d", &n);  
      
    long long a[n][3];  
    for(int i=0;i<n;i++){  
        scanf("%lld%lld", &a[i][0], &a[i][1]);  
        a[i][2] =i+1;  
    }  
      
    long long temp[n];  
    int count;  
    while(1){  
        count=compare_value(a, temp);  
        if(count==-1) break;  
        compare_index(temp, count);  
    }  
      
    return 0;  
}  
  
int compare_value(long long (*a)[3], long long *temp)  
{  
    int max_i=-1, count=0;  
    long long temp_v;  
    for(int i=0;i<n;i++){                //Initiate  
        if(a[i][2]!=0){  
            max_i=i;  
            break;  
        }  
    }  
    if(max_i==-1) return -1;  
      
    for(int i=0;i<n;i++){                //Compare & Choose the max  
        if(a[i][2]!=0){  
            temp_v=a[i][1]*a[max_i][0]-a[max_i][1]*a[i][0];  
            if(temp_v<0) max_i=i;  
        }  
    }  
    for(int i=0;i<n;i++){  
        temp_v=a[i][1]*a[max_i][0]-a[max_i][1]*a[i][0];  
        if(temp_v==0&&a[i][2]!=0) {  
            temp[count]=a[i][2];  
            a[i][2]=0;  
            count++;  
        }  
    }  
    return count;  
}  
  
void compare_index(long long *temp,int count)  
{  
    int m_key;  
    long long min=-1;               //Initiate                
    for(int i=0;i<count;i++){  
        for(int i=0;i<count;i++){  
            if(temp[i]!=-1){  
                min=temp[i];  
                m_key=i;  
                break;  
            }  
        }  
        if(min==-1) break;  
        for(int i=0;i<count;i++){  
            if(temp[i]<min&&temp[i]!=-1){  
                m_key=i;  
                temp[m_key]=-1;               
                min = temp[m_key];  
            }  
        }  
        printf("%lld\n", min);  
        temp[m_key]=-1;  
    }  
}
