#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int minmult(int elementNum, int *d, int **p); //�ּ� ���� Ƚ��, ���� ��� ���� ���ϴ� �Լ�
void order(int **P, int i, int j); //���� ��� ���ϴ� �Լ�

int main(void)
{
	int elementNum; //��� ����
	int *d; //��Ǵ� ���� ���� �迭, d[i-1]�� i�� ��, d[i]�� i�� ��
	int **P; //���� ��� ���� �迭, P[i][j]�� i���� j���� ���Ҷ� ����Ƚ���� �ּҰ� �Ǵ� �߰���� ����

	printf("��� ���� �Է�: ");
	scanf("%d", &elementNum);

	d = (int*)malloc(sizeof(int) * elementNum); //d�迭 ������ �Է�

	P = (int**)malloc(sizeof(int*) * elementNum); //P�迭 ������ �Է�
	for (int i = 0; i < elementNum; i++) {
		P[i] = (int*)malloc(sizeof(int) * elementNum);
	}

	printf("\n");
	printf("(��� ũ�� �Է�)\n");
	for (int i=0; i < elementNum; i++) 
	{
		if (i == 0)
		{
			printf("%d��° ��,�� �Է�: ", i + 1);
			scanf("%d %d", &d[i], &d[i + 1]);
		}
		else 
		{
			printf("%d��° �� �Է�:", i+1);
			scanf("%d", &d[i+1]);
		}
	}

	printf("\n");
	printf("(����� ũ�� ���)\n"); //Ȯ���� �Է¹��� ������ ���
	for (int i=0; i < elementNum; i++)
	{
		printf("%d��° ��� = %d * %d\n", i + 1, d[i], d[i + 1]);
	}

	printf("\n");
	printf("M[1][%d] = %d\n", elementNum, minmult(elementNum, d, P)); //�ּҰ���Ƚ�����, ������α������ ��� �� 
	printf("\n");													  //M[1][elementNum] �� return�ؼ� ��� 												
	printf("(���� ���� ����)\n");
	order(P, 0, elementNum - 1);  //������� ���
	
}

int minmult(int elementNum, int *d, int **p)
{
	int diagonal, i, j, k, temp, cost;
	int **M; //�ּ� ���� Ƚ�� �����ϴ� �迭
	M = (int**)malloc(sizeof(int*) * elementNum); //M�迭 ������ �Է�
	for (int i = 0; i < elementNum; i++) 
		M[i] = (int*)malloc(sizeof(int) * elementNum);

	for (i = 0; i < elementNum; i++) 
		M[i][i] = 0;

	for (i = 0; i < elementNum; i++) //��Ŀ��� �ʿ���� ���� 0���� �ʱ�ȭ
		for (j = 0; j < i; j++)
			M[i][j] = 0;

	for (diagonal = 1; diagonal < elementNum; diagonal++) {  //M,P �迭 ���ϴ� ����
		for (i = 0; i < elementNum - diagonal; i++) {
			j = i + diagonal; //diagonal ���� ���� ���ϴ� ������ �޶�����
			M[i][j] = 1000; //�������� M�迭 ���� ���� �Ǳ� ������ ū���� �ʱ�ȭ�ؼ� �񱳽� �ٲ� �� �ְ��Ѵ� 
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

	//M��� ���
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
	//P��� ���
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
