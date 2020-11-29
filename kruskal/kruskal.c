#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int n;
typedef int index;
typedef index set_pointer;

//nodetype�� ����ü�� ����
typedef struct nodetype
{
	index parent;
	int depth;
}universe;
universe *U;

//edge�� ����ü�� ����
//������ ���Ǹ� ���� �˰��򿡼� �߰������� ����
//edge�� �޸� �� vertex���� weight ���� ���´�.
typedef struct edge {
	index vertex1;
	index vertex2;
	int weight;
}edge;
edge *E;


//i�� �θ� i�ڽ����� �ʱ�ȭ
void makeset(index i)
{
	U[i].parent = i;
	U[i].depth = 0;
}

//�θ� �ڽ��̸� �ڽ���, �ڽ��� �ƴϸ� �θ��� return�� 
set_pointer find(index i)
{
	index j;
	j = i;
	while (U[j].parent != j)
		j = U[j].parent;
	return j;
}

//depth�� ���񱳸� ���� ���� �θ𰡵��� ����
void merge(set_pointer p, set_pointer q)
{
	if (U[p].depth == U[q].depth)
	{
		U[p].depth = U[p].depth + 1;
		U[q].parent = p;
	}
	else if (U[p].depth < U[q].depth)
		U[p].parent = q;
	else
		U[q].parent = p;
}

//�θ��� ��
bool equal(set_pointer p, set_pointer q)
{
	if (p == q)
		return true;
	else
		return false;
}

//�θ��� �ʱ�ȭ�ϱ� ����
void initial(int n)
{
	U = (universe *)malloc(sizeof(universe) * n);
	index i;
	for (i = 1; i <= n; i++)
		makeset(i);
}

//sort���Ľ� ���Ǹ� ���� �����ϴ� �Լ��� �˰��� �߰������� ������
void edge_copy(edge *Destination, const edge *Source)
{
	Destination->vertex1 = Source->vertex1;
	Destination->vertex2 = Source->vertex2;
	Destination->weight = Source->weight;
}

//U,V �迭�� S�� �����ϴ� �Լ�
void merge2(int h, int m, const edge *U, const edge *V, edge *S)
{
	int i, j, k;
	i = 1; j = 1; k = 1;
	while (i <= h && j <= m)
	{
		if (U[i].weight < V[j].weight)
		{
			edge_copy(S + k, U + i);
			i++;
		}
		else
		{
			edge_copy(S + k, V + j);
			j++;
		}
		k++;
	}
	if (i > h)
		for (; j <= m; j++)
		{
			edge_copy(S + k, V + j);
			k++;
		}
	else
		for (; i <= h; i++)
		{
			edge_copy(S + k, U + i);
			k++;
		}
}

//edge���� ������������ �����ϱ����� �Լ�, ���⵵�� nlogn�� sort�� ����Ͽ���.
void mergesort(int n, edge *S)
{
	if (n > 1)
	{
		const int h = n / 2, m = n - h;
		edge *U = (edge*)malloc(sizeof(edge)*h + 1);
		edge *V = (edge*)malloc(sizeof(edge)*m + 1);

		for (int i = 1; i <= h; i++)
			edge_copy(U + i, S + i);
		for (int j = 1; j <= m; j++)
			edge_copy(V + j, S + (j + h));
		mergesort(h, U);
		mergesort(m, V);
		merge2(h, m, U, V, S);
	}
}

//ũ�罺Į �˰���
void kruskal(int n, int m, edge *E, edge *F)
{
	index i, j, fi, ei;
	set_pointer p, q;
	edge e;
	i = j = ei = 1;
	fi = 0;
	mergesort(m, E);

	initial(n);

	while (fi < n - 1) 
	{
		e = E[ei++];
		if (e.weight == 9999) //����������� ������� weight�� 9999�� �ױ⶧���� skip�Ѵ�.
			continue;
		i = e.vertex1;
		j = e.vertex2;
		p = find(i);
		q = find(j);
		if (!equal(p, q)) 
		{
			merge(p, q);
			F[fi++] = e;
		}
	}
}

int main(void)
{
	int temp = 0, sum = 0;
	int k = 1;
	edge *F;
	printf("node ����: ");
	scanf("%d", &n);
	temp = n - 1;
	for (int i = 0; i < n; i++) //edge�� ������ n+(n-1)+(n-2)....�� ����Ѵ�
	{
		sum = sum + temp;
		temp--;
	}
	E = (edge*)malloc(sizeof(edge)*sum);
	F = (edge*)malloc(sizeof(edge)*sum);

	for (int i = 0; i < n; i++) //i,j�� ������츦 ���� edge ���� �޴´�
	{							
		for (int j = i; j < n; j++) //i-j �� j-i�� �����Ƿ� �ѹ��� �Է¹޴´�
		{
			if (i != j)
			{
				E[k].vertex1 = i + 1;
				E[k].vertex2 = j + 1;

				printf("V%d-V%d: ", i + 1, j + 1);
				scanf("%d", &E[k].weight);
				k++;
			}
		}
	}
	

	kruskal(n, sum, E, F);

	printf("\n");
	printf("����F ���\n");
	for (int i = 0; i < n - 1; i++)
		if (F[i].weight != 9999)
			printf("v%d - v%d, weight= %d\n", F[i].vertex1, F[i].vertex2, F[i].weight);

}
