#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#define index int

void sum_of_subsets(index i, int weight, int total, int *w, int *include, int W); //sum_of_subset �˰��� �Լ�
bool promising(index i, int weight, int total, int *w, int W); //�������� ���� �˾ƺ��� �Լ�

int main(void)
{
	int size, W, total=0;
	int *w, *include;

	printf("���� ����: ");
	scanf("%d", &size); //������ ��

	w = (int*)malloc(sizeof(int)*(size+1)); //���԰� ����� �迭 ũ�� �Ҵ�
	include = (int*)malloc(sizeof(int)*(size + 1)); //�ش� ���԰� ���Ե����� ���� ����� �迭 ũ�� �Ҵ�

	printf("���� �Է�)\n");
	for (int i = 0; i < size; i++)  //���Ը� �Է¹ް� w�迭�� ����, �׸��� �� ������ ���� total�� ����
	{
		printf("w%d ����: ", i+1);
		scanf("%d", &w[i + 1]);
		total += w[i + 1];
	}
	printf("���Ϸ��� ����: ");
	scanf("%d", &W);  //���� ���� W

	printf("\n");
	sum_of_subsets(0, 0, total, w, include, W);
	free(w);
	free(include);
}

void sum_of_subsets(index i, int weight, int total, int *w, int *include, int W)
{
	if (promising(i, weight, total, w, W)) //�����ϸ� ����
		if (weight == W) //�����ϰ� ���� ���ϴ� ���԰� �������ٸ� ���
		{
			printf("include1~%d: ", i);
			for (int j = 1; j <= i; j++) //include�� �� ���
			{	
				printf("%d ", include[j]);
			}
			printf("\n");
			printf("���� %d�� �Ǵ� ������ ����: ", W);
			for (int j = 1; j <= i; j++) //include[i]=1�̸� i��° ���Դ� �����ϹǷ� ���
			{
				if (include[j] == 1)
					printf("w%d(%d) ", j,w[j]);
			}
		}
		else //���������� ���� ���ϴ� ���԰� �ƴ϶�� ���� ���Ը� ����, �������� �Լ��� �ٽ� ����
		{
			include[i + 1] = 1; //���� ���Ը� ���Խ�Ų��
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1], w, include, W);
			include[i + 1] = 0; //���� ���Ը� ���Խ�Ű�� �ʴ´�
			sum_of_subsets(i + 1, weight, total - w[i + 1], w, include, W);

		}
}

bool promising(index i, int weight, int total, int *w, int W)
{
	//1.���ݱ����� ���Կ� ���� ���԰� ���ϴ� ���Ժ��� ũ�ų�����.
	//2.���ݱ����� ���԰� ���ϴ� �����̰ų� �������Ա����� ���� ���ϴ� ���� �����̴�.
	//1,2 �� ��� �����Ǹ� �����ϴ�.
	return (weight + total >= W) && ((weight == W) || (weight + w[i + 1] <= W));
}