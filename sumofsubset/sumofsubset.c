#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#define index int

void sum_of_subsets(index i, int weight, int total, int *w, int *include, int W); //sum_of_subset 알고리즘 함수
bool promising(index i, int weight, int total, int *w, int W); //유망함의 여부 알아보는 함수

int main(void)
{
	int size, W, total=0;
	int *w, *include;

	printf("무게 개수: ");
	scanf("%d", &size); //무게의 수

	w = (int*)malloc(sizeof(int)*(size+1)); //무게가 저장될 배열 크기 할당
	include = (int*)malloc(sizeof(int)*(size + 1)); //해당 무게가 포함된지의 여부 저장될 배열 크기 할당

	printf("무게 입력)\n");
	for (int i = 0; i < size; i++)  //무게를 입력받고 w배열에 저장, 그리고 총 무게의 합을 total에 저장
	{
		printf("w%d 무게: ", i+1);
		scanf("%d", &w[i + 1]);
		total += w[i + 1];
	}
	printf("구하려는 무게: ");
	scanf("%d", &W);  //구할 무게 W

	printf("\n");
	sum_of_subsets(0, 0, total, w, include, W);
	free(w);
	free(include);
}

void sum_of_subsets(index i, int weight, int total, int *w, int *include, int W)
{
	if (promising(i, weight, total, w, W)) //유망하면 실행
		if (weight == W) //유망하고 내가 원하는 무게가 구해졌다면 출력
		{
			printf("include1~%d: ", i);
			for (int j = 1; j <= i; j++) //include의 값 출력
			{	
				printf("%d ", include[j]);
			}
			printf("\n");
			printf("합이 %d가 되는 정수의 조합: ", W);
			for (int j = 1; j <= i; j++) //include[i]=1이면 i번째 무게는 포함하므로 출력
			{
				if (include[j] == 1)
					printf("w%d(%d) ", j,w[j]);
			}
		}
		else //유망하지만 내가 원하는 무게가 아니라면 다음 무게를 포함, 미포함한 함수를 다시 실행
		{
			include[i + 1] = 1; //다음 무게를 포함시킨다
			sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1], w, include, W);
			include[i + 1] = 0; //다음 무게를 포함시키지 않는다
			sum_of_subsets(i + 1, weight, total - w[i + 1], w, include, W);

		}
}

bool promising(index i, int weight, int total, int *w, int W)
{
	//1.지금까지의 무게와 남은 무게가 원하는 무게보다 크거나같다.
	//2.지금까지의 무게가 원하는 무게이거나 다음무게까지의 합이 원하는 무게 이하이다.
	//1,2 가 모두 충족되면 유망하다.
	return (weight + total >= W) && ((weight == W) || (weight + w[i + 1] <= W));
}