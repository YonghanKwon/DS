#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(A,B) ((A>B)?1:((A==B)?0:-1) 

typedef struct {//계수 배열 방식
	int degree;
	int *coef;
}polynomial_coefficient;

typedef struct {//항 배열 방식의 항
	int coef;
	int exp;
}Term;

typedef struct {//항 배열 방식
	int num_term;
	Term term[MAX_TERMS];
}polynomial_term;

Term Terms[MAX_TERMS]; //다항식 합을 구하기 위해 다항식 a,b,d를 한번에 저장할 변수
int avail=0; //다항식 합을 구하기 위해 Terms변수중 다항식d를 저장가능한 시작위치를 저장하기위한 변수

void load_term(polynomial_term A,int n)//항 배열 방식으로 작성된 A(x)를 Terms 변수로 옮기기 위해 작성함
{
	for (int i = 0; i < n; i++)
	{
		Terms[i].exp = A.term[i].exp;
		Terms[i].coef = A.term[i].coef;
		avail++;//Terms에 값이 저장되면 전역변수 avail도 그에 따라서 숫자가 증가해야한다. 따라서 값을 저장한 이후 avail도 값을 증가시켜줌
	}
};

void load_coefficient(polynomial_coefficient B,int m)//계수 배열 방식으로 작성된 B(x)를 항배열 방식으로 작성된 Terms에 옮기고 그 방식도 계수배열에서 항배열 방식으로 변환하여 저장함.
{
	for (int i = 0; i < B.degree+1; i++)
	{
		if (B.coef[i] != 0) {//항배열방식으로 Terms에 저장하기 위해 계수배열방식에서 0으로 저장된 부분을 제외하기위해 씀
			Terms[m].coef = B.coef[i];
			Terms[m++].exp = B.degree - i;//계수배열방식에서는 항배열방식과는 달리 가장 높은 차수의 지수만 저장하기때문에 저장해야할 항이 등장한다면 그 항의 지수를 계산하기 위해 가장 높은 차수의 지수 - 반복획수
			avail++;//Terms에 값이 저장되면 전역변수 avail도 그에 따라서 숫자가 증가해야한다. 따라서 값을 저장한 이후 avail도 값을 증가시켜줌
		}
	}
};

void attach(float coefficient, int exponent)//새로운 항을 첨가하는 함수
{
	if (avail >= MAX_TERMS) {//Terms가 정적으로 할당되었기 때문에 기준치 이상으로 메모리를 요구한다면 이를 거부
		printf("다항식에 항이 너무 많다.");
		exit(1);
	}
	Terms[avail].coef = coefficient;
	Terms[avail++].exp = exponent;//값이 저장된 이후에 그 다음 Terms 요소에 값을 저장해야하므로 avail값을 증가시킴
};

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) 
{
	int coefficient;//지수가 같을 경우 그 값을 더하여 저장할 변수 선언
	*startD = avail;
	while (startA <= finishA && startB <= finishB ) {
		switch (COMPARE(Terms[startA].exp, Terms[startB].exp)))
		{
		case -1://B식의 지수가 클 경우
			attach(Terms[startB].coef, Terms[startB].exp);//B식의 지수와 계수를 Terms의 avail번째에 저장
			startB++;
			break;
		case 0://두 식의 지수가 같을 경우
			coefficient = Terms[startA].coef + Terms[startB].coef;
			if (coefficient)
			{
				attach(coefficient, Terms[startA].exp);
			}
				startA++;
				startB++;
				break;
		case 1://A식의 지수가 클 경우
			attach(Terms[startA].coef, Terms[startA].exp);//A식의 지수와 계수를 Terms의 avail번째에 저장
			startA++;
		}
	}
	for (; startA <= finishA; startA++)//while문 이후 A식에 남은 값이 있을 경우 남은 값들을 Terms에 저장
		attach(Terms[startA].coef, Terms[startA].exp);
	for (; startB <= finishB; startB++)//while문 이후 B식에 남은 값이 있을 경우 남은 값들을 Terms에 저장
		attach(Terms[startB].coef, Terms[startB].exp);
	*finishD = avail;
};

int main(char string[])
{
	int routine_num_term,routine_num_coefficient,temperate_degree;//항배열방식, 계수배열방식에서 0이 아닌 계수의 갯수를 저장하기위해 선언된 변수
	int n=0;//계수배열방식에서 계수가 배열로 저장되는데 for문은 계수가 있는 경우에만 반복되므로 입력된 지수의 자리에 저장하기 위해 그 순번을 기록하기 위해 선언된 변수
	int pre_temperate_degree=0;//계수배열방식에서 이전의 지수값과 현재의 지수값을 비교하여 그 차이만큼 남은곳에 0을 저장하는데, 이전의 지수값을 저장하기 위한 변수
	int *startD;//Terms중 D방정식의 시작점
	int *finishD;//Terms중 D방정식의 마지막점

	polynomial_term A;//항배열방식A(x)
	polynomial_coefficient B;//계수배열방식B(x)

	printf("Enter A(x):\n");
	printf("계수가 0이 아닌 항의 수?:");
	scanf_s("%d", &routine_num_term);
	if (routine_num_term == 0)
	{
		return 0;//A(x)에서 0이 아닌 항의 갯수가 0이면 프로그램을 종료
	}
	for (int i = 0; i < routine_num_term; i++)
	{
		printf("지수?:");
		scanf_s("%d", &A.term[i].exp);
		printf("계수?:");
		scanf_s("%d", &A.term[i].coef);
	}

	printf("Enter B(x):\n");
	printf("계수가 0이 아닌 항의 수?:");
	scanf_s("%d",&routine_num_coefficient);

	for (int i = 0; i < routine_num_coefficient;i++)
	{
		printf("지수?:");
		scanf_s("%d", &temperate_degree);//계수배열방식

		if (i == 0)//내림차순으로 입련된다면 가장 먼저 입력되는 지수가 가장 높은 차수의 지수이므로 가장 처음의 경우 선택
		{
			B.degree = temperate_degree;//가정 먼저 입력되는 지수가 가장 높은 차수의 지수이므로 그 지수를 저장
			B.coef = (int*)malloc((B.degree + 1) * sizeof(int));//입력된 가장 큰 지수+1만큼 B(x)의 계수를 저장할 메모리 동적할당
		}
		else
		{
			int sub_degree =pre_temperate_degree - temperate_degree-1;//계수배열방식에서 전의 지수와 그 다음 지수의 차이만큼 나머지 공간에 0이 저장되어야하므로 그 차이를 계산
			if (sub_degree != 0) {
				for (int j = 0; j < sub_degree; j++) {//나머지 공간에 0을 저장
					B.coef[n] = 0;
					n++;//B.coef의 n번째 요소와 그 이후 요소들에 접근하기 위해 n의 값을 증가시킴
				}
			}
		}
		printf("계수?:");
		scanf_s("%d",B.coef+n);
		
		pre_temperate_degree = temperate_degree;
		n++;

		if (i == routine_num_coefficient-1)//마지막 항의 지수가 0이 아니라면 그 이후부분에 0을 저장하지 않고 프로그램이 마무리되므로 이를 해결하기 위해 작성함
		{
			for (; n <= B.degree;) 
			{
				B.coef[n] = 0;//나머지 부분에 0으로 초기화
				n++;
			}
		}
	}

	for (int j = 0; j < routine_num_term; j++)//A(x) 방정식을 출력
	{
		printf("A[%d].coef=%d	A[%d].exp=%d\n", j, A.term[j].coef,j,A.term[j].exp);

	}

	printf("B.degree=%d\n", B.degree);//B(x)의 지수 출력
	for (int i = 0; i < B.degree + 1; i++)//B(x)의 계수 출력
	{
		if (B.coef[i] != 0)
		{
			printf("B.coef[%d] = %d\n", i, B.coef[i]);
		}
	}

	load_term(A, routine_num_term);//A(x)식을 Terms에 저장하는 함수
	load_coefficient(B, routine_num_term);//B(x)식을 Terms에 저장하는 함수

	padd(0,routine_num_term - 1, routine_num_term, routine_num_term + routine_num_coefficient-1,&startD,&finishD);//Terms에 저장된 A(x)와 B(x)식을 더하는 함수

	for (int i = startD; i < finishD; i++)//D(x)를 출력
	{
		printf("D[%d].coef = %d	", i - routine_num_coefficient - routine_num_term, Terms[i].coef);
		printf("D[%d].exp = %d\n",i-routine_num_coefficient-routine_num_term, Terms[i].exp);
	}

	free(B.coef);//동적할당된 B.coef free

	system("pause>null");

	return 0;
}