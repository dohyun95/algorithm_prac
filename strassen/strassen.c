#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNING
#pragma warning(disable:4996)

void add(int **a, int **b, int size, int **c); //덧셈함수
void sub(int **a, int **b, int size, int **c); //뺄셈함수
void strMul(int **a, int **b, int size, int **c); //슈트라센 행렬곱셈 함수


int main(void)
{
	int rowA, columnA, rowB, columnB; //rowA=A행렬의행, columnA=A행렬의열, rowB=B행렬의행, columnB=B행렬의열
	int aMAX, bMAX; //행렬의 행,열 중 큰사이즈
	int zero = 0;
	int **A, **B, **newA, **newB, **C; //A,B는 입력받는 행렬이고 newA, newB는 입력받고 새로 저장되는행렬, C는 곱셈결과행렬

	printf("행렬A 사이즈 입력하세요:");
	scanf("%d %d", &rowA, &columnA);

	A = (int**)malloc(sizeof(int*)*rowA);
	for (int i = 0; i < rowA; i++){
		A[i] = (int*)malloc(sizeof(int)*columnA);     //행렬 사이즈를 입력받으면 동적할당으로 사이즈에 맞는 이차행렬A생성
	}

	printf("행렬A 값 입력하세요:\n");
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < columnA; j++)
		{
			scanf("%d", &A[i][j]);                 
		}
	}

	/*
	행렬을 입력받았을때 행과 열의 크기가 다를경우
	슈트라센 알고리즘의 구현을 쉽게 하기위하여
	행과 열의 사이즈를 같게한다, ex)3X4 -> 4X4
	*/
	if (rowA <= columnA)
		aMAX = columnA;
	else if (rowA >= columnA)
		aMAX = rowA;                  

	newA = (int**)malloc(sizeof(int*)*aMAX);
	for (int i = 0; i < aMAX; i++)
	{
		newA[i] = (int*)malloc(sizeof(int)*aMAX);
	}

	printf("\n");

	for (int i = 0; i < aMAX; i++)  //행과 열의 사이즈를 같게한후 입력받지 못한값이 생기는곳을 0으로 채운다.
	{
		for (int j = 0; j < aMAX; j++) 
		{
			if ((rowA == aMAX) && (j > (columnA - 1)))
				newA[i][j] = 0;
			else if ((columnA == aMAX) && (i > (rowA - 1)))      
				newA[i][j] = 0;
			else
				newA[i][j] = A[i][j];
		}
	}

	printf("A행렬)\n");
	for (int i = 0; i < aMAX; i++)
	{

		for (int j = 0; j < aMAX; j++)
		{
			printf("%2d ", newA[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	printf("행렬B 사이즈 입력하세요:");
	scanf("%d %d", &rowB, &columnB);

	B = (int**)malloc(sizeof(int*)*rowB);
	for (int i = 0; i < rowB; i++){
		B[i] = (int*)malloc(sizeof(int)*columnB);    //행렬 사이즈를 입력받으면 동적할당으로 사이즈에 맞는 이차행렬B생성
	}

	printf("행렬B 값 입력하세요:\n");
	for (int i = 0; i < rowB; i++)
	{
		for (int j = 0; j < columnB; j++)
		{
			scanf("%d", &B[i][j]);
		}
	}

	/*
	행렬을 입력받았을때 행과 열의 크기가 다를경우
	슈트라센 알고리즘의 구현을 쉽게 하기위하여
	행과 열의 사이즈를 같게한다, ex)3X4 -> 4X4
	*/
	if (rowB <= columnB)
		bMAX = columnB;
	else if (rowB >= columnB)
		bMAX = rowB;

	newB = (int**)malloc(sizeof(int*)*bMAX);
	for (int i = 0; i < bMAX; i++)
	{
		newB[i] = (int*)malloc(sizeof(int)*bMAX);
	}

	printf("\n");

	for (int i = 0; i < bMAX; i++)   //행과 열의 사이즈를 같게한후 입력받지 못한값이 생기는곳을 0으로 채운다.
	{
		for (int j = 0; j < bMAX; j++)
		{
			if ((rowB == bMAX) && (j > (columnB - 1)))
				newB[i][j] = 0;
			else if ((columnB == bMAX) && (i > (rowB - 1)))    
				newB[i][j] = 0;
			else
				newB[i][j] = B[i][j];
		}
		
	}

	printf("B행렬)\n");
	for (int i = 0; i < bMAX; i++)
	{

		for (int j = 0; j < bMAX; j++)
		{
			printf("%2d ", newB[i][j]);
		}
		printf("\n");
	}

	if (aMAX != bMAX)  //A행렬이 4X4, B행렬이 3X3이면 곱셈이 불가능하기 때문에 프로그램종료
	{
		printf("\n");
		printf("A,B의 크기가 다릅니다.\n");  
		printf("프로그램을 종료합니다.\n");
		return 0;
	}
	
	C = (int**)malloc(sizeof(int*)*aMAX);
	for (int i = 0; i < aMAX; i++) {
		C[i] = (int*)malloc(sizeof(int)*aMAX);
	}

	strMul(newA, newB, aMAX, C);

	printf("\n");
	printf("AXB행렬)\n");
	for (int i = 0; i < aMAX; i++)
	{

		for (int j = 0; j < aMAX; j++)
		{
			printf("%3d ", C[i][j]);
		}
		printf("\n");
	}
	free(A);
	free(B);
	free(C);
	free(newA);
	free(newB);
	return 0;
}

/*
슈트라센 행렬곱셈
a, b 행렬과 사이즈를 받아서 a*b를 c에 저장
*/
void strMul(int**a, int**b, int size, int **c)
{
	if (size == 1)  
	{
		c[0][0] = a[0][0] * b[0][0];
	}

	else
	{
		int i, j;
		int halfsize = size / 2; 
		int **a11, **a12, **a21, **a22, **b11, **b12, **b21, **b22, **m1, **m2, **m3, **m4, **m5, **m6, **m7;
		int **c11, **c12, **c21, **c22;
		int **temp1, **temp2;

		/*
		인자행렬의 행, 열의 반으로 사이즈를 맞춰서 행렬의 크기는 4분의1이된다.
		*/
		a11 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			a11[i] = malloc(sizeof(int)*halfsize);
		}

		a12 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			a12[i] = malloc(sizeof(int)*halfsize);
		}

		a21 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			a21[i] = malloc(sizeof(int)*halfsize);
		}

		a22 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			a22[i] = malloc(sizeof(int)*halfsize);
		}

		b11 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			b11[i] = malloc(sizeof(int)*halfsize);
		}

		b12 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			b12[i] = malloc(sizeof(int)*halfsize);
		}

		b21 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			b21[i] = malloc(sizeof(int)*halfsize);
		}

		b22 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			b22[i] = malloc(sizeof(int)*halfsize);
		}

		m1 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m1[i] = malloc(sizeof(int)*halfsize);
		}

		m2 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m2[i] = malloc(sizeof(int)*halfsize);
		}

		m3 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m3[i] = malloc(sizeof(int)*halfsize);
		}
		m4 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m4[i] = malloc(sizeof(int)*halfsize);
		}
		m5 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m5[i] = malloc(sizeof(int)*halfsize);
		}

		m6 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m6[i] = malloc(sizeof(int)*halfsize);
		}
		m7 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++){
			m7[i] = malloc(sizeof(int)*halfsize);
		}

		temp1 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++) {
			temp1[i] = malloc(sizeof(int)*halfsize);
		}

		temp2 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++) {
			temp2[i] = malloc(sizeof(int)*halfsize);
		}

		/*
		a=|a11 a12|
		  |a21 a22|

		b=|b11 b12|
		  |b21 b22| 로 설정
		*/
		for (i = 0; i < halfsize; i++)     
		{
			for (j = 0; j < halfsize; j++)
			{
				a11[i][j] = a[i][j];
				a12[i][j] = a[i][j + halfsize];
				a21[i][j] = a[i + halfsize][j];
				a22[i][j] = a[i + halfsize][j + halfsize];

				b11[i][j] = b[i][j];
				b12[i][j] = b[i][j + halfsize];
				b21[i][j] = b[i + halfsize][j];
				b22[i][j] = b[i + halfsize][j + halfsize];
			}
		}
		
		//슈트라센 알고리즘 공식 구현
		add(a11, a22, halfsize, temp1);
		add(b11, b22, halfsize, temp2);
		strMul(temp1, temp2, halfsize, m1); 

		add(a21, a22, halfsize, temp1);
		strMul(temp1, b11, halfsize, m2); 

		sub(b12, b22, halfsize, temp1);
		strMul(a11, temp1, halfsize, m3);

		sub(b21, b11, halfsize, temp1);
		strMul(a22, temp1, halfsize, m4);

		add(a11, a12, halfsize, temp1);
		strMul(temp1, b22, halfsize, m5); 

		sub(a21, a11, halfsize, temp1);
		add(b11, b12, halfsize, temp2);
		strMul(temp1, temp2, halfsize, m6);

		sub(a12, a22, halfsize, temp1);
		add(b21, b22, halfsize, temp2);
		strMul(temp1, temp2, halfsize, m7); 

		c11 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++) {
			c11[i] = malloc(sizeof(int)*halfsize);
		}
	    
		c12 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++) {
			c12[i] = malloc(sizeof(int)*halfsize);
		}

		c21 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++) {
			c21[i] = malloc(sizeof(int)*halfsize);
		}

		c22 = malloc(sizeof(int *)*halfsize);
		for (i = 0; i < halfsize; i++) {
			c22[i] = malloc(sizeof(int)*halfsize);
		}
		
		add(m1, m4, halfsize, temp1);
		sub(m7, m5, halfsize, temp2);
		add(temp1, temp2, halfsize, c11);

		add(m3, m5, halfsize, c12);

		add(m2, m4, halfsize, c21);

		add(m1, m3, halfsize, temp1);
		sub(m6, m2, halfsize, temp2);
		add(temp1, temp2, halfsize, c22);

		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				if ((i < halfsize) && (j < halfsize))
					c[i][j] = c11[i][j];
				else if ((i < halfsize) && (j >= halfsize))
					c[i][j] = c12[i][j-halfsize];
				else if ((i >= halfsize) && (j < halfsize))
					c[i][j] = c21[i-halfsize][j];
				else if ((i >= halfsize) && (j >= halfsize))
					c[i][j] = c22[i-halfsize][j-halfsize];
			}

		}

		free(a11);
		free(a12);
		free(a21);
		free(a22);
		free(b11);
		free(b12);
		free(b21);
		free(b22);
		free(m1);
		free(m2);
		free(m3);
		free(m4);
		free(m5);
		free(m6);
		free(m7);
		free(c11);
		free(c12);
		free(c21);
		free(c22);
		free(temp1);
		free(temp2);
	}
}

/*
슈트라센 알고리즘에 사용하는 행렬덧셈구현
a+b 를 c에 저장
*/
void add(int **a, int**b, int size, int **c)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

/*
슈트라센 알고리즘에 사용하는 행렬뺄셈구현
a-b 를 c에 저장
*/
void sub(int **a, int**b, int size, int **c)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			c[i][j] = a[i][j] - b[i][j];
		}
	}
}