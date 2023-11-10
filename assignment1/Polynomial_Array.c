#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(A,B) ((A>B)?1:((A==B)?0:-1) 

typedef struct {//��� �迭 ���
	int degree;
	int *coef;
}polynomial_coefficient;

typedef struct {//�� �迭 ����� ��
	int coef;
	int exp;
}Term;

typedef struct {//�� �迭 ���
	int num_term;
	Term term[MAX_TERMS];
}polynomial_term;

Term Terms[MAX_TERMS]; //���׽� ���� ���ϱ� ���� ���׽� a,b,d�� �ѹ��� ������ ����
int avail=0; //���׽� ���� ���ϱ� ���� Terms������ ���׽�d�� ���尡���� ������ġ�� �����ϱ����� ����

void load_term(polynomial_term A,int n)//�� �迭 ������� �ۼ��� A(x)�� Terms ������ �ű�� ���� �ۼ���
{
	for (int i = 0; i < n; i++)
	{
		Terms[i].exp = A.term[i].exp;
		Terms[i].coef = A.term[i].coef;
		avail++;//Terms�� ���� ����Ǹ� �������� avail�� �׿� ���� ���ڰ� �����ؾ��Ѵ�. ���� ���� ������ ���� avail�� ���� ����������
	}
};

void load_coefficient(polynomial_coefficient B,int m)//��� �迭 ������� �ۼ��� B(x)�� �׹迭 ������� �ۼ��� Terms�� �ű�� �� ��ĵ� ����迭���� �׹迭 ������� ��ȯ�Ͽ� ������.
{
	for (int i = 0; i < B.degree+1; i++)
	{
		if (B.coef[i] != 0) {//�׹迭������� Terms�� �����ϱ� ���� ����迭��Ŀ��� 0���� ����� �κ��� �����ϱ����� ��
			Terms[m].coef = B.coef[i];
			Terms[m++].exp = B.degree - i;//����迭��Ŀ����� �׹迭��İ��� �޸� ���� ���� ������ ������ �����ϱ⶧���� �����ؾ��� ���� �����Ѵٸ� �� ���� ������ ����ϱ� ���� ���� ���� ������ ���� - �ݺ�ȹ��
			avail++;//Terms�� ���� ����Ǹ� �������� avail�� �׿� ���� ���ڰ� �����ؾ��Ѵ�. ���� ���� ������ ���� avail�� ���� ����������
		}
	}
};

void attach(float coefficient, int exponent)//���ο� ���� ÷���ϴ� �Լ�
{
	if (avail >= MAX_TERMS) {//Terms�� �������� �Ҵ�Ǿ��� ������ ����ġ �̻����� �޸𸮸� �䱸�Ѵٸ� �̸� �ź�
		printf("���׽Ŀ� ���� �ʹ� ����.");
		exit(1);
	}
	Terms[avail].coef = coefficient;
	Terms[avail++].exp = exponent;//���� ����� ���Ŀ� �� ���� Terms ��ҿ� ���� �����ؾ��ϹǷ� avail���� ������Ŵ
};

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) 
{
	int coefficient;//������ ���� ��� �� ���� ���Ͽ� ������ ���� ����
	*startD = avail;
	while (startA <= finishA && startB <= finishB ) {
		switch (COMPARE(Terms[startA].exp, Terms[startB].exp)))
		{
		case -1://B���� ������ Ŭ ���
			attach(Terms[startB].coef, Terms[startB].exp);//B���� ������ ����� Terms�� avail��°�� ����
			startB++;
			break;
		case 0://�� ���� ������ ���� ���
			coefficient = Terms[startA].coef + Terms[startB].coef;
			if (coefficient)
			{
				attach(coefficient, Terms[startA].exp);
			}
				startA++;
				startB++;
				break;
		case 1://A���� ������ Ŭ ���
			attach(Terms[startA].coef, Terms[startA].exp);//A���� ������ ����� Terms�� avail��°�� ����
			startA++;
		}
	}
	for (; startA <= finishA; startA++)//while�� ���� A�Ŀ� ���� ���� ���� ��� ���� ������ Terms�� ����
		attach(Terms[startA].coef, Terms[startA].exp);
	for (; startB <= finishB; startB++)//while�� ���� B�Ŀ� ���� ���� ���� ��� ���� ������ Terms�� ����
		attach(Terms[startB].coef, Terms[startB].exp);
	*finishD = avail;
};

int main(char string[])
{
	int routine_num_term,routine_num_coefficient,temperate_degree;//�׹迭���, ����迭��Ŀ��� 0�� �ƴ� ����� ������ �����ϱ����� ����� ����
	int n=0;//����迭��Ŀ��� ����� �迭�� ����Ǵµ� for���� ����� �ִ� ��쿡�� �ݺ��ǹǷ� �Էµ� ������ �ڸ��� �����ϱ� ���� �� ������ ����ϱ� ���� ����� ����
	int pre_temperate_degree=0;//����迭��Ŀ��� ������ �������� ������ �������� ���Ͽ� �� ���̸�ŭ �������� 0�� �����ϴµ�, ������ �������� �����ϱ� ���� ����
	int *startD;//Terms�� D�������� ������
	int *finishD;//Terms�� D�������� ��������

	polynomial_term A;//�׹迭���A(x)
	polynomial_coefficient B;//����迭���B(x)

	printf("Enter A(x):\n");
	printf("����� 0�� �ƴ� ���� ��?:");
	scanf_s("%d", &routine_num_term);
	if (routine_num_term == 0)
	{
		return 0;//A(x)���� 0�� �ƴ� ���� ������ 0�̸� ���α׷��� ����
	}
	for (int i = 0; i < routine_num_term; i++)
	{
		printf("����?:");
		scanf_s("%d", &A.term[i].exp);
		printf("���?:");
		scanf_s("%d", &A.term[i].coef);
	}

	printf("Enter B(x):\n");
	printf("����� 0�� �ƴ� ���� ��?:");
	scanf_s("%d",&routine_num_coefficient);

	for (int i = 0; i < routine_num_coefficient;i++)
	{
		printf("����?:");
		scanf_s("%d", &temperate_degree);//����迭���

		if (i == 0)//������������ �Էõȴٸ� ���� ���� �ԷµǴ� ������ ���� ���� ������ �����̹Ƿ� ���� ó���� ��� ����
		{
			B.degree = temperate_degree;//���� ���� �ԷµǴ� ������ ���� ���� ������ �����̹Ƿ� �� ������ ����
			B.coef = (int*)malloc((B.degree + 1) * sizeof(int));//�Էµ� ���� ū ����+1��ŭ B(x)�� ����� ������ �޸� �����Ҵ�
		}
		else
		{
			int sub_degree =pre_temperate_degree - temperate_degree-1;//����迭��Ŀ��� ���� ������ �� ���� ������ ���̸�ŭ ������ ������ 0�� ����Ǿ���ϹǷ� �� ���̸� ���
			if (sub_degree != 0) {
				for (int j = 0; j < sub_degree; j++) {//������ ������ 0�� ����
					B.coef[n] = 0;
					n++;//B.coef�� n��° ��ҿ� �� ���� ��ҵ鿡 �����ϱ� ���� n�� ���� ������Ŵ
				}
			}
		}
		printf("���?:");
		scanf_s("%d",B.coef+n);
		
		pre_temperate_degree = temperate_degree;
		n++;

		if (i == routine_num_coefficient-1)//������ ���� ������ 0�� �ƴ϶�� �� ���ĺκп� 0�� �������� �ʰ� ���α׷��� �������ǹǷ� �̸� �ذ��ϱ� ���� �ۼ���
		{
			for (; n <= B.degree;) 
			{
				B.coef[n] = 0;//������ �κп� 0���� �ʱ�ȭ
				n++;
			}
		}
	}

	for (int j = 0; j < routine_num_term; j++)//A(x) �������� ���
	{
		printf("A[%d].coef=%d	A[%d].exp=%d\n", j, A.term[j].coef,j,A.term[j].exp);

	}

	printf("B.degree=%d\n", B.degree);//B(x)�� ���� ���
	for (int i = 0; i < B.degree + 1; i++)//B(x)�� ��� ���
	{
		if (B.coef[i] != 0)
		{
			printf("B.coef[%d] = %d\n", i, B.coef[i]);
		}
	}

	load_term(A, routine_num_term);//A(x)���� Terms�� �����ϴ� �Լ�
	load_coefficient(B, routine_num_term);//B(x)���� Terms�� �����ϴ� �Լ�

	padd(0,routine_num_term - 1, routine_num_term, routine_num_term + routine_num_coefficient-1,&startD,&finishD);//Terms�� ����� A(x)�� B(x)���� ���ϴ� �Լ�

	for (int i = startD; i < finishD; i++)//D(x)�� ���
	{
		printf("D[%d].coef = %d	", i - routine_num_coefficient - routine_num_term, Terms[i].coef);
		printf("D[%d].exp = %d\n",i-routine_num_coefficient-routine_num_term, Terms[i].exp);
	}

	free(B.coef);//�����Ҵ�� B.coef free

	system("pause>null");

	return 0;
}