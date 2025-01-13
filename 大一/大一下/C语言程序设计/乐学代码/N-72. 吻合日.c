#include <stdio.h>

int day_of_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int is_lunar(int y);
int weekday(int y, int m, int d);
void judge_spec_day(int y, int m, int *spec_day);
void count_spec_day(int y1, int y2, int m1, int m2, int d1, int d2, int *spec_day);



int main()
{
	int y1, m1, d1, y2, m2, d2;
	
//	printf("%d", weekday(2024, 5, 26));
	
	while (scanf("%d %d %d", &y1, &m1, &d1) != EOF){
		scanf("%d %d %d", &y2, &m2, &d2);
		int spec_day[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		
		
		count_spec_day(y1, y2, m1, m2, d1, d2, spec_day);
		
		
		
		int all_spec = 0, i;
		for (i = 1; i <= 7; i ++){
			all_spec += spec_day[i];
		} 
		
		printf("%d", all_spec);
		for (i = 1; i <= 7; i ++)    printf(" %d", spec_day[i]);
		printf("\n");
	} 
	return 0;
}


int weekday(int y, int m, int d){
	int st = 0;
	
	st += 365 * (y - 1900);   // years
	if (st > 1901)    st += (y - 1901) / 4;     // lunar years
	
	// months this year
	int i;
	for (i = 1; i < m; i ++){
		st += day_of_month[i];
	}
	
	if (m > 2 && is_lunar(y))    st ++;   // this year is lunar
	
	st += d; // days this month
	if (y == 2100 && m > 2){
		st --;
	}
	
	st %= 7;
	if (st == 0)    st = 7;
	return st;
}


int is_lunar(int y){
	if (y % 400 == 0){
		return 1;
	} else if (y % 100 == 0){
		return 0;
	} else if (y % 4 == 0){
		return 1;
	} else {
		return 0;
	}
}


void count_spec_day(int y1, int y2, int m1, int m2, int d1, int d2, int *spec_day){
	while (y1 <= y2){
		if (y1 < y2){
			while (m1 <= 12){
				while (d1 <= day_of_month[m1]){
					if (d1 % 10 == weekday(y1, m1, d1)){
						spec_day[d1 % 10] ++;
					}
					d1 ++;
				}
				d1 = 1;
				m1 ++;
			}
			m1 = 1;
		} else{
			while (m1 < m2){
				while (d1 <= day_of_month[m1]){
					if (d1 % 10 == weekday(y1, m1, d1)){
						spec_day[d1 % 10] ++;
					}
					d1 ++;
				}
				d1 = 1;
				m1 ++;
			}
			
			while (d1 < d2){
				if (d1 % 10 == weekday(y1, m1, d1)){
						spec_day[d1 % 10] ++;
				}
				d1 ++;
			}
		}
		
		y1 ++;
	}
	
	
	




//	int y, m, d;
//	
//	if (y1 == y2){
//		if (m1 == m2){
//			for (d = d1; d < d2; d ++){
//				if (d % 10 == weekday(y2, m2, d)){
//					spec_day[d % 10] ++;
//				}
//			} 
//		} else {
//			// this month
//			for (d = d1; d <= day_of_month[m1]; d ++){
//				if (d % 10 == weekday(y1, m1, d)){
//					spec_day[d % 10] ++;
//				}
//			}
//			
//			for (m = m1 + 1; m < m2; m ++){
//				judge_spec_day(y2, m, spec_day);
//			}
//			
//			for (d = 1; d < d2; d ++){
//				if (d % 10 == weekday(y2, m2, d)){
//				spec_day[d % 10] ++;
//				}
//			}
//		}
//	} else{
//		// this month
//		for (d = d1; d <= day_of_month[m1]; d ++){
//			if (d % 10 == weekday(y1, m1, d)){
//				spec_day[d % 10] ++;
//			}
//		} 
//		
//		for (y = y1; y < y2; y ++){		
//			// remaining months this year
//			for (m = (y > y1) ? 1 : m1 + 1; m <= 12; m ++){
//				judge_spec_day(y, m, spec_day);
//			}
//		}
//		
//		// in y2
//		for (m = 1; m < m2; m ++){
//			judge_spec_day(y2, m, spec_day);
//		}
//		
//		for (d = 1; d < d2; d ++){
//			if (d % 10 == weekday(y2, m2, d)){
//				spec_day[d % 10] ++;
//			}
//		}
//	}
//	
//
	
}


void judge_spec_day(int y, int m, int *spec_day){
	int i;
	
	if (weekday(y, m, 1) == 1 || weekday(y, m, 11) == 1 || weekday(y, m, 21) == 1){
		for (i = 1; i <= 7; i ++){
			spec_day[i] ++;
		}
	}
	
	if (day_of_month[m] == 31){
		if (weekday(y, m, 31) == 1){
			spec_day[1] ++;
		}
	}
}



