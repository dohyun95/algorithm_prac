#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define index int

void dijkstra(int n, int **W, int *F); //다익스트라 알고리즘
void pathprint(int *F, int size);  //F의 경로를 보여주는 함수

int main(void)
{
	int size;
	int *F; //set of edges
	int **W; //두 node 사이의 edge weight ex)W[1][3] = V1->V3 edge의 weight
	printf("node 개수: ");
	scanf("%d", &size);
	
	//이차배열 W의 동적배열
	W = malloc(sizeof(int*) * (size+1));
	for (int i = 0; i <= size; i++) {
		W[i] = malloc(sizeof(int) * (size+1));
	}

	F = malloc(sizeof(int) * (size + 1));
	for (int i = 0; i <= size; i++)
		F[i] = 0;
	
	//edge길이 입력받는다. 연결돼있지 않을경우 1000입력
	printf("edge길이 입력) \n");
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

//다익스트라 알고리즘 함수
void dijkstra(int size, int **W, int *F)
{
	index i, vnear;
	index *touch; //경로에서의 바로전 node   ex)V1->V3->V5, touch[5] = 3
	int *length, cnt=size-1;
	
	touch = malloc(sizeof(int)*(size + 1));
	length = malloc(sizeof(int)*(size + 1));

	//v1에서 출발하는 최단경로 마지막 마디와 그 경로 길이를 초기화 
	for (i = 2; i <= size; i++) 
	{
		touch[i] = 1;
		length[i] = W[1][i];
	}

	while (cnt)
	{
		int min = 1000;
		//최단경로를 가지는지 검사
		//-1이거나 직접연결되지않은(1000)인 edge는 고려하지 않는다
		for (i = 2; i <= size; i++)
			if (0 <= length[i] && length[i] < min)
			{
				min = length[i];
				vnear = i;
			}
		//(set of edge F) v1-(F)->v5를 F[5]=1로 표현하였다.
		F[vnear] = touch[vnear];
		for (i = 2; i <= size; i++)
		{
			//최단거리 length[vnear]에서 이어진경로가 기존경로보다 짧으면 갱신
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
	//F출력
	printf("F 출력)\n");
	for (int i = 2; i <= size; i++)
	{
		printf("V%d->V%d", F[i], i);
		printf("\n");
	}
	printf("\n");
	//V1에서 각 node의 path 출력 
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