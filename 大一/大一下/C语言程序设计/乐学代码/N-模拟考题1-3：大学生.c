#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Student{
	char name[6];
	struct Student *left;
	struct Student *right;
} S;

S* create(char *name);
void delete_student(S *student);


int main() {
	int n, i, j;
	scanf("%d", &n);
	
	
	// init
	int del[n];
	for (i = 0; i < n; i ++) {
		scanf("%d", &del[i]);
	}
	
	S *student[n + 2];
	student[0] = create("eijuy");
	student[n + 1] = create("vrqfb");
	
	for (i = 1; i <= n; i ++) {
		char name[6];
		scanf("%s", name);
		student[i] = create(name);
	}
	
	for (i = 0; i <= n; i ++) {
		student[i]->right = student[i + 1]; 
		student[i + 1]->left = student[i];
	}
	
	// del
	for (i = 0; i < n; i ++) {
		printf("%s %s\n", student[del[i]]->left->name, student[del[i]]->right->name);
		
		student[del[i]]->left->right = student[del[i]]->right;
		student[del[i]]->right->left = student[del[i]]->left;
		
		delete_student(student[del[i]]);
	}
	
	 
	return 0;
}


S* create(char *name) {
	S *new_student = (S*) malloc(sizeof(S));
	strcpy(new_student->name, name);
	new_student->left = NULL;
	new_student->right = NULL;
	return new_student;
}

void delete_student(S *student) {
	free(student);
}

