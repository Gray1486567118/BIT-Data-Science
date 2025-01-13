#include <stdio.h>    
    
unsigned long long int array[20], subset[20];    
unsigned long long int maxXor = 0;    
int n;    
    
unsigned long long int xorSum(unsigned long long int arr[], int length) {    
    unsigned long long int result = 0;    
    for (int i = 0; i < length; i++)    
        result ^= arr[i];    
    return result;    
}    
    
void findMaxXor(int index, unsigned long long int subset[], int subsetLength, unsigned long long int* maxXor)     
{    
    if (index == n) {    
        unsigned long long int currentXor = xorSum(subset, subsetLength);    
        *maxXor = *maxXor < currentXor ? currentXor : *maxXor;    
        return;    
    }    
    
    subset[subsetLength] = array[index];    
    findMaxXor(index + 1, subset, subsetLength + 1, maxXor);    
    
    findMaxXor(index + 1, subset, subsetLength, maxXor);    
}    
    
int main()     
{    
    
    scanf("%d", &n);    
    for (int i = 0; i < n; i++)    
        scanf("%lld", &array[i]);    
    findMaxXor(0, subset, 0, &maxXor);    
    printf("%lld\n", maxXor);    
}
