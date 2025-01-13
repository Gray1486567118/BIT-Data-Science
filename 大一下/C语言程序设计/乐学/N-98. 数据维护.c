#include <stdio.h>

struct student {
	int num;
	char sex;
	double grade;
};




int n;

void insert(int pos, struct student S[], int num, char sex, double grade);
void del(int pos, struct student S[]);
void search(int pos, struct student S[]);


int main() {
	scanf("%d", &n);
	
	// input
	struct student S[30000];
	int i;
	for (i = 1; i <= n; i ++) {
		scanf("%d %c %lf", &S[i].num, &S[i].sex, &S[i].grade);
	}
	
	int oper, pos;
  	while (scanf("%d", &oper) != EOF) {
		scanf("%d", &pos);
		if (oper == 1) {
			int num;
			char sex;
			double grade;
			scanf("%d %c %lf", &num, &sex, &grade);
			
			insert(pos, S, num, sex, grade);
		} else if (oper == 2) {
			del(pos, S);
		} else if (oper == 3) {
			search(pos, S);
		}
	}
	
	return 0;
}


void insert(int pos, struct student S[], int num, char sex, double grade) {
	int i;
	for (i = n; i > pos; i --) {
		S[i + 1] = S[i];
	}
	
	S[pos + 1].num = num;
	S[pos + 1].sex = sex;
	S[pos + 1].grade = grade;
	
	n ++;
}

void del(int pos, struct student S[]) {
	int i;
	for (i = pos; i <= n; i ++) {
		S[i] = S[i + 1];
	}
	
	n --;
}

void search(int pos, struct student S[]) {
	printf("%d %c %.1lf\n", S[pos].num, S[pos].sex, S[pos].grade);
}
