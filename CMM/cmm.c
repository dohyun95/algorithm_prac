#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int minmult(int elementNum, int *d, int **p); //최소 곱셈 횟수, 최적 경로 기점 구하는 함수
void order(int **P, int i, int j); //최정 경로 구하는 함수

int main(void)
{
	int elementNum; //행렬 개수
	int *d; //행또는 열의 개수 배열, d[i-1]은 i의 행, d[i]는 i의 열
	int **P; //최적 경로 기점 배열, P[i][j]는 i에서 j까지 곱할때 곱셈횟수가 최소가 되는 중간경로 기점

	printf("행렬 개수 입력: ");
	scanf("%d", &elementNum);

	d = (int*)malloc(sizeof(int) * elementNum); //d배열 사이즈 입력

	P = (int**)malloc(sizeof(int*) * elementNum); //P배열 사이즈 입력
	for (int i = 0; i < elementNum; i++) {
		P[i] = (int*)malloc(sizeof(int) * elementNum);
	}

	printf("\n");
	printf("(행렬 크기 입력)\n");
	for (int i=0; i < elementNum; i++) 
	{
		if (i == 0)
		{
			printf("%d번째 행,열 입력: ", i + 1);
			scanf("%d %d", &d[i], &d[i + 1]);
		}
		else 
		{
			printf("%d번째 열 입력:", i+1);
			scanf("%d", &d[i+1]);
		}
	}

	printf("\n");
	printf("(행렬의 크기 결과)\n"); //확인차 입력받은 사이즈 출력
	for (int i=0; i < elementNum; i++)
	{
		printf("%d번째 행렬 = %d * %d\n", i + 1, d[i], d[i + 1]);
	}

	printf("\n");
	printf("M[1][%d] = %d\n", elementNum, minmult(elementNum, d, P)); //최소곱셈횟수행렬, 최적경로기점행렬 출력 및 
	printf("\n");													  //M[1][elementNum] 값 return해서 출력 												
	printf("(최적 분해 순서)\n");
	order(P, 0, elementNum - 1);  //최적경로 출력
	
}

int minmult(int elementNum, int *d, int **p)
{
	int diagonal, i, j, k, temp, cost;
	int **M; //최소 곱셈 횟수 저장하는 배열
	M = (int**)malloc(sizeof(int*) * elementNum); //M배열 사이즈 입력
	for (int i = 0; i < elementNum; i++) 
		M[i] = (int*)malloc(sizeof(int) * elementNum);

	for (i = 0; i < elementNum; i++) 
		M[i][i] = 0;

	for (i = 0; i < elementNum; i++) //행렬에서 필요없는 공간 0으로 초기화
		for (j = 0; j < i; j++)
			M[i][j] = 0;

	for (diagonal = 1; diagonal < elementNum; diagonal++) {  //M,P 배열 구하는 과정
		for (i = 0; i < elementNum - diagonal; i++) {
			j = i + diagonal; //diagonal 값에 따라서 구하는 범위가 달라진다
			M[i][j] = 1000; //작은수가 M배열 원소 값이 되기 때문에 큰수로 초기화해서 비교시 바뀔 수 있게한다 
			for (k = i; k < j; k++) {
				temp = d[i] * d[k + 1] * d[j + 1];
				cost = M[i][k] + M[k + 1][j] + temp;
				if (cost < M[i][j]) {
					M[i][j] = cost;
					p[i][j] = k;
				}
			}
		}
	}

	//M행렬 출력
	printf("M)");
	for (int i = 0; i < elementNum; i++)
	{
		printf("%5d", i + 1);
	}
	printf("\n");
	printf("  ");
	for (int i = 0; i < elementNum; i++)
	{
		printf("-----");
	}
	printf("\n");
	
	for (int i = 0; i < elementNum; i++)
	{
		printf("%d|", i+1);
		for (int j = 0; j < elementNum; j++)
		{
			if (j<i)
				printf("     ");
			else
				printf("%5d", M[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	//P행렬 출력
	printf("P)");
	for (int i = 0; i < elementNum; i++)
	{
		printf("%5d", i + 1);
	}
	printf("\n");
	printf("  ");
	for (int i = 0; i < elementNum; i++)
	{
		printf("-----");
	}
	printf("\n");

	for (int i = 0; i < elementNum; i++)
	{
		printf("%d|", i + 1);
		for (int j = 0; j < elementNum; j++)
		{
			if (j <= i)
				printf("     ");
			else
				printf("%5d", p[i][j]+1);
		}
		printf("\n");
	}
	
	printf("\n");
	return M[0][elementNum-1];
}
void order(int **P, int i, int j)
{
	if (i == j)
		printf("A%d", i+1);
	else
	{
		int k = P[i][j];
		printf("(");              
		order(P, i, k);
		order(P, k+1, j);
		printf(")");

	}

}
