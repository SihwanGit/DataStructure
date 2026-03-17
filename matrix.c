#include "matrix.h"

void main()
{
	int a[ROW][COL] = { { 1,0,0 }, { 1,0,0 }, { 1,0,0 } };
	int b[ROW][COL] = { { 1,1,1 },{ 0,0,0 },{ 0,0,0 } };
	int c[ROW][COL] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };

	printf("matrix a : \n");
	matrix_print(a);

	printf("matrix b : \n");
	matrix_print(b);

	printf("matrix add : a + b = c\n");
	matrix_add(a, b, c);
	matrix_print(c);

	printf("matrix mul : a * b = c\n");
	matrix_init(c);
	matrix_mult(a, b, c);
	matrix_print(c);

	printf("a transpose = a^T\n");
	matrix_init(c);
	matrix_trans(a, c);
	matrix_print(c);
}

void matrix_init(int a[ROW][COL]) //행렬 성분을 0으로 만듦
{
	int i, j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			a[i][j] = 0;
}

void matrix_add(int a[ROW][COL], int b[ROW][COL], int c[ROW][COL]) { //행렬 합
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void matrix_mult(int a[ROW][COL], int b[ROW][COL], int c[ROW][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			for (int k = 0; k < 3; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}


void matrix_trans(int a[ROW][COL], int c[ROW][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			c[j][i] = a[i][j];
		}
	}
}

void matrix_print(int a[ROW][COL]) { //행렬 출력
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}