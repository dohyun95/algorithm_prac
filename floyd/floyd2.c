#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void floyd(int size, int **W, int **D, int **P);
void path(int **P,int q, int r);

int main()
{
	int size;
	int q, r;
	printf("size 입력하세요:");
	scanf("%d", &size);

	int **W;
	W = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		W[i] = (int*)malloc(sizeof(int) * size);
	}

	int **D;
	D = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		D[i] = (int*)malloc(sizeof(int) * size);
	}
	int **P;
	P = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++) {
		P[i] = (int*)malloc(sizeof(int) * size);
	}

	printf("\n");
	printf("(direct하지않다면 100입력)\n");
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				W[i][j] = 0;
			else
			{
				printf("%d->%d의 direct거리: ", i + 1, j + 1);
				scanf("%d", &W[i][j]);
			}
		}

	floyd(size, W, D, P);

	printf("\n");
	printf("W)\n");
	printf("  ");
	for (int i = 0; i < size; i++)
		printf("%4d", i + 1);
	printf("\n");
	printf("  ");
	for (int i = 0; i < size; i++)
		printf("----");
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("%d|", i + 1);
		for (int j = 0; j < size; j++)
		{
			if (W[i][j] == 100)
				printf("  ∞");
			else
				printf("%4d", W[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("D)\n");
	printf("  ");
	for (int i = 0; i < size; i++)
		printf("%4d", i + 1);
	printf("\n");
	printf("  ");
	for (int i = 0; i < size; i++)
		printf("----");
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("%d|", i + 1);
		for (int j = 0; j < size; j++)
		{
				printf("%4d", D[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("P)\n");
	printf("  ");
	for (int i = 0; i < size; i++)
		printf("%4d", i + 1);
	printf("\n");
	printf("  ");
	for (int i = 0; i < size; i++)
		printf("----");
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("%d|", i + 1);
		for (int j = 0; j < size; j++)
		{
			printf("%4d", P[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	int m = 1;
	while (m != 0)
	{
		printf("\n");
		printf("최단경로 구하려는 두 마디 입력하세요(0,0입력시 종료): ");
		scanf("%d %d", &q, &r);
		if (q == 0 || r == 0)
		{
			m = 0;
			printf("종료합니다");
		}
		else
		{
			printf("%d에서 %d까지 최단경로: ", q, r);
			printf("v%d->", q);
			path(P, q, r);
			printf("v%d\n", r);
		}
	}
	printf("\n");

	return 0;
}

void floyd(int size, int **W, int **D, int **P)
{
	int i, j, k;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			P[i][j] = 0;

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			D[i][j] = W[i][j];

	for (k = 0; k < size; k++)
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				if (D[i][k] + D[k][j] < D[i][j])
				{
					P[i][j] = k+1;
					D[i][j] = D[i][k] + D[k][j];
				}
			}

}

void path(int **P, int q, int r)
{
	if (P[q-1][r-1] != 0)
	{
		path(P, q, P[q-1][r-1]);
		printf("v%d->", P[q-1][r-1]);
		path(P, P[q-1][r-1], r);
	}

}