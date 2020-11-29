#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

void optsearchtree(int n, float *p, float minavg, int **R); //���� �̺а˻�Ʈ�� ���ϴ� �Լ�
float P(float *p, int i, int j); //p[i]���� p[j]������ ���� ���ϴ� �Լ�

int main(void)
{
	int elementNum; //������ ����
	float a, b;  
	printf("���� ����: ");
	scanf("%d", &elementNum);

	float *p;
	p = (float*)malloc(sizeof(int) * (elementNum+1)); //Ȯ���迭 p�� ũ�� ����
													  //p�� p1~pi �̹Ƿ� ũ��� p[i+1]�� �Ѵ�.
	int **R;
	R = (int**)malloc(sizeof(int*) * elementNum+2);
	for (int i = 0; i < elementNum+2; i++) {
		R[i] = (int*)malloc(sizeof(int) * elementNum+1); //����Ʈ���� �Ѹ����� ������ �ε����迭 Rũ�� ����
	}													 //R[i+1][i] ���� �����Ƿ� ���� elementNum+2, ���� +1�� �Ѵ�.


	printf("\n");
	printf("Ȯ���Է�(�м��� a/b) \n"); //�Է��� ���� �� �м������� �ޱ� �����̴�.
	for(int i = 0; i < elementNum; i++)
	{
		printf("p[%d]: ", i+1);
		scanf(" %f/%f", &a, &b);
		p[i + 1] = a / b; //����, �и� ���� �Է¹����� p�迭�� a/b���� �Է����ش�.
	}

	printf("\n");
	for (int i = 0; i < elementNum; i++)
	{
		printf("p[%d]:%3.2f  ", i + 1, p[i + 1]); //�м������� �Է¹��� p�迭���Ҹ� ���� �Ҽ������� ��Ȯ��
	}
	printf("\n");

	optsearchtree(elementNum, p, 1, R); //���� �̺а˻�Ʈ�� ����
	
}

//����ũ��, Ȯ���迭, 1���� ���������ұ����� ��հ˻��ð�, �Ѹ����ҹ迭 R�� ���ڷ� ����
//diagonal�� �̿��Ͽ� 2������, 3������, 4������.... ���������� �˻��ð��� ���Ѵ�.
void optsearchtree(int elementNum, float *p, float minavg, int **R)
{
	int i, j, k, diagonal;
	float **A;
	A = (float**)malloc(sizeof(int*) * elementNum+2); 
	for (int i = 0; i < elementNum+2; i++) {
		A[i] = (float*)malloc(sizeof(int) * elementNum+1); //����Ʈ�� ��սð� �迭 ũ��
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
			A[i][j] = 1000; //k���� ���� �ٸ� ���� �ּҰ� A�迭 ���Ұ� �ǹǷ� ū���� �ʱ�ȭ �س��´�.
		}

	for(diagonal=1; diagonal<=elementNum-1; diagonal++)
		for (i = 1; i <= elementNum - diagonal; i++)
		{
			j = i + diagonal;
			for (k = i; k <= j; k++) //k�� �ϳ��� �����ϸ� ����ϸ鼭 �������� ��󳽴�.
			{
				if (A[i][j] > A[i][k - 1] + A[k + 1][j] + P(p, i, j)) //���� A���Һ��� ���� ����� ���Ұ� �� ũ��
				{													  //���� ����� ���Ұ� A�� ���Ұ� �ȴ�
					A[i][j] = A[i][k - 1] + A[k + 1][j] + P(p, i, j); //�Ѹ��� k���� �� ���ҿ� ���ؼ� �ѹ��� ���ϹǷ� 
					R[i][j] = k;								  //�ش��ϴ� ������ �� ������ Ȯ���� �ѹ��� �� ���ؾ��Ѵ�.
				}
			}
		}
	
	printf("\n");
	printf("A"); //���� �ٺ��� A�迭 �����ִ� ��

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
	printf("R"); //R�迭 �����ִ� ��
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

//�迭 p�� ���� ���Ϸ��� ���� i, j�� �Է�
//p[i]���� p[j]������ ���� ���ϴ� �Լ�
float P(float *p,int i, int j)
{
	float result=0;
	for (i; i <= j; i++)
		result = result + p[i];
	return result;
}