#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define index int

void dijkstra(int n, int **W, int *F); //���ͽ�Ʈ�� �˰���
void pathprint(int *F, int size);  //F�� ��θ� �����ִ� �Լ�

int main(void)
{
	int size;
	int *F; //set of edges
	int **W; //�� node ������ edge weight ex)W[1][3] = V1->V3 edge�� weight
	printf("node ����: ");
	scanf("%d", &size);
	
	//�����迭 W�� �����迭
	W = malloc(sizeof(int*) * (size+1));
	for (int i = 0; i <= size; i++) {
		W[i] = malloc(sizeof(int) * (size+1));
	}

	F = malloc(sizeof(int) * (size + 1));
	for (int i = 0; i <= size; i++)
		F[i] = 0;
	
	//edge���� �Է¹޴´�. ��������� ������� 1000�Է�
	printf("edge���� �Է�) \n");
	for(int i=1; i<=size; i++)
		for(int j=1; j<=size; j++)
			if(i != j)
			{
				printf("V%d->V%d: ", i, j);
				scanf("%d", &W[i][j]);
			}
		
	dijkstra(size, W, F);
	printf("\n");
	pathprint(F, size);
}

//���ͽ�Ʈ�� �˰��� �Լ�
void dijkstra(int size, int **W, int *F)
{
	index i, vnear;
	index *touch; //��ο����� �ٷ��� node   ex)V1->V3->V5, touch[5] = 3
	int *length, cnt=size-1;
	
	touch = malloc(sizeof(int)*(size + 1));
	length = malloc(sizeof(int)*(size + 1));

	//v1���� ����ϴ� �ִܰ�� ������ ����� �� ��� ���̸� �ʱ�ȭ 
	for (i = 2; i <= size; i++) 
	{
		touch[i] = 1;
		length[i] = W[1][i];
	}

	while (cnt)
	{
		int min = 1000;
		//�ִܰ�θ� �������� �˻�
		//-1�̰ų� ���������������(1000)�� edge�� ������� �ʴ´�
		for (i = 2; i <= size; i++)
			if (0 <= length[i] && length[i] < min)
			{
				min = length[i];
				vnear = i;
			}
		//(set of edge F) v1-(F)->v5�� F[5]=1�� ǥ���Ͽ���.
		F[vnear] = touch[vnear];
		for (i = 2; i <= size; i++)
		{
			//�ִܰŸ� length[vnear]���� �̾�����ΰ� ������κ��� ª���� ����
			if (length[vnear] + W[vnear][i] < length[i]) 
			{
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}
			length[vnear] = -1;
		}
		cnt--;
	}
}

void pathprint(int *F, int size)
{
	//F���
	printf("F ���)\n");
	for (int i = 2; i <= size; i++)
	{
		printf("V%d->V%d", F[i], i);
		printf("\n");
	}
	printf("\n");
	//V1���� �� node�� path ��� 
	for (int i = size; i>=2; i--)
	{
		int value = 1;
		int temp = i;
		printf("V%d path: V%d", i, i);
		while (value)
		{
			printf("<-V%d", F[temp]);
			temp = F[temp];
			if (F[temp] == 0)
				value = 0;

		}
		printf("\n");
	}
}