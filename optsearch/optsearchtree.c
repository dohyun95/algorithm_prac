#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void optsearchtree(int n, float *p, float minavg, int **R); //최적 이분검색트리 구하는 함수
float P(float *p, int i, int j); //p[i]부터 p[j]까지의 합을 구하는 함수

int main(void)
{
	int elementNum; //원소의 개수
	float a, b;  
	printf("원소 개수: ");
	scanf("%d", &elementNum);

	float *p;
	p = (float*)malloc(sizeof(int) * (elementNum+1)); //확률배열 p의 크기 지정
													  //p는 p1~pi 이므로 크기는 p[i+1]로 한다.
	int **R;
	R = (int**)malloc(sizeof(int*) * elementNum+2);
	for (int i = 0; i < elementNum+2; i++) {
		R[i] = (int*)malloc(sizeof(int) * elementNum+1); //최적트리의 뿌리에서 원소의 인덱스배열 R크기 지정
	}													 //R[i+1][i] 까지 있으므로 행은 elementNum+2, 열은 +1로 한다.


	printf("\n");
	printf("확률입력(분수형 a/b) \n"); //입력을 받을 때 분수형으로 받기 위함이다.
	for(int i = 0; i < elementNum; i++)
	{
		printf("p[%d]: ", i+1);
		scanf(" %f/%f", &a, &b);
		p[i + 1] = a / b; //분자, 분모를 각각 입력받은후 p배열에 a/b값을 입력해준다.
	}

	printf("\n");
	for (int i = 0; i < elementNum; i++)
	{
		printf("p[%d]:%3.2f  ", i + 1, p[i + 1]); //분수형으로 입력받은 p배열원소를 계산된 소수형으로 재확인
	}
	printf("\n");

	optsearchtree(elementNum, p, 1, R); //최적 이분검색트리 실행
	
}

//원소크기, 확률배열, 1부터 마지막원소까지의 평균검색시간, 뿌리원소배열 R을 인자로 받음
//diagonal을 이용하여 2개원소, 3개원소, 4개원소.... 적은순부터 검색시간을 구한다.
void optsearchtree(int elementNum, float *p, float minavg, int **R)
{
	int i, j, k, diagonal;
	float **A;
	A = (float**)malloc(sizeof(int*) * elementNum+2); 
	for (int i = 0; i < elementNum+2; i++) {
		A[i] = (float*)malloc(sizeof(int) * elementNum+1); //최적트리 평균시간 배열 크기
	}
	
	for (i = 1; i <= elementNum; i++)
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}
	A[elementNum + 1][elementNum] = 0;
	R[elementNum + 1][elementNum] = 0;

	for(i=1; i<=elementNum+1; i++)
		for (j = i + 1; j <= elementNum; j++)
		{
			A[i][j] = 1000; //k값에 따라 다른 값중 최소가 A배열 원소가 되므로 큰수로 초기화 해놓는다.
		}

	for(diagonal=1; diagonal<=elementNum-1; diagonal++)
		for (i = 1; i <= elementNum - diagonal; i++)
		{
			j = i + diagonal;
			for (k = i; k <= j; k++) //k를 하나씩 대입하며 계산하면서 작은값을 골라낸다.
			{
				if (A[i][j] > A[i][k - 1] + A[k + 1][j] + P(p, i, j)) //기존 A원소보다 새로 계산한 원소가 더 크면
				{													  //새로 계산한 원소가 A의 원소가 된다
					A[i][j] = A[i][k - 1] + A[k + 1][j] + P(p, i, j); //뿌리인 k에서 각 원소에 대해서 한번더 비교하므로 
					R[i][j] = k;								  //해당하는 범위의 각 원소의 확률을 한번씩 다 더해야한다.
				}
			}
		}
	
	printf("\n");
	printf("A"); //다음 줄부터 A배열 보여주는 식

	for (int i = 0; i < elementNum + 1; i++) 
	{
		printf("%6d", i);
	}
	printf("\n");
	printf(" ");
	for (int i = 0; i < elementNum + 1; i++)
	{
		printf("------");
		
	}
	printf("\n");
	for (int i = 1; i < elementNum + 2; i++)
	{
		printf("%d| ", i);
		for (int j = 0; j < elementNum + 1; j++)
		{
			if (i > j + 1)
				printf("      ");
			else
				printf("%3.2f  ", A[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("R"); //R배열 보여주는 식
	for (int i = 0; i < elementNum + 1; i++)
	{
		printf("%5d", i);
	}
	printf("\n");
	printf(" ");
	for (int i = 0; i < elementNum + 1; i++)
	{
		printf("-----");

	}

	printf("\n");
	for (int i = 1; i < elementNum + 2; i++)
	{
		printf("%d| ", i);
		for (int j = 0; j < elementNum + 1; j++)
		{
			if (i > j + 1)
				printf("     ");
			else
				printf("%3d  ", R[i][j]);
		}
		printf("\n");
	}
	minavg = A[elementNum + 1][elementNum];
}

//배열 p와 합을 구하려는 범위 i, j를 입력
//p[i]부터 p[j]까지의 합을 구하는 함수
float P(float *p,int i, int j)
{
	float result=0;
	for (i; i <= j; i++)
		result = result + p[i];
	return result;
}