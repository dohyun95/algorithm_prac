#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int n;
typedef int index;
typedef index set_pointer;

//nodetype의 구조체를 정의
typedef struct nodetype
{
	index parent;
	int depth;
}universe;
universe *U;

//edge의 구조체를 정의
//구현의 편의를 위해 알고리즘에서 추가적으로 구현
//edge에 달린 두 vertex값과 weight 값을 갖는다.
typedef struct edge {
	index vertex1;
	index vertex2;
	int weight;
}edge;
edge *E;


//i의 부모를 i자신으로 초기화
void makeset(index i)
{
	U[i].parent = i;
	U[i].depth = 0;
}

//부모가 자신이면 자신을, 자신이 아니면 부모값을 return함 
set_pointer find(index i)
{
	index j;
	j = i;
	while (U[j].parent != j)
		j = U[j].parent;
	return j;
}

//depth의 값비교를 통해 누가 부모가될지 결정
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

//부모값을 비교
bool equal(set_pointer p, set_pointer q)
{
	if (p == q)
		return true;
	else
		return false;
}

//부모값을 초기화하기 위함
void initial(int n)
{
	U = (universe *)malloc(sizeof(universe) * n);
	index i;
	for (i = 1; i <= n; i++)
		makeset(i);
}

//sort정렬시 편의를 위해 복사하는 함수를 알고리즘에 추가적으로 구현함
void edge_copy(edge *Destination, const edge *Source)
{
	Destination->vertex1 = Source->vertex1;
	Destination->vertex2 = Source->vertex2;
	Destination->weight = Source->weight;
}

//U,V 배열을 S로 통합하는 함수
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

//edge들을 오름차순으로 정렬하기위한 함수, 복잡도가 nlogn인 sort를 사용하였다.
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

//크루스칼 알고리즘
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
		if (e.weight == 9999) //직접연결되지 않은경우 weight를 9999로 뒀기때문에 skip한다.
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
	printf("node 갯수: ");
	scanf("%d", &n);
	temp = n - 1;
	for (int i = 0; i < n; i++) //edge의 갯수를 n+(n-1)+(n-2)....로 계산한다
	{
		sum = sum + temp;
		temp--;
	}
	E = (edge*)malloc(sizeof(edge)*sum);
	F = (edge*)malloc(sizeof(edge)*sum);

	for (int i = 0; i < n; i++) //i,j가 같은경우를 빼고 edge 값을 받는다
	{							
		for (int j = i; j < n; j++) //i-j 와 j-i는 같으므로 한번만 입력받는다
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
	printf("집합F 출력\n");
	for (int i = 0; i < n - 1; i++)
		if (F[i].weight != 9999)
			printf("v%d - v%d, weight= %d\n", F[i].vertex1, F[i].vertex2, F[i].weight);

}
