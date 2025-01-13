#include <stdio.h>

void swap(int *a, int *b);
int partition(int a[], int low, int high);
void quickSort(int a[], int low, int high);



int main(){
	int n, k, i, p;
	scanf("%d %d", &n, &k);
	
	int card[n];
	for (i = 0; i < n; i ++){
		scanf("%d", &card[i]);
	}
	
	quickSort(card, 0, n - 1);
	
	int comp = 0; // cards needed to compensate
	for (p = 0; p < n - 1; p ++){		
		comp += (p + 1) * (card[p + 1] - card[p]);
		if (comp >= k){
			break;
		}

	}

	int set, remain_money, my_card;   // sets of cards
	if (comp > k){
		set = card[p];  // 组数 
		my_card = n - p - 1;  // 给朋友后剩余手牌种类数 
		comp -= (p + 1) * (card[p + 1] - card[p]);  // 已分配卡牌数 
		
		int added = 0;
		while (comp < k){
			comp += p + 1; 
			set ++;
			added = 1;
		}
		if (added == 1){
			comp -= p + 1; 
			set --;
		}
		
		remain_money = k - comp;
		my_card += remain_money;
		
		printf("%d %d\n", set, my_card);
	} else if (comp == k){
		while (p < n - 2 && card[p + 1] == card[p +2]){
			p ++;
		}
		
		set = card[p + 1];
		remain_money = 0;
		my_card = n - p - 2;
		
		printf("%d %d\n", set, my_card);
	} else{
		remain_money = k - comp;
		int more_set = remain_money / n;
		my_card = remain_money % n;
		set = card[p] + more_set;
		
		printf("%d %d\n", set, my_card);
	}
	
	return 0;
}



int partition(int a[], int low, int high){
	int pivot = a[high];
	int i = low - 1;
	int j;
	
	for (j = low; j < high; j ++){
		if (a[j] < pivot){
			i ++;
			swap(&a[i], &a[j]);
		}
	}
	
	swap(&a[i + 1], &a[high]);
	return i + 1;
}

void quickSort(int a[], int low, int high){
	if (low < high){
		int pi = partition(a, low, high);
		
		quickSort(a, low, pi - 1);
		quickSort(a, pi + 1, high); 
	}
}

void swap(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = t;
}



