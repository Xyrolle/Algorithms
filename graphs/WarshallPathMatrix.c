#include <stdio.h>
#include <stdlib.h>

int* alloc(int* mat, int n);

void printAdjMat(int* mat, int n);
void inputAdjMat(int* mat, int n);

void pathMatrix(int* mat, int n);

int main(void) {

	int n;
	printf("N: ");
	scanf("%d", &n);

	int* mat = alloc(mat, n);

	inputAdjMat(mat, n);

	printf("Adjacency matrix \n");
	printAdjMat(mat, n);

	printf("Path matrix \n");
	pathMatrix(mat, n);
	printAdjMat(mat, n);
	
  return 0;
}

// colon major
int* alloc(int *mat, int n) {
	mat = calloc(n * n,sizeof(int));
	return mat;
}

void printAdjMat(int* mat, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d", *(mat + n * i + j));
		}
		printf("\n");
	}

}

void inputAdjMat(int* mat, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &*(mat + n * i + j));
		}
		printf("-------\n");
	}
}

void pathMatrix(int* mat, int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				*(mat + n * i + j) = *(mat + n * i + j) || (*(mat + n * i + k) && *(mat + n * k + i)); 
			}
		}
	}
}
