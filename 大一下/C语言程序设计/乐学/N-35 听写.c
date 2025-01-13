#include <stdio.h>

void swap(int *a, int *b);
void quickSort(int arr[], int low, int high);

int main()
{
	int n, i, j;
	scanf("%d", &n);
	int A[n];
	
	for (i = 0; i < n; i ++)
	{
		scanf("%d", &A[i]);
	}
	
	
	quickSort(A, 0, n - 1);

	
	for (i = 0; i < n - 1; i ++)
	{
		printf("%d ", A[i]);
	}
	printf("%d\n", A[i]);
	return 0;
}



void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void quickSort(int arr[], int low, int high)
{
	int i = low;
	int j = high;
	if(i >= j)
	{
		return;
	}
	
	int pivot = arr[low];
	while (i != j)
	{
		while (arr[j] >= pivot && i < j)
		{
			j --;
		}
		while (arr[i] <= pivot && i < j)
		{
			i ++;
		}
		
		if (i < j)
		{
			swap(&arr[i], &arr[j]);
		}
	}
	
	swap(&arr[low], &arr[i]);
	quickSort(arr, low, i - 1);
	quickSort(arr, i + 1, high);
}
