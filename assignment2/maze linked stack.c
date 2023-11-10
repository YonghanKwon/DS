#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define numRow 5
#define numCol 5

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

typedef struct stack *stackPtr;
typedef struct stack{
	element map;
	stackPtr link;
}stack;
stackPtr top = NULL;

void stack_empty() {
	printf("stack is empty, cannot delete element");
	exit(EXIT_FAILURE);
}
void push(element item) {
	stackPtr temp;
	temp = (stackPtr)malloc(sizeof(stack));
	temp->map = item;
	temp->link = top;
	top = temp;
}
element pop() {
	stackPtr temp = top;
	element item;
	if (!temp)
		stack_empty();
	item = temp->map;
	top = temp->link;
	free(temp);
	return item;
}


int mark[numRow + 2][numCol + 2];
int maze[numRow + 2][numCol + 2];

void initial_mark(){
	for (int i = 0; i < numRow + 2; i++)
	{
		for (int j = 0; j < numCol + 2; j++)
		{
			mark[i][j] = 0;
		}
	}
}

void setup_maze() {
	short int maze0[numRow][numCol] = { // 여기서 줄 바꾸어 주세요(1).
	{ 0,1,1,1,1 },
	{ 1,0,1,1,1 },
	{ 1,0,0,1,1 },
	{ 0,0,1,1,1 },
	{ 1,0,0,0,0 } // 여기서 줄 바꾸어 주세요(2).
	};

	for (int i = 0; i < numRow + 2; i++){
		maze[0][i] = 1;
		maze[numRow + 1][i] = 1;
		maze[i][0] = 1;
		maze[i][numCol + 1] = 1;
	}
	for (int i = 0; i < numRow; i++){
		for (int j = 0; j < numCol; j++){
			maze[i + 1][j + 1] = maze0[i][j];
		}
	}
	// 2차원 배열 maze0[numRow][numCol]로부터
	// 전역변수인 2차원 배열 maze[numRow + 2][numCol + 2]를 설정 완료하는 코드
}

char mazech[numRow][numCol];

void drawmaze(int row,int col,bool found) {
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			if (maze[i + 1][j + 1] == 1)
				mazech[i][j] = 'x';
			else
				mazech[i][j] = ' ';
		}
	}

	for (int i = 0; i < numRow; i++)
	{
		stackPtr temp = NULL;
		if (top != NULL) {
			temp = top;
			while(temp != NULL){
				mazech[(*temp).map.row - 1][(*temp).map.col - 1] = '*';
				temp = temp->link;
			}
		}
	}
	mazech[row-1][col-1] = '*';
	if (found == true)
		mazech[numRow - 1][numCol - 1] = '*';
	printf("row/col  1  2  3  4  5\n");
	for(int i=0;i<numRow;i++)
		printf("   %d     %c  %c  %c  %c  %c\n",i+1, mazech[i][0],mazech[i][1] , mazech[i][2], mazech[i][3], mazech[i][4]);
}


typedef struct {
	short int vert;
	short int horiz;
}offset;
offset move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };


void path(void) {
	int i,a, row, col,dir, nextRow, nextCol;
	char c;
	bool found = false;
	element position;

	mark[1][1] = 1;
	row = 1;
	col = 1;
	dir = 1;
	position.row = row;
	position.col = col;
	position.dir = dir;
	push(position);

	drawmaze(row, col, found);
	printf("continue(Y/N)? :");
	
	do {
		scanf("%c", &c);
		if (c == 'N' || c == 'n')
		{
			printf("N이 입력되어서 프로그램을 종료함\n");
			exit(EXIT_FAILURE);
		}
		else if (c == 'Y' || c == 'y')
		{
			a = 0;
		}
		else {
			printf("Y나 N을 입력해 주십시오\n");
			printf("continue(Y/N)? :");

			a = 1;
		}
		c = getchar();
	} while (a);

	while (dir < 8 && !found)
	{
		nextRow = row + move[dir].vert;
		nextCol = col + move[dir].horiz;
		if (nextRow == numRow && nextCol == numCol) {
			found = true;
			drawmaze(row, col, found);
		}
		else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
			mark[nextRow][nextCol] = 1;
			position.row = row;
			position.col = col;
			position.dir = ++dir;
			push(position);
			row = nextRow;
			col = nextCol;
			dir = 0;
			drawmaze(row, col, found);
			printf("continue(Y/N)? :");

			do {
				scanf("%c", &c);
				if (c == 'N' || c == 'n')
				{
					printf("N이 입력되어서 프로그램을 종료함\n");
					exit(EXIT_FAILURE);
				}
				else if (c == 'Y' || c == 'y')
				{
					a = 0;
				}
				else {
					printf("Y나 N을 입력해 주십시오");
					printf("continue(Y/N)? :");
					
					a = 1;
				}
				c = getchar();
			} while (a);
		}
		else {
			++dir;
		}
	}
	
	if(found != true) printf("The maze does not have a path\n");
}

int main() {

	element free;//maze가 결과를 찾은 이후 동적할당된 top 변수들을 free하기 위한 변수

	initial_mark();
	setup_maze();
	path();

	while (top != NULL){
		free = pop();
	}

	return 0;
}